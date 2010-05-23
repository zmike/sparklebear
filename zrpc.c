/*zrpc efl c bindings base
 * 2010 Mike Blumenkrantz*/

#include "zrpc.h"
#include "xml.c"


/*called every time a new connection is made
 * data is the zcon struct passed to the zrpc function
 */
static int
_zcon_add(void *data, int type, void *event)
{
	zrpc_con *zcon;
	char itoav[13];
	Ecore_Con_Event_Server_Add *ev;
        Eina_Strbuf *sbuf;
        int x;
	zrpc_handle z = -1;

	if (!(zcon = data)) return 1;

	ev = event;
	for (x = 0; x < 100; x++)
	/*try to find our server handle*/
		if (zcon->server[x])
		/*if the server exists*/
			if (zcon->server[x] == ev->server)
			{/*and if it's the right one*/
				z = x;
				/*make it our handle*/
				break;
			}
	/*if we don't find it, bail*/
	if (z < 0) return 1;
	/*if the buffer in the handle has no data, delete the object*/
	if (!zcon->buf[z])
	{
		ecore_con_server_del(zcon->server[z]);
		return 1;
	}


        sbuf = eina_strbuf_new();
	/*set http header*/

	eina_strbuf_append(sbuf, "POST ");
        if (zcon->rpc_path)
                eina_strbuf_append(sbuf, zcon->rpc_path);
        else
                eina_strbuf_append(sbuf, "/");

	eina_convert_itoa(eina_strbuf_length_get(zcon->buf[z]), itoav);
	eina_strbuf_append_printf(sbuf, " HTTP/1.1\n\
Content-Type: text/xml\n\
Content-length: %s\n", itoav);

	if (zcon->host_header)
                eina_strbuf_append_printf(sbuf, "Host: %s\n", zcon->host_header);

	if (zcon->zcookie)
	/*add cookie if it exists*/
                eina_strbuf_append_printf(sbuf, "Cookie: sessid=%s\n", zcon->zcookie);

	eina_strbuf_prepend_printf(zcon->buf[z], "%s\n", eina_strbuf_string_get(sbuf));

#ifdef DEBUG
	printf("\n\t\tCalling %s @ %s:%d\n", zcon->call[z], zcon->host, zcon->port);
#endif
#ifdef XML_DEBUG
	printf("\n%s\n", eina_strbuf_string_get(zcon->buf[z]));
#endif
	/*actually queue up the send job*/
	if (!ecore_con_server_send(zcon->server[z], eina_strbuf_string_get(zcon->buf[z]), eina_strbuf_length_get(zcon->buf[z])))
		printf("send failed!\n");

	/*no need to free anything else, _zcon_del will take care of that*/

	/*returning 1 means this function will continue to be reused
	 * any time a server connect is made, which is what we want
	 */
	return 1;
}

/*called any time a server object is deleted
 * ie on connect error, receive error
 */
static int
_zcon_del(void *data, int type, void *event)
{
	zrpc_con *zcon;
	Ecore_Con_Event_Server_Del *ev;
	int x;
	zrpc_handle z = -1;

	/*same handle check*/
	zcon = data;
	ev = event;
	for (x = 0; x < 100; x++)
		if (zcon->server[x])
			if (zcon->server[x] == ev->server)
			{
				z = x;
				break;
			}
	if (z < 0) return 1;

	/*output something to console*/
	fprintf(stderr, "%s on handle %d failed!\n", zcon->call[z], z);

	ecore_con_server_del(zcon->server[z]);
	zcon->server[z] = NULL;

	/*reset buffer if it exists*/
	eina_strbuf_free(zcon->buf[z]);
	zcon->buf[z] = NULL;

	/*zero the reply since it will be wrong anyway*/
	eina_strbuf_free(zcon->recbuf[z]);
	zcon->recbuf[z] = NULL;

	if (!strcmp(zcon->call[z], "User.logout"))
	{/*free/null the cookie on logout*/
		eina_stringshare_del(zcon->zcookie);
		zcon->zcookie = NULL;
	}
	eina_stringshare_del(zcon->call[z]);

	/*pass the callback so an error can be detected*/
	if (zcon->cb[z])
	{
		/*run the cb, passing along the handle*/
		(*zcon->cb[z])(NULL, zcon->cbd[z]);
	}



	/*again, this cb is to be reused so return 1*/
	return 1;
}

/*this is the handler for data receive*/
static int
_zcon_rec(void *data, int type, void *event)
{
	zrpc_con *zcon;
	Ecore_Con_Event_Server_Data *ev;
	int x;
	const char *test;
        char buf[37], *ret;
	zrpc_handle z = -1;
	
	/*regular handle grab/check*/
	if (!(zcon = data)) return 1;
	ev = event;

	for (x = 0; x < 100; x++)
		if (zcon->server[x])
			if (zcon->server[x] == ev->server)
			{
				z = x;
				break;
			}
	if (z < 0) return 1;

	if (!zcon->recbuf[z])
                zcon->recbuf[z] = eina_strbuf_new();

        /*try to append, involves a realloc so bail if we fail*/
	if (!eina_strbuf_append_length(zcon->recbuf[z], ev->data, ev->size))
		return 1;

#ifdef XML_DEBUG
	printf("\n%s\n", eina_strbuf_string_get(zcon->recbuf[z]));
#endif
        test = eina_strbuf_string_get(zcon->recbuf[z]);
	if (strstr(test, "</methodResponse>"))
	{/*if methodresponse> is receieved, we have the full call*/
		/*done with the server now, so we can call delete on it*/
		ecore_con_server_del(zcon->server[z]);
		zcon->server[z] = NULL;

		eina_strbuf_free(zcon->buf[z]);
		zcon->buf[z] = NULL;

		if (zcon->call[z])
		{
			if (!strcmp(zcon->call[z], "User.logout"))
			{
				eina_stringshare_del(zcon->zcookie);
				zcon->zcookie = NULL;
			}
			else if (!strcmp(zcon->call[z], "User.login"))
			{
				if (zcon->zcookie) eina_stringshare_del(zcon->zcookie);
                                test = eina_strbuf_string_get(zcon->recbuf[z]);
				test = strstr(test, "sessid=");
				sscanf(test, "sessid=%[^;];", buf);
				zcon->zcookie = eina_stringshare_add(buf);
#ifdef DEBUG
printf("Cookie grabbed: %s\n", zcon->zcookie);
#endif
			}
			eina_stringshare_del(zcon->call[z]);
		}

		ret = eina_strbuf_string_steal(zcon->recbuf[z]);
                eina_strbuf_free(zcon->recbuf[z]);
		zcon->recbuf[z] = NULL;
		
		/*if we get this far, we have a null terminated rpc response
		 * now we can use the zcon struct's callback if it exists
		 */
		if (zcon->cb[z])
		{
			/*run the cb, passing along the reply*/
			(*zcon->cb[z])((const char*)ret, zcon->cbd[z]);
		}

                free(ret);

	}
		
	/*reuse this as well*/
	return 1;
}

/*meta function for all other zrpc functions; should not be called directly*/
int zrpc_meta(const char *call, Eina_List *params, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	/*set up initial variables*/
	xmlDocPtr doc;
	xmlChar *xmlbuff;
	int buffersize, x, *y, w, numints;
	void *a, *b;
	Eina_List *l = NULL;
	void *s;
	zrpc_handle z = -1;

	
	for (x = 0; x < 100; x++)
	/*try to grab a handle on an empty zcon*/
		if ((!zcon->server[x]) && (!zcon->recbuf[x]))
		{/*check both server object and recbuf before setting handle*/
			z = x;
			break;
		}
	if (z < 0) return 0;
#ifdef DEBUG
	printf("Grabbed handle: %d\n", z);
#endif
	/*set the call*/
	zcon->call[z] = call;
	/*set params*/
	zcon->params[z] = params;
	/*set cb*/
	zcon->cb[z] = cb;
	zcon->cbd[z] = cbd;
	doc = xmlNewDoc(BAD_CAST "1.0"); //init the xml document
	xml_xml_new_call(doc, zcon->call[z]); //set up the doc with the methodcall
	if (zcon->params[z])
	{/*if the params aren't null*/
		EINA_LIST_FOREACH(zcon->params[z], l, s)
		/* use eina list for params to have uniform functions */
		{/*FIXME: add type checking for last couple calls*/
			if (isalnum((*(char*)s))) /*dereference char* to char and check for non-garbage*/
				xml_xml_new_string(doc, (char*)s); /*must be string*/
			else /*otherwise int*/
			{
				y = (int*)s;
				w = 0;
				numints = 0;
				a = NULL;
				b = NULL;
				if (l->prev)
					a = l->prev->data;
				if (l->next)
					b = l->next->data;
				while (1)
				{/*only way out is through break*/
					if (w > 0) /*don't want invalid subscript errors*/
						if ((abs(y[w] - y[w-1]) > 100000)
						/*if it's an array of ints, the values will not
						 * be more than 100k apart for any zrpc function
						 * currently existing, so it's heap data*/
							|| (&y[w] == a) || (&y[w] == b))
							/*also check prev/next items in list for pointer collision*/
							break;
					numints++;
					w++;
				}
				if (numints > 1)
				{
					xml_xml_new_array(doc);
					for (w = 0; w < numints; w++)
						xml_xml_new_int(doc, y[w], 1);
				}
				else
					xml_xml_new_int(doc, y[0], 0);
			}
		}
	}
	//dumps the xmldoc into a a xmlChar* which is the same as a char*
	xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
	//copy to zcon struct and set bufsize
        zcon->buf[z] = eina_strbuf_new();
        eina_strbuf_append(zcon->buf[z], (char*)xmlbuff);

	//add event handlers if they don't exist
	if (!zcon->add) zcon->add = ecore_event_handler_add(ECORE_CON_EVENT_SERVER_ADD, _zcon_add, zcon);
	if (!zcon->del) zcon->del = ecore_event_handler_add(ECORE_CON_EVENT_SERVER_DEL, _zcon_del, zcon);
	if (!zcon->data) zcon->data = ecore_event_handler_add(ECORE_CON_EVENT_SERVER_DATA, _zcon_rec, zcon);

	//set the server and make the call
	zcon->server[z] = ecore_con_server_connect(ECORE_CON_REMOTE_SYSTEM, zcon->host, zcon->port, zcon);

	if (params)
	{/*free params if there were any*/
		EINA_LIST_FREE(params, s)
			if (isalnum((*(char*)s)))
			/*check for strings to free*/
				eina_stringshare_del(s);

	}
	/*null the list to prevent magic fail if we reuse it*/
	zcon->params[z] = NULL;

	//free xml stuff
	xmlFree(xmlbuff);
	xmlFreeDoc(doc);

	return 1;

}

#include "zrpc_functions.c"

/*for sorting a list of uids*/
static int uid_sort(const void *a, const void *b)
{
	const zrpc_user *x = a;
	const zrpc_user *y = b;

	return x->uid - y->uid;
}

static void _collector(const char *reply, void *data)
{
	zrpc_meta_struct *meta = data;
	int it = 0, numusers = meta->num;
	static int count;
	zrpc_user *user;
	xmlNode *r;
	double timer;
	zrpc_con *zcon;
	static Eina_List *users;

	if (count++ == 0) it = 1;

	if (!(zcon = meta->zcon)) return;

	if (!(r = xml_parse_xml(reply)))
          return;

	user = xml_parse_user(r);

	users = eina_list_append(users, user);
	if (!it) return;

	//if (eina_list_count(users) != 1) return;


#ifdef DEBUG
printf("DEBUG: waiting for %d user infos to come in...\n", numusers);
#endif

	timer = ecore_time_get(); /*don't want to get stuck here*/
	while ((count < numusers) && (ecore_time_get() < (timer+10)))
	{
#ifdef DEBUG
printf("DEBUG: %d of %d have arrived...\n", count, numusers);
#endif
		ecore_main_loop_iterate();
	}
	count = 0;

	users = eina_list_sort(users, eina_list_count(users), uid_sort);

#ifdef DEBUG
	Eina_List *l;
	EINA_LIST_FOREACH(users, l, user)
		printf("DEBUG: Added user %d:%s-%s to list\n", user->uid, user->name, user->language);
#endif

	meta->extra = users;
	users = NULL;

	meta->cb(NULL, meta);
}

static void _getusers(const char *reply, void *data)
{
	zrpc_meta_struct *meta = data;
	zrpc_con *zcon;
	xmlNode *r;
	int *users, it, numusers = 0;

	if (!(zcon = meta->zcon)) return;

	if (!(r = xml_parse_xml(reply)))
          return;
	users = xml_parse_users(r);

	/*count up the users*/
	for (it = 1; users[it]; it++)
		numusers++;

	/*if 0, don't even bother*/
	if (!numusers)
	{
		meta->cb(NULL, NULL);
		return;
	}

	/*increment here if the first user is 0 since we had to skip it to loop before since I'm lazy*/
	if (users[0] == 0) numusers++;
#ifdef DEBUG
	printf("DEBUG: Found %d users\n", numusers);
#endif
	/*set to meta*/
	meta->num = numusers;
	for (it = 0; it < numusers; it++)
	{
#ifdef DEBUG
		printf("DEBUG: fetching info for user with uid: %d\n", users[it]);
#endif		/*actually send the request*/
		zrpc_User_getUserByUID(users[it], zcon, _collector, meta);
	}/*free the int array*/
	free(users);
}

/* meta function to implement getUsersFull */
int meta_getUsersFull(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	/*use a zrpc meta here to preserve what was passed to it*/
	zrpc_meta_struct *x = zmeta_new();
	x->cb = cb;
	x->zcon = zcon;
	x->cbd = cbd;

	if (!zrpc_User_getUsers(zcon, _getusers, x))
		return 0;
		
	return 1;
}

zrpc_meta_struct *zmeta_new()
{
	zrpc_meta_struct *new;
	if (!(new = calloc(1, sizeof(zrpc_meta_struct))))
		return NULL;

	return new;
}

zrpc_disk *zdisk_new()
{
	zrpc_disk *new;
	if (!(new = calloc(1, sizeof(zrpc_disk))))
		return NULL;

	return new;
}

void zdisk_free(zrpc_disk *disk)
{
	if (!disk) return;

	eina_stringshare_del(disk->int_dev);
	eina_stringshare_del(disk->ext_dev);
	eina_stringshare_del(disk->mode);
	eina_stringshare_del(disk->type);
	eina_stringshare_del(disk->partition_type);
	eina_stringshare_del(disk->mapped_dev);

	free(disk);
}


zrpc_vif *zvif_new()
{
	zrpc_vif *new;
	if (!(new = calloc(1, sizeof(zrpc_vif))))
		return NULL;

	return new;
}

void zvif_free(zrpc_vif *vif)
{
	if (!vif) return;

	eina_stringshare_del(vif->name);
	eina_stringshare_del(vif->mac);
	eina_stringshare_del(vif->bridge);
	eina_stringshare_del(vif->script);
	eina_stringshare_del(vif->type);
	eina_stringshare_del(vif->ip);
	eina_stringshare_del(vif->netmask);
	eina_stringshare_del(vif->gateway);
	eina_stringshare_del(vif->broadcast);

	free(vif);
}

zrpc_vm *zvm_new()
{
	zrpc_vm *new;
	if (!(new = calloc(1, sizeof(zrpc_vm))))
		return NULL;
	
	return new;
}

void zvm_free(zrpc_vm *vm)
{
        zrpc_disk *disk;
        zrpc_vif *vif;
        
	if (!vm) return;

	eina_stringshare_del(vm->name);
	eina_stringshare_del(vm->uuid);
	eina_stringshare_del(vm->puuid);
	eina_stringshare_del(vm->type);
	eina_stringshare_del(vm->os);
	eina_stringshare_del(vm->kernel);
	eina_stringshare_del(vm->ramdisk);
	eina_stringshare_del(vm->cmdline);
	eina_stringshare_del(vm->on_reboot);
	eina_stringshare_del(vm->on_poweroff);
	eina_stringshare_del(vm->on_crash);
	eina_stringshare_del(vm->vncpasswd);
	eina_stringshare_del(vm->state);

	EINA_LIST_FREE(vm->disks, disk)
		zdisk_free(disk);
	EINA_LIST_FREE(vm->vifs, vif)
		zvif_free(vif);

	free(vm);
}

zrpc_user *zuser_new()
{
	zrpc_user *new;
        
	if (!(new = calloc(1, sizeof(zrpc_user))))
		return NULL;

	return new;
}

void zuser_free(zrpc_user *user)
{
	if (!user) return;

	eina_stringshare_del(user->name);
	eina_stringshare_del(user->email);
	eina_stringshare_del(user->language);

	free(user);
}
