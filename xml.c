/*zrpc efl c bindings xml functions
 *2010 Mike Blumenkrantz*/

#include <libxml/parser.h>
#include <libxml/tree.h>

/* always use this when checking node->next or node->children
 * to avoid random XML_TEXT_NODEs from formatting
 * failure to do so will result in unexpected parsing errors
 */
xmlNode *xml_safenext(xmlNode *node)
{
	xmlNode *node2 = node;
	if (!node2)
		return NULL;
	else if (xmlNodeIsText(node2))
		return node2->next;
	return node2;
}

/*parses a generic int response*/
int parseint(xmlNode *node)
{
	xmlNode *node2 = NULL;
	int ret;

    	for (node2 = node; node2; node2 = xml_safenext(node2->children))
		if ((streq((char*)node2->name, "boolean")) || (streq((char*)node2->name, "int")))
		{
			ret = atoi((char*)(node2->children->content));
			node2 = NULL;
			xmlFreeNode(node);
			return ret;
		}
		
	/* dunno how it would get here */
	return -1;
}

int *parseusers(xmlNode *node)
{
	xmlNode *node2, *node3;
	char *value = 0;
	int *users, usercount = 0;


	node2 = node;
	if (streq((char*)node2->name, "methodResponse"))
		while (!streq((char*)node2->name, "data"))
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

	if (!(users = calloc(usercount, sizeof(int))))
		return 0;
	usercount = 0;
	while (node2)
	{
		node3 = xml_safenext(node2->children);
		value = (char*)node3->children->content;
		users[usercount++] = atoi(value);

		node2 = xml_safenext(node2->next);
	}
	node2 = node3 = NULL;
	if (streq((char*)node->name, "methodResponse"))
		xmlFreeNode(node);

	return users;
}

zrpc_user *parseuser(xmlNode *node)
{
	xmlNode *node2, *node3, *seek;
	char *name, *value = 0, *null = "NULL";
	zrpc_user *user = new_zuser();


	node2 = node;
	if (streq((char*)node2->name, "methodResponse"))
		while (!streq((char*)node2->name, "struct"))
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

		if (streq(name, "uid"))
			user->uid = atoi(value);
		else if (streq(name, "name"))
			user->name = strdup(value);
		else if (streq(name, "email"))
			user->email = strdup(value);
		else if (streq(name, "active"))
			user->active = atoi(value);
		else if (streq(name, "type"))
			user->type = atoi(value);
		else if (streq(name, "language"))
			user->language = strdup(value);

		node2 = xml_safenext(node2->next);
	}
	node2 = node3 = seek = NULL;
	if (streq((char*)node->name, "methodResponse"))
		xmlFreeNode(node);

	return user;
}

/*parses an xml vm node into a vm struct*/
zrpc_vm *parsevm(xmlNode *node)
{
	xmlNode *node2, *node3, *node4, *seek, *seek2;
	char *name, *value = 0, *value2 = 0, *null = "NULL";
	zrpc_vm *vm = new_zvm();
	zrpc_vif *vif;
	zrpc_disk *disk;


	node2 = node;
	if (streq((char*)node2->name, "methodResponse"))
		while (!streq((char*)node2->name, "struct"))
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

		
		if (streq(name, "name"))
			vm->name = strdup(value);
		else if (streq(name, "uuid"))
			vm->uuid = strdup(value);
		else if (streq(name, "puuid"))
			vm->puuid = strdup(value);
		else if (streq(name, "type"))
			vm->type = strdup(value);
		else if (streq(name, "os"))
			vm->os = strdup(value);
		else if (streq(name, "id"))
			vm->id = atoi(value);
		else if (streq(name, "kernel"))
			vm->kernel = strdup(value);
		else if (streq(name, "ramdisk"))
			vm->ramdisk = strdup(value);
		else if (streq(name, "cmdline"))
			vm->cmdline = strdup(value);
		else if (streq(name, "on_reboot"))
			vm->on_reboot = strdup(value);
		else if (streq(name, "on_poweroff"))
			vm->on_poweroff = strdup(value);
		else if (streq(name, "on_crash"))
			vm->on_crash = strdup(value);
		else if (streq(name, "mem"))
			vm->mem = atoi(value);
		else if (streq(name, "maxmem"))
			vm->maxmem = atoi(value);
		else if (streq(name, "vcpus"))
			vm->vcpus = atoi(value);
		else if (streq(name, "cpupct"))
			vm->cpupct = atof(value);
		else if (streq(name, "cputime"))
			vm->cputime = atof(value);
		else if (streq(name, "uptime"))
			vm->uptime = atoi(value);
		else if (streq(name, "vncport"))
			vm->vncport = atoi(value);
		else if (streq(name, "vncpasswd"))
			vm->vncpasswd = strdup(value);
		else if (streq(name, "state"))
			vm->state = strdup(value);
		else if (streq(name, "numvbds"))
			vm->numvbds = atoi(value);
		else if (streq(name, "disks"))
		{
			node3 = xml_safenext(node3->next);
			
			/* seek to disk array */
			while (!streq((char*)node3->name, "data"))
				node3 = xml_safenext(node3->children);
			
			if (!(node3 = xml_safenext(node3->children)))
			{
				node2 = xml_safenext(node2->next);
				continue;
			}
				
			while (node3)
			{
				disk = new_zdisk();

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

					
					if (streq(name, "int_dev"))
						disk->int_dev = strdup(value2);
					else if (streq(name, "ext_dev"))
						disk->ext_dev = strdup(value2);
					else if (streq(name, "mode"))
						disk->mode = strdup(value2);
					else if (streq(name, "type"))
						disk->type = strdup(value2);
					else if (streq(name, "ooreq"))
						disk->ooreq = atoi(value2);
					else if (streq(name, "rdreq"))
						disk->rdreq = atoi(value2);
					else if (streq(name, "wrreq"))
						disk->wrreq = atoi(value2);
					else if (streq(name, "num_sectors"))
						disk->num_sectors = atoi(value2);
					else if (streq(name, "size_sector"))
						disk->size_sector = atoi(value2);
					else if (streq(name, "partition_type"))
						disk->partition_type = strdup(value2);
					else if (streq(name, "start_sector"))
						disk->start_sector = atoi(value2);
					else if (streq(name, "block_size"))
						disk->block_size = atoi(value2);
					else if (streq(name, "free"))
						disk->free = atoi(value2);
					else if (streq(name, "mapped_dev"))
						disk->mapped_dev = strdup(value2);
						
					node4 = xml_safenext(node4->next);
				}
				vm->disks = eina_list_append(vm->disks, disk);
				node3 = xml_safenext(node3->next);
			}

		}	
		else if (streq(name, "numnets"))
			vm->numnets = atoi(value);
		else if (streq(name, "rxbw"))
			vm->rxbw = atoi(value);
		else if (streq(name, "txbw"))
			vm->txbw = atoi(value);
		else if (streq(name, "vifs"))
		{
			node3 = xml_safenext(node3->next);
						
			/* seek to vif array */
			while (!streq((char*)node3->name, "data"))
				node3 = xml_safenext(node3->children);
			
			if (!(node3 = xml_safenext(node3->children)))
			{
				node2 = xml_safenext(node2->next);
				continue;
			}
			
			while (node3)
			{
				vif = new_zvif();
				
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


					if (streq(name, "name"))
						vif->name = strdup(value2);
					else if (streq(name, "mac"))
						vif->mac = strdup(value2);
					else if (streq(name, "bridge"))
						vif->bridge = strdup(value2);
					else if (streq(name, "script"))
						vif->script = strdup(value2);
					else if (streq(name, "type"))
						vif->type = strdup(value2);
					else if (streq(name, "loopback"))
						vif->loopback = *(Eina_Bool*)value2;
					else if (streq(name, "connected"))
						vif->connected = *(Eina_Bool*)value2;
					else if (streq(name, "promisc"))
						vif->promisc = *(Eina_Bool*)value2;
					else if (streq(name, "ip"))
						vif->ip = strdup(value2);
					else if (streq(name, "netmask"))
						vif->netmask = strdup(value2);
					else if (streq(name, "gateway"))
						vif->gateway = strdup(value2);
					else if (streq(name, "broadcast"))
						vif->broadcast = strdup(value2);
					else if (streq(name, "mtu"))
						vif->mtu = atoi(value2);
					else if (streq(name, "txpackets"))
						vif->txpackets = atof(value2);
					else if (streq(name, "txbytes"))
						vif->txbytes = atof(value2);
					else if (streq(name, "txdrop"))
						vif->txdrop = atof(value2);
					else if (streq(name, "txerr"))
						vif->txerr = atof(value2);
					else if (streq(name, "rxpackets"))
						vif->rxpackets = atof(value2);
					else if (streq(name, "rxbytes"))
						vif->rxbytes = atof(value2);
					else if (streq(name, "rxdrop"))
						vif->rxdrop = atof(value2);
					else if (streq(name, "rxerr"))
						vif->rxerr = atof(value2);
					else if (streq(name, "collisions"))
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
	if (streq((char*)node->name, "methodResponse"))
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
		if (streq(vm->uuid, v->uuid))
		{
			#ifdef DEBUG
			printf("\t\tDEBUG: Match found with %s! Updating...\n", v->uuid);
			#endif
			vms = eina_list_append(vms, vm);
			vms = eina_list_remove_list(vms, l);
			free_zvm(v);
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
Eina_List *parsevmsfull(xmlNode *node)
{
	xmlNode *node2, *node3;
//	void *t = NULL;
	zrpc_vm *vm;
	Eina_List *tmp = NULL;

//	if (!(t = eina_list_data_get(vms))) vms = NULL;
	
	node2 = xml_safenext(node->children);
	
	while (node2)
	{
		/* seek to start of array */
		if (!streq((char*)node2->parent->name, "data"))
			node2 = xml_safenext(node2->children);
		else
		{
			/* send the actual vm struct */
			node3 = xml_safenext(node2->children);
			vm = NULL;
			if (!(vm = parsevm(node3)))
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
					free_zvm(vm);*/
			/* neeeext */
			node2 = xml_safenext(node2->next);

		}

		
	}

	node2 = node3 = NULL;
	xmlFreeNode(node);


	return tmp;	
}

/*simple function to turn xml response into a parseable xml node*/
xmlNode *parsechar(char *charxml)
{
	char *xml;
	xmlDocPtr doc;
	xmlNode *root, *root2;

	xml = (char*)xmlCharStrdup(charxml);
	if ((doc = xmlParseMemory(xml, strlen((char*)xml))) == NULL)
		return EINA_FALSE;

	if ((root = xmlDocGetRootElement(doc)) == NULL)
		return EINA_FALSE;

	root2 = xmlCopyNodeList(root);

	free(xml);
	free(charxml);
	xmlFreeDoc(doc);

	return root2;

}


//adds params up through "params" to a new rpc
void xml_newcall(xmlDocPtr doc, const char *method)
{
	xmlNodePtr methodcall, methodname, params;
	methodcall = xmlNewNode(NULL, BAD_CAST "methodCall");
	xmlDocSetRootElement(doc, methodcall);
	methodname = xmlNewChild(methodcall, NULL, BAD_CAST "methodName", BAD_CAST method);
	params = xmlNewChild(methodcall, NULL, BAD_CAST "params", NULL);

}

//adds a new string param
void xml_newstring(xmlDocPtr doc, const char *string)
{
	xmlNodePtr node, node2, p, v, s;
	node = xmlDocGetRootElement(doc); //methodCall
    	for (node2 = node; node2; node2 = node2->children->next)
		if (streq((char*)node2->name, "params"))
		{
			p = xmlNewChild(node2, NULL, BAD_CAST "param", NULL);
			v = xmlNewChild(p, NULL, BAD_CAST "value", NULL);
			s = xmlNewChild(v, NULL, BAD_CAST "string", BAD_CAST string);
			break;
		}

}

//adds a new int param
void xml_newint(xmlDocPtr doc, int i)
{
	xmlNodePtr node, node2, p, v, s;
	char *i2;

	i2 = itoa(i); //must be freed
	node = xmlDocGetRootElement(doc); //methodCall
    	for (node2 = node; node2; node2 = node2->children->next)
		if (streq((char*)node2->name, "params"))
		{
			p = xmlNewChild(node2, NULL, BAD_CAST "param", NULL);
			v = xmlNewChild(p, NULL, BAD_CAST "value", NULL);
			s = xmlNewChild(v, NULL, BAD_CAST "int", BAD_CAST i2);
			break;
		}
	free(i2);

}
