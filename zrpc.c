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
	const char *zreq, *itoav;
	char *post, *http, *host, *cookiestring, *req;
	Ecore_Con_Event_Server_Add *ev;
	int len, headlen, x, host_header = 0, rsize;
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
	/*make this all local so we can reuse the struct later*/
	zreq = zcon->buf[z];
	len = zcon->bufsize[z];
	zcon->buf[z] = NULL;
	zcon->bufsize[z] = 0;



	/*set http header*/

	post = "POST ";
	http = " HTTP/1.1\n\
Content-Type: text/xml\n\
Content-length: ";

	host = NULL;
	if (zcon->host_header)
	{
		host = calloc(strlen(zcon->host_header)+strlen("Host: \n")+1, sizeof(char));
		sprintf(host, "Host: %s\n", zcon->host_header);
		host_header = strlen(host);
	}
	headlen = strlen(post) + strlen(http) + ((zcon->rpc_path) ? strlen(zcon->rpc_path) : 1) + host_header;
	/*call itoa for request length*/
	itoav = itoa(strlen(zreq)); //malloc string has to be freed later
	if (zcon->zcookie != NULL)
	{/*add cookie if it exists*/
		cookiestring = "Cookie: sessid=";
		rsize = strlen(zreq)+headlen+eina_stringshare_strlen(itoav)+strlen(cookiestring)+eina_stringshare_strlen(zcon->zcookie);
		req = calloc((rsize+4), sizeof(char)); /*+3 for newlines, 1 for null*/
		if (host) sprintf(req, "%s%s%s%d\n%s%s%s\n\n%s", post, ((zcon->rpc_path) ? zcon->rpc_path : "/") , http, len, cookiestring, zcon->zcookie, host, zreq);
		else sprintf(req, "%s%s%s%d\n%s%s\n\n%s", post, ((zcon->rpc_path) ? zcon->rpc_path : "/") , http, len, cookiestring, zcon->zcookie, zreq);
	}
	else
	{/*must be a login, so no cookie added*/
		req = calloc((strlen(zreq)+headlen+eina_stringshare_strlen(itoav))+3, sizeof(char));
		if (host) sprintf(req, "%s%s%s%d\n%s\n%s", post, ((zcon->rpc_path) ? zcon->rpc_path : "/") , http, len, host, zreq);
		else sprintf(req, "%s%s%s%d\n\n%s", post, ((zcon->rpc_path) ? zcon->rpc_path : "/") , http, len, zreq);
	}
	/*free itoa result*/
	eina_stringshare_del(itoav);
	eina_stringshare_del(zreq);
	free(host);

	zcon->buf[z] = eina_stringshare_add(req);
	free(req);

	/*size of request*/
	zcon->bufsize[z] = eina_stringshare_strlen(zcon->buf[z]);

#ifdef DEBUG
	printf("\n\t\tCalling %s @ %s:%d\n", zcon->call[z], zcon->host, zcon->port);
#endif
#ifdef XML_DEBUG
	printf("\n%s\n", zcon->buf[z]);
#endif
	/*actually queue up the send job*/
	if (!ecore_con_server_send(zcon->server[z], zcon->buf[z], zcon->bufsize[z]))
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
	zrpc_network_cb cb;

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
	eina_stringshare_del(zcon->buf[z]);
	zcon->buf[z] = NULL;

	zcon->bufsize[z] = 0;

	/*zero the reply since it will be wrong anyway*/
	eina_stringshare_del(zcon->recbuf[z]);
	zcon->recbuf[z] = NULL;
	zcon->recbufsize[z] = 0;

	if (streq(zcon->call[z], "User.logout"))
	{/*free/null the cookie on logout*/
		eina_stringshare_del(zcon->zcookie);
		zcon->zcookie = NULL;
	}
	eina_stringshare_del(zcon->call[z]);

	/*pass the callback so an error can be detected*/
	if (zcon->cb[z])
	{
		if (!(cb = zcon->cb[z]))
		{
			printf("setting cb failed!\n");
			return 1;
		}
		/*run the cb, passing along the handle*/
		cb(zcon->cbd[z], NULL);
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
	char *test, buf[37];
	const char *ret;
	zrpc_handle z = -1;
	zrpc_network_cb cb;

	
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

	/*if data has been previously received for this zrpc server handle,
	 * the recbuf will have data in it resulting from that call.
	 * we need to add on to this data.
	 */
	if (zcon->recbuf[z])
	{/*try to realloc to add the size of the receive event*/
		if (!(zcon->recbuf[z] = realloc(zcon->recbuf[z], zcon->recbufsize[z] + ev->size)))
			return 1;
		/*memcpy because it isn't null terminated data
		 * pointer math ensures that we are adding right where we left off
		 */
		memcpy(zcon->recbuf[z]+zcon->recbufsize[z], ev->data, ev->size);
		/*increase recbufsize by the size of the event*/
		zcon->recbufsize[z] += ev->size;
	}
	/*if this is the first data receive call for a function, recbuf is null*/
	else
	{/*attempt to alloc size of event data*/
		if (!(zcon->recbuf[z] = calloc(ev->size+1, sizeof(char))))
			return 1;
		memcpy(zcon->recbuf[z], ev->data, ev->size);
		zcon->recbufsize[z] = ev->size;
	}
#ifdef XML_DEBUG
	printf("\n%s\n", zcon->recbuf[z]);
#endif

	/* strlen("</methodResponse>") = 17, hence 17 */
	if ((test = strstr(zcon->recbuf[z], "</methodResponse>")))
	{/*if methodresponse> is receieved, we have the full call*/
		if (test[17]) test[17] = 0; 	/*now we need to null terminate the string.
						* if the char* is big enough, we zero the correct char
						*/
		else
		{/*otherwise realloc by 1 for the null*/
			if (!(zcon->recbuf[z] = realloc(zcon->recbuf[z], zcon->recbufsize[z]+1)))
				return 1;
			zcon->recbufsize[z] += 1;
			zcon->recbuf[z][zcon->recbufsize[z]] = 0;
		}

		/*done with the server now, so we can call delete on it*/
		ecore_con_server_del(zcon->server[z]);
		zcon->server[z] = NULL;

		eina_stringshare_del(zcon->buf[z]);
		zcon->buf[z] = NULL;

		zcon->bufsize[z] = 0;
		zcon->recbufsize[z] = 0;

		if (zcon->call[z])
		{
			if (streq(zcon->call[z], "User.logout"))
			{
				eina_stringshare_del(zcon->zcookie);
				zcon->zcookie = NULL;
			}
			else if (streq(zcon->call[z], "User.login"))
			{
				test = strstr(zcon->recbuf[z], "sessid=");
				sscanf(test, "sessid=%[^;];", buf);
				zcon->zcookie = eina_stringshare_add(buf);
#ifdef DEBUG
printf("Cookie grabbed: %s\n", zcon->zcookie);
#endif
			}
			eina_stringshare_del(zcon->call[z]);
		}

		ret = eina_stringshare_add(zcon->recbuf[z]);
		free(zcon->recbuf[z]);
		zcon->recbuf[z] = NULL;
		
		/*if we get this far, we have a null terminated rpc response
		 * now we can use the zcon struct's callback if it exists
		 */
		if (zcon->cb[z])
		{
			if (!(cb = zcon->cb[z]))
			{
				printf("setting cb failed!\n");
				return 1;
			}
			/*run the cb, passing along the reply*/
			cb(zcon->cbd[z], ret);
		}

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
	int buffersize, x, *y, w;
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
	xml_newcall(doc, zcon->call[z]); //set up the doc with the methodcall
	if (zcon->params[z])
	{/*if the params aren't null*/
		EINA_LIST_FOREACH(zcon->params[z], l, s)
		/* use eina list for params to have uniform functions */
		{/*FIXME: add type checking for last couple calls*/
			if (isalnum((*(char*)s))) /*dereference char* to char and check for non-garbage*/
				xml_newstring(doc, (char*)s); /*must be string*/
			else /*otherwise int*/
			{
				y = (int*)s;
				w = 0;
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
							/*also check prev/next items in list for collision*/
							break;
					xml_newint(doc, y[w++]);
				}
			}
		}
	}
	//dumps the xmldoc into a a xmlChar* which is the same as a char*
	xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
	//copy to zcon struct and set bufsize
	zcon->buf[z] = eina_stringshare_add((char*)xmlbuff);
	zcon->bufsize[z] = eina_stringshare_strlen(zcon->buf[z]);

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

static void _collector(void *data, const char *reply)
{
	zrpc_meta_struct *meta = data;
	int it = 0, numusers = meta->num;
	static int count;
	zrpc_user *user;
	const char *y;
	xmlNode *r;
	double timer;
	zrpc_con *zcon;
	static Eina_List *users;

	if (count++ == 0) it = 1;

	if (!(zcon = meta->zcon)) return;

	y = eina_stringshare_add(strchr(reply, '<'));
	eina_stringshare_del(reply);
	r = parsechar(y);

	user = parseuser(r);

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

	meta->cb(meta, NULL);
}

static void _getusers(void *data, const char *reply)
{
	zrpc_meta_struct *meta = data;
	zrpc_con *zcon;
	const char *y;
	xmlNode *r;
	int *users, it, numusers = 0;

	if (!(zcon = meta->zcon)) return;

	/*parsing*/
	y = eina_stringshare_add(strchr(reply, '<'));
	eina_stringshare_del(reply);
	r = parsechar(y);
	users = parseusers(r);

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
	zrpc_meta_struct *x = new_zmeta();
	x->cb = cb;
	x->zcon = zcon;
	x->cbd = cbd;

	if (!zrpc_User_getUsers(zcon, _getusers, x))
		return 0;
		
	return 1;
}
