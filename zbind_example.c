/* demo app for zrpc c bindings
 * 2010 Mike Blumenkrantz
 *
 * It's worth noting that all the zrpc functions return 1 on successful setup,
 * so error checking is possible.  I choose not to here because it's pedantic and tedious.
 */

//#define DEBUG 1 /*enables some general parsing debug info*/
//#define XML_DEBUG 1/*shows full rpc call send/receive*/
#include <stdio.h>
#include "zrpc.h"
#include "zrpc.c"

/*after logout completes*/
void cleanup(zrpc_con *zcon, const char *reply)
{
	xmlNode *r;

	if ((r = xml_parse_xml(reply)) && (xml_parse_int(r)))
		printf("Logout successful!\n");
	else printf("Logout failed!\n");

	ecore_main_loop_quit();
	exit(0);
}

void print_uinfos(const char *reply, void *data)
{
	zrpc_meta_struct *meta;
	zrpc_con *zcon;
	Eina_List *users, *l;
	zrpc_user *user;

	meta = data;
	zcon = meta->cbd;
	users = meta->extra;

	EINA_LIST_FOREACH(users, l, user)
		printf("Name: %s\nUID: %d\nLanguage: %s\n", user->name, user->uid, user->language);

	EINA_LIST_FREE(users, user)
		zuser_free(user);

	/*passing a callback for logout isn't really necessary, but why not*/
	zrpc_User_logout(zcon, (void*)cleanup, zcon);
}

/*second callback, parses getVMsFull*/
void print_infos(zrpc_con *zcon, const char *reply)
{
	/*seek to the xml data*/
	Eina_List *vms, *l;
	zrpc_vm *vm;
	xmlNode *r;

	/*parse the shit out of it*/
	if (!(r = xml_parse_xml(reply)))
                printf("Error with reply!\n");
	vms = xml_parse_vmsfull(r);
	/*print out some stats to prove the data was grabbed*/
	EINA_LIST_FOREACH(vms, l, vm)
		printf("\n********\n\nUUID: %s\nName: %s\nOS: %s\nUptime: %d\n", vm->uuid, vm->name, vm->os, vm->uptime);

	/*free the vm list*/
	EINA_LIST_FREE(vms, vm)
		zvm_free(vm);


	meta_getUsersFull(zcon, (void*)print_uinfos, zcon);
}

/*the first callback, called after login response has been received*/
void post(zrpc_con *zcon, const char *reply)
{/*parameters are a zcon handle, and the handle number*/
	xmlNode *r;

	/* char* -> xmlNode */
	if (!(r = xml_parse_xml(reply)))
                printf("Error with reply!\n");
	/*xml_parse_int handles int and boolean tags and returns the value.
	 *all parse functions free the node passed to them
	 */
	if (xml_parse_int(r)) /*if login succeeded*/
		zrpc_VM_getVMsFull(zcon, (void*)print_infos, zcon);
	else
	{
		printf("Login failed!\n");
		exit(0);
	}
}

int main()
{
	eina_init();
	ecore_con_init();

	/*no new function because there's no free function*/
	static zrpc_con zcon;
	/*set up host/port*/
//	zcon.host = "www.domain.com";
//	zcon.port = 4444;
	zcon.host = "10.10.10.6";
	zcon.port = 65534;

//	char *username = "someuser";
//	char *password = "somepassword";
	char *username = "admin";
	char *password = "sparklebear";

	/*all zrpc functions take a minimum of 3 arguments:
	 * 1) a zcon handle
	 * 2) a zrpc_network_cb function
	 * 3) a (void*) to pass to the callback
	 */
	zrpc_User_login(username, password, &zcon, (void*)post, &zcon);

	/*start the ecore job server*/
	ecore_main_loop_begin();
	return 0;
}
