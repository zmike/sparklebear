/*zrpc efl c bindings xml functions
 *2010 Mike Blumenkrantz*/

#include "zrpc.h"
#include "xml.h"

/* always use this when checking node->next or node->children
 * to avoid random XML_TEXT_NODEs from formatting
 * failure to do so will result in unexpected parsing errors
 */
inline xmlNode *
xml_safenext(xmlNode *node)
{
	xmlNode *node2 = node;
	if (!node2)
		return NULL;
	else if (xmlNodeIsText(node2))
		return node2->next;
	return node2;
}

/*parses a generic int response*/
int
xml_parse_int(xmlNode *node)
{
	xmlNode *node2 = NULL;
	int ret;

    	for (node2 = node; node2; node2 = xml_safenext(node2->children))
		if ((!strcmp((char*)node2->name, "boolean")) || (!strcmp((char*)node2->name, "int")))
		{
			ret = atoi((char*)(node2->children->content));
			node2 = NULL;
			xmlFreeNode(node);
			return ret;
		}

	/* dunno how it would get here */
	return -1;
}

int *
xml_parse_users(xmlNode *node)
{
	xmlNode *node2, *node3;
	char *value = 0;
	int *users, usercount = 0;


	node2 = node;
	if (!strcmp((char*)node2->name, "methodResponse"))
		while (strcmp((char*)node2->name, "data"))
		{
			/* seek to start of user array */
			node2 = xml_safenext(node2->children);
		}
	/*descend into the array members*/
	node2 = xml_safenext(node2->children);

	node3 = node2;

	while (node3)
	{/*count the number of uids returned*/
		usercount++;
		node3 = xml_safenext(node3->next);
	}

	if (!(users = calloc(usercount + 1, sizeof(int))))
		return 0;
	usercount = 0;
	while (node2)
	{
		node3 = xml_safenext(node2->children);
		value = (char*)node3->children->content;
		users[usercount++] = atoi(value);

		node2 = xml_safenext(node2->next);
	}
        users[usercount] = -1;
	node2 = node3 = NULL;
	if (!strcmp((char*)node->name, "methodResponse"))
		xmlFreeNode(node);

	return users;
}

zrpc_user *
xml_parse_user(xmlNode *node)
{
	xmlNode *node2, *node3, *seek;
	char *name, *value = 0, *null = "NULL";
	zrpc_user *user = zuser_new();


	node2 = node;
	if (!strcmp((char*)node2->name, "methodResponse"))
		while (strcmp((char*)node2->name, "struct"))
		{
			/* seek to start of user struct */
			node2 = xml_safenext(node2->children);
		}
	/*descend into the struct members*/
	node2 = xml_safenext(node2->children);

	while (node2)
	{
		node3 = xml_safenext(node2->children);

		name = (char*)node3->children->content;

		seek = xml_safenext(node3->next);
		seek = xml_safenext(seek->children);
		if (!seek->children)
			value = null;
		else
			value = (char*)seek->children->content;

		if (!strcmp(name, "uid"))
			user->uid = atoi(value);
		else if (!strcmp(name, "name"))
			user->name = eina_stringshare_add(value);
		else if (!strcmp(name, "email"))
			user->email = eina_stringshare_add(value);
		else if (!strcmp(name, "active"))
			user->active = atoi(value);
		else if (!strcmp(name, "type"))
			user->type = atoi(value);
		else if (!strcmp(name, "language"))
			user->language = eina_stringshare_add(value);

		node2 = xml_safenext(node2->next);
	}
	node2 = node3 = seek = NULL;
	if (!strcmp((char*)node->name, "methodResponse"))
		xmlFreeNode(node);

	return user;
}

/*parses an xml vm node into a vm struct*/
zrpc_vm *
xml_parse_vm(xmlNode *node)
{
	xmlNode *node2, *node3, *node4, *seek, *seek2;
	char *name, *value = 0, *value2 = 0, *null = "NULL";
	zrpc_vm *vm = zvm_new();
	zrpc_vif *vif;
	zrpc_disk *disk;


	node2 = node;
	if (!strcmp((char*)node2->name, "methodResponse"))
		while (strcmp((char*)node2->name, "struct"))
		{
			/* seek to start of vm struct */
			node2 = xml_safenext(node2->children);
		}
	/*descend into the struct members*/
	node2 = xml_safenext(node2->children);

	while (node2)
	{
		node3 = xml_safenext(node2->children);

		name = (char*)node3->children->content;

		seek = xml_safenext(node3->next);
		seek = xml_safenext(seek->children);
		if (!seek->children)
			value = null;
		else
			value = (char*)seek->children->content;


		if (!strcmp(name, "name"))
			vm->name = eina_stringshare_add(value);
		else if (!strcmp(name, "uuid"))
			vm->uuid = eina_stringshare_add(value);
		else if (!strcmp(name, "puuid"))
			vm->puuid = eina_stringshare_add(value);
		else if (!strcmp(name, "type"))
			vm->type = eina_stringshare_add(value);
		else if (!strcmp(name, "os"))
			vm->os = eina_stringshare_add(value);
		else if (!strcmp(name, "id"))
			vm->id = atoi(value);
		else if (!strcmp(name, "kernel"))
			vm->kernel = eina_stringshare_add(value);
		else if (!strcmp(name, "ramdisk"))
			vm->ramdisk = eina_stringshare_add(value);
		else if (!strcmp(name, "cmdline"))
			vm->cmdline = eina_stringshare_add(value);
		else if (!strcmp(name, "on_reboot"))
			vm->on_reboot = eina_stringshare_add(value);
		else if (!strcmp(name, "on_poweroff"))
			vm->on_poweroff = eina_stringshare_add(value);
		else if (!strcmp(name, "on_crash"))
			vm->on_crash = eina_stringshare_add(value);
		else if (!strcmp(name, "mem"))
			vm->mem = atoi(value);
		else if (!strcmp(name, "maxmem"))
			vm->maxmem = atoi(value);
		else if (!strcmp(name, "vcpus"))
			vm->vcpus = atoi(value);
		else if (!strcmp(name, "cpupct"))
			vm->cpupct = atof(value);
		else if (!strcmp(name, "cputime"))
			vm->cputime = atof(value);
		else if (!strcmp(name, "uptime"))
			vm->uptime = atoi(value);
		else if (!strcmp(name, "vncport"))
			vm->vncport = atoi(value);
		else if (!strcmp(name, "vncpasswd"))
			vm->vncpasswd = eina_stringshare_add(value);
		else if (!strcmp(name, "state"))
			vm->state = eina_stringshare_add(value);
		else if (!strcmp(name, "numvbds"))
			vm->numvbds = atoi(value);
		else if (!strcmp(name, "disks"))
		{
			node3 = xml_safenext(node3->next);

			/* seek to disk array */
			while (strcmp((char*)node3->name, "data"))
				node3 = xml_safenext(node3->children);

			if (!(node3 = xml_safenext(node3->children)))
			{
				node2 = xml_safenext(node2->next);
				continue;
			}

			while (node3)
			{
				disk = zdisk_new();

				/* seek to first member */
				node4 = xml_safenext(node3->children);
				node4 = xml_safenext(node4->children);

				while (node4)
				{
					seek = xml_safenext(node4->children);

					name = (char*)seek->children->content;

					seek2 = xml_safenext(seek->next);
					seek2 = xml_safenext(seek2->children);
					if (!seek2->children)
						value2 = null;
					else
						value2 = (char*)seek2->children->content;


					if (!strcmp(name, "int_dev"))
						disk->int_dev = eina_stringshare_add(value2);
					else if (!strcmp(name, "ext_dev"))
						disk->ext_dev = eina_stringshare_add(value2);
					else if (!strcmp(name, "mode"))
						disk->mode = eina_stringshare_add(value2);
					else if (!strcmp(name, "type"))
						disk->type = eina_stringshare_add(value2);
					else if (!strcmp(name, "ooreq"))
						disk->ooreq = atoi(value2);
					else if (!strcmp(name, "rdreq"))
						disk->rdreq = atoi(value2);
					else if (!strcmp(name, "wrreq"))
						disk->wrreq = atoi(value2);
					else if (!strcmp(name, "num_sectors"))
						disk->num_sectors = atoi(value2);
					else if (!strcmp(name, "size_sector"))
						disk->size_sector = atoi(value2);
					else if (!strcmp(name, "partition_type"))
						disk->partition_type = eina_stringshare_add(value2);
					else if (!strcmp(name, "start_sector"))
						disk->start_sector = atoi(value2);
					else if (!strcmp(name, "block_size"))
						disk->block_size = atoi(value2);
					else if (!strcmp(name, "free"))
						disk->free = atoi(value2);
					else if (!strcmp(name, "mapped_dev"))
						disk->mapped_dev = eina_stringshare_add(value2);

					node4 = xml_safenext(node4->next);
				}
				vm->disks = eina_list_append(vm->disks, disk);
				node3 = xml_safenext(node3->next);
			}

		}
		else if (!strcmp(name, "numnets"))
			vm->numnets = atoi(value);
		else if (!strcmp(name, "rxbw"))
			vm->rxbw = atoi(value);
		else if (!strcmp(name, "txbw"))
			vm->txbw = atoi(value);
		else if (!strcmp(name, "vifs"))
		{
			node3 = xml_safenext(node3->next);

			/* seek to vif array */
			while (strcmp((char*)node3->name, "data"))
				node3 = xml_safenext(node3->children);

			if (!(node3 = xml_safenext(node3->children)))
			{
				node2 = xml_safenext(node2->next);
				continue;
			}

			while (node3)
			{
				vif = zvif_new();

				/* seek to first member */
				node4 = xml_safenext(node3->children);
				node4 = xml_safenext(node4->children);
				while (node4)
				{
					seek = xml_safenext(node4->children);

					name = (char*)seek->children->content;

					seek2 = xml_safenext(seek->next);
					seek2 = xml_safenext(seek2->children);
					if (!seek2->children)
						value2 = null;
					else
						value2 = (char*)seek2->children->content;


					if (!strcmp(name, "name"))
						vif->name = eina_stringshare_add(value2);
					else if (!strcmp(name, "mac"))
						vif->mac = eina_stringshare_add(value2);
					else if (!strcmp(name, "bridge"))
						vif->bridge = eina_stringshare_add(value2);
					else if (!strcmp(name, "script"))
						vif->script = eina_stringshare_add(value2);
					else if (!strcmp(name, "type"))
						vif->type = eina_stringshare_add(value2);
					else if (!strcmp(name, "loopback"))
						vif->loopback = *(Eina_Bool*)value2;
					else if (!strcmp(name, "connected"))
						vif->connected = *(Eina_Bool*)value2;
					else if (!strcmp(name, "promisc"))
						vif->promisc = *(Eina_Bool*)value2;
					else if (!strcmp(name, "ip"))
						vif->ip = eina_stringshare_add(value2);
					else if (!strcmp(name, "netmask"))
						vif->netmask = eina_stringshare_add(value2);
					else if (!strcmp(name, "gateway"))
						vif->gateway = eina_stringshare_add(value2);
					else if (!strcmp(name, "broadcast"))
						vif->broadcast = eina_stringshare_add(value2);
					else if (!strcmp(name, "mtu"))
						vif->mtu = atoi(value2);
					else if (!strcmp(name, "txpackets"))
						vif->txpackets = atof(value2);
					else if (!strcmp(name, "txbytes"))
						vif->txbytes = atof(value2);
					else if (!strcmp(name, "txdrop"))
						vif->txdrop = atof(value2);
					else if (!strcmp(name, "txerr"))
						vif->txerr = atof(value2);
					else if (!strcmp(name, "rxpackets"))
						vif->rxpackets = atof(value2);
					else if (!strcmp(name, "rxbytes"))
						vif->rxbytes = atof(value2);
					else if (!strcmp(name, "rxdrop"))
						vif->rxdrop = atof(value2);
					else if (!strcmp(name, "rxerr"))
						vif->rxerr = atof(value2);
					else if (!strcmp(name, "collisions"))
						vif->collisions = atof(value2);
					node4 = xml_safenext(node4->next);
				}
				vm->vifs = eina_list_append(vm->vifs, vif);
				node3 = xml_safenext(node3->next);

			}
		}
		node2 = xml_safenext(node2->next);
	}
	node2 = node3 = node4 = seek = seek2 = NULL;
	if (!strcmp((char*)node->name, "methodResponse"))
		xmlFreeNode(node);

	return vm;
}

/*I think this function is dumb.
checks list of vms for a vm, updates the item if found, adds if not found
Eina_List *
updatevmsfull(Eina_List *vms, zrpc_vm *vm)
{
	if (!vm) return vms;
	Eina_List *l, *l2;
	zrpc_vm *v;
	#ifdef DEBUG
	printf("DEBUG: Checking against existing vms...\n");
	#endif
	EINA_LIST_FOREACH_SAFE(vms, l, l2, v)
	{
		if (!v) continue;
	#ifdef DEBUG

	printf("\tDEBUG: Checking vm %s\n", v->uuid);
	#endif
		if (!strcmp(vm->uuid, v->uuid))
		{
			#ifdef DEBUG
			printf("\t\tDEBUG: Match found with %s! Updating...\n", v->uuid);
			#endif
			vms = eina_list_append(vms, vm);
			vms = eina_list_remove_list(vms, l);
			zvm_free(v);
			v = NULL;
			return vms;
		}
		#ifdef DEBUG
		else
			printf("\t\tDEBUG: Not a match!\n");
		#endif
	}
	#ifdef DEBUG
	printf("DEBUG: Checking against updated vm list...\n");
	#endif
	if (!eina_list_data_find(vms, vm))
	{
		#ifdef DEBUG
		printf("DEBUG: Not found!  Adding to list.\n");
		#endif
		vms = eina_list_append(vms, vm);
	}

	return vms;

}
*/


/*parses getVMsFull
 * requires current list of vms (or null if nonexistent)
 * so it can update old data if it exists
 */
Eina_List *
xml_parse_vmsfull(xmlNode *node)
{
	xmlNode *node2, *node3;
//	void *t = NULL;
	zrpc_vm *vm;
	Eina_List *tmp = NULL;
        double time;


#ifdef DEBUG
        time = ecore_time_get();
#endif
//	if (!(t = eina_list_data_get(vms))) vms = NULL;

	node2 = xml_safenext(node->children);

	while (node2)
	{
		/* seek to start of array */
		if (strcmp((char*)node2->parent->name, "data"))
			node2 = xml_safenext(node2->children);
		else
		{
			/* send the actual vm struct */
			node3 = xml_safenext(node2->children);
			vm = NULL;
			if (!(vm = xml_parse_vm(node3)))
			{
				fprintf(stderr, "No vm parsed\n");
				node2 = xml_safenext(node2->next);
				continue;
			}
			#ifdef DEBUG
			printf("DEBUG: Received vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
			#endif
			tmp = eina_list_append(tmp, vm);
			/*if (vms) vms = updatevmsfull(vms, vm);
			else
			{
				#ifdef DEBUG
				printf("DEBUG: Not found!  Adding to list.\n");
				#endif
				vms = eina_list_append(vms, vm);
			}
			if (vms)
				EINA_LIST_FREE(vms, vm)
					zvm_free(vm);*/
			/* neeeext */
			node2 = xml_safenext(node2->next);

		}


	}

	node2 = node3 = NULL;
	xmlFreeNode(node);

#ifdef DEBUG
        printf("DEBUG: getvmsfull parsing completed in %f seconds!\n", ecore_time_get() - time);
#endif

	return tmp;
}

/*simple function to turn xml response into a parseable xml node*/
xmlNode *
xml_parse_xml(const char *charxml)
{
	const char *xml;
	xmlDocPtr doc;
	xmlNode *root, *root2;

        if (!charxml || !strlen(charxml)) return NULL;
        if (strstr(charxml, "faultCode") && strstr(charxml, "faultString"))
                return NULL;

        xml = strchr(charxml, '<');
	if (!(doc = xmlParseMemory(xml, strlen(xml))))
		return NULL;

	if (!(root = xmlDocGetRootElement(doc)))
		return NULL;

	root2 = xmlCopyNodeList(root);

	xmlFreeDoc(doc);

	return root2;
}


//adds params up through "params" to a new rpc
void
xml_new_call(xmlDocPtr doc, const char *method)
{
	xmlNodePtr methodcall, methodname, params;

	methodcall = xmlNewNode(NULL, BAD_CAST "methodCall");
	xmlDocSetRootElement(doc, methodcall);
	methodname = xmlNewChild(methodcall, NULL, BAD_CAST "methodName", BAD_CAST method);
	params = xmlNewChild(methodcall, NULL, BAD_CAST "params", NULL);

}

//adds a new string param
void
xml_new_string(xmlDocPtr doc, const char *string)
{
	xmlNodePtr node, node2, p, v, s;

	node = xmlDocGetRootElement(doc); //methodCall
    	for (node2 = node; node2; node2 = node2->children->next)
		if (!strcmp((char*)node2->name, "params"))
		{
			p = xmlNewChild(node2, NULL, BAD_CAST "param", NULL);
			v = xmlNewChild(p, NULL, BAD_CAST "value", NULL);
			s = xmlNewChild(v, NULL, BAD_CAST "string", BAD_CAST string);
			break;
		}

}

//adds a new int param
void
xml_new_int(xmlDocPtr doc, int i, int array)
{
	xmlNodePtr node, node2, p, v, s;
	char i2[13];

	eina_convert_itoa(i, i2);
	node = xmlDocGetRootElement(doc); //methodCall
    	for (node2 = node; node2; node2 = node2->children->next)
		if (!strcmp((char*)node2->name, (array) ? "data" : "params"))
		{
			p = (array) ? node2 : xmlNewChild(node2, NULL, BAD_CAST "param", NULL);
			v = xmlNewChild(p, NULL, BAD_CAST "value", NULL);
			s = xmlNewChild(v, NULL, BAD_CAST "int", BAD_CAST i2);
			break;
		}

}

void
xml_new_array(xmlDocPtr doc)
{
	xmlNodePtr node, node2, p, v, a, d;

	node = xmlDocGetRootElement(doc); //methodCall
    	for (node2 = node; node2; node2 = node2->children->next)
		if (!strcmp((char*)node2->name, "params"))
		{
			p = xmlNewChild(node2, NULL, BAD_CAST "param", NULL);
			v = xmlNewChild(p, NULL, BAD_CAST "value", NULL);
			a = xmlNewChild(v, NULL, BAD_CAST "array", NULL);
			d = xmlNewChild(a, NULL, BAD_CAST "data", NULL);
			break;
		}
}
