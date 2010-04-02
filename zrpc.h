/*zrpc efl c bindings
 * Mike Blumenkrantz 2010
 */

#ifndef ZRPC_H
#define ZRPC_H

/*for zrpc_user->type*/
#define USER_LEVEL_MIN 0
#define USER_LEVEL_MAX 5

#define streq(s1, s2) (strcmp((s1), (s2)) ==0)
#include <Eina.h>
#include <Ecore_Con.h>
#include <Ecore.h>
#include <ctype.h>

typedef int zrpc_handle;
/*generic callback for every function call*/
typedef void (*zrpc_network_cb)(void *, const char*);

/*generic itoa*/
const char *itoa(int x)
{
        char y[13];
        sprintf(y, "%d", x);
        return eina_stringshare_add(y);
}

/*struct used to initiate a zrpc call*/
typedef struct _zrpc_con
{
	Ecore_Con_Server *server[100];
	Ecore_Event_Handler *add;
	Ecore_Event_Handler *del;
	Ecore_Event_Handler *data;

	char *host;
	char *rpc_path;
	char *host_header;
	int port;

	/*use list for params to keep functions uniform*/
	Eina_List *params[100];
	const char *buf[100], /*send buffer*/
	*call[100], 	/*rpc call name*/
	*zcookie; /*session cookie from login*/
	int bufsize[100], recbufsize[100];
	char *recbuf[100]; /*receive buffer*/

	/*this determines what should be done with the return data
	 * almost definitely should not be null
	 * */
	zrpc_network_cb cb[100];
	/*data sent to callback*/
	void 		*cbd[100];

} zrpc_con;

typedef struct _zrpc_meta_struct {
	zrpc_network_cb cb;
	zrpc_con *zcon;
	void *cbd;
	void *extra;
	int num;
} zrpc_meta_struct;

zrpc_meta_struct *new_zmeta()
{
	zrpc_meta_struct *new;
	if (!(new = calloc(1, sizeof(zrpc_meta_struct))))
		return NULL;

	new->cb = NULL;
	new->zcon = NULL;
	new->cbd = NULL;
	new->extra = NULL;

	return new;
}

typedef struct _zrpc_plugin {
	char *name;
	char *description;
	Eina_Bool frontend;
	Eina_Bool xmlrpc;
	Eina_Bool scheduler;
	Eina_Bool poller;
	Eina_Bool enabled;
} zrpc_plugin;

typedef struct _zrpc_log {
	char *timestamp;
	int severity;
	int uid;
	char *message;
} zrpc_log;

typedef struct _zrpc_bridge { 
	int id;
	char *name;
	char *node;
	char *description;
	char *interface;
	char *ip;
	char *netmask;
	char *broadcast;
	int vlans[];
} zrpc_bridge;

typedef struct _zrpc_disk {
	const char *int_dev;
	const char *ext_dev;
	const char *mode;
	const char *type;
	int ooreq;
	int rdreq;
	int wrreq;
	int num_sectors;
	int size_sector;
	const char *partition_type;
	int start_sector;
	int block_size;
	int free;
	const char *mapped_dev;
} zrpc_disk;

zrpc_disk *new_zdisk()
{
	zrpc_disk *new = NULL;
	if (!(new = calloc(1, sizeof(zrpc_disk))))
		return NULL;

	new->int_dev = NULL;
	new->ext_dev = NULL;
	new->mode = NULL;
	new->type = NULL;
	new->partition_type = NULL;
	new->mapped_dev = NULL;

	return new;
}

static void free_zdisk(zrpc_disk *disk)
{
	if (!disk) return;

	eina_stringshare_del(disk->int_dev);
	disk->int_dev = NULL;
	eina_stringshare_del(disk->ext_dev);
	disk->ext_dev = NULL;
	eina_stringshare_del(disk->mode);
	disk->mode = NULL;
	eina_stringshare_del(disk->type);
	disk->type = NULL;
	eina_stringshare_del(disk->partition_type);
	disk->partition_type = NULL;
	eina_stringshare_del(disk->mapped_dev);
	disk->mapped_dev = NULL;

	free(disk);
	disk = NULL;
}

typedef struct _zrpc_vif {
	const char *name;
	const char *mac;
	const char *bridge;
	const char *script;
	const char *type;

	Eina_Bool loopback;
	Eina_Bool connected;
	Eina_Bool promisc;

	const char *ip;
	const char *netmask;
	const char *gateway;
	const char *broadcast;
		
	int mtu;

	double txpackets;
	double txbytes;
	double txdrop;
	double txerr;

	double rxpackets;
	double rxbytes;
	double rxdrop;
	double rxerr;

	double collisions;
} zrpc_vif;

zrpc_vif *new_zvif()
{
	zrpc_vif *new = NULL;
	if (!(new = calloc(1, sizeof(zrpc_vif))))
		return NULL;
	
	new->name = NULL;
	new->mac = NULL;
	new->bridge = NULL;
	new->script = NULL;
	new->type = NULL;
	new->ip = NULL;
	new->netmask = NULL;
	new->gateway = NULL;
	new->broadcast = NULL;

	return new;
}

static void free_zvif(zrpc_vif *vif)
{
	if (!vif) return;

	eina_stringshare_del(vif->name);
	vif->name = NULL;
	eina_stringshare_del(vif->mac);
	vif->mac = NULL;
	eina_stringshare_del(vif->bridge);
	vif->bridge = NULL;
	eina_stringshare_del(vif->script);
	vif->script = NULL;
	eina_stringshare_del(vif->type);
	vif->type = NULL;
	eina_stringshare_del(vif->ip);
	vif->ip = NULL;
	eina_stringshare_del(vif->netmask);
	vif->netmask = NULL;
	eina_stringshare_del(vif->gateway);
	vif->gateway = NULL;
	eina_stringshare_del(vif->broadcast);
	vif->broadcast = NULL;

	free(vif);

}

typedef struct _zrpc_vm {
	const char *name;
	const char *uuid;
	const char *puuid;
	const char *type;
	const char *os;
	int id;

	const char *kernel;
	const char *ramdisk;	
	const char *cmdline;
	const char *on_reboot;
	const char *on_poweroff;	
	const char *on_crash; 

	int mem;
	int maxmem;

	int vcpus;
	double cpupct;
	double cputime;
	int uptime;

	int vncport;
	const char *vncpasswd;
	
	const char *state;

	int numvbds;
	Eina_List *disks;
	
	int numnets;
	int rxbw;
	int txbw;
	Eina_List *vifs;
} zrpc_vm;

zrpc_vm *new_zvm()
{
	zrpc_vm *new = NULL;
	if (!(new = calloc(1, sizeof(zrpc_vm))))
		return NULL;
	
	new->name = NULL;
	new->uuid = NULL;
	new->puuid = NULL;
	new->type = NULL;
	new->os = NULL;
	new->kernel = NULL;
	new->ramdisk = NULL;	
	new->cmdline = NULL;
	new->on_reboot = NULL;
	new->on_poweroff = NULL;	
	new->on_crash = NULL; 
	new->vncpasswd = NULL;	
	new->state = NULL;
	new->disks = NULL;
	new->vifs = NULL;
	
	return new;
}

static void free_zvm(zrpc_vm *vm)
{
	if (!vm) return;

	eina_stringshare_del(vm->name);
	vm->name = NULL;
	eina_stringshare_del(vm->uuid);
	vm->uuid = NULL;
	eina_stringshare_del(vm->puuid);
	vm->puuid = NULL;
	eina_stringshare_del(vm->type);
	vm->type = NULL;
	eina_stringshare_del(vm->os);
	vm->os = NULL;
	eina_stringshare_del(vm->kernel);
	vm->kernel = NULL;
	eina_stringshare_del(vm->ramdisk);
	vm->ramdisk = NULL;
	eina_stringshare_del(vm->cmdline);
	vm->cmdline = NULL;
	eina_stringshare_del(vm->on_reboot);
	vm->on_reboot = NULL;
	eina_stringshare_del(vm->on_poweroff);
	vm->on_poweroff = NULL;
	eina_stringshare_del(vm->on_crash);
	vm->on_crash = NULL;
	eina_stringshare_del(vm->vncpasswd);
	vm->vncpasswd = NULL;
	eina_stringshare_del(vm->state);
	vm->state = NULL;

	if (vm->disks)
	{
		zrpc_disk *disk = NULL;
		EINA_LIST_FREE(vm->disks, disk)
			free_zdisk(disk);
		vm->disks = NULL;
	}
	if (vm->vifs)
	{
		zrpc_vif *vif = NULL;
		EINA_LIST_FREE(vm->vifs, vif)
			free_zvif(vif);
		vm->vifs = NULL;
	}

	free(vm);
	vm = NULL;

}

typedef struct _zrpc_node {

  	const char *hwuuid;
	const char *kernel;
	const char *address;
	const char *os;
	const char *architecture;
	const char *hostname;
	const char *domainname;
	const char *platformver;
	const char *platform;
	const char *default_vnc_pass;
	int  num_cpus;
	int  cores_per_socket;
	int  threads_per_core;
	int  num_cpu_nodes;
	int  sockets_per_node;
	double  cpu_mhz;
	double  total_memory;

	Eina_Bool hvm;
	const char *capabilities;
} zrpc_node;

typedef struct _zrpc_nodestats {

  	int timestamp;	
	double iowait;
    	const char *loadavg;
    	double uptime;
    	double cpupct;
   	int intr;
    	int ctxts;
   	int num_procs;
    	int mem_free;
    	int mem_total;
    	int mem_shared;
    	int mem_buffered;
    	int swap_total;
    	int swap_free;
    	const char *domainname;
    	const char *hostname;
    	const char *address;
    	double total_phys_mem;
    	double free_phys_mem;

} zrpc_nodestats;

typedef struct _zrpc_user {

        int uid;
        const char *name;
        const char *email;
        int active;
        int type;
        const char *language;
        
} zrpc_user;

zrpc_user *new_zuser()
{
	zrpc_user *new;
	if (!(new = calloc(1, sizeof(zrpc_user))))
		return NULL;

	new->name = NULL;
	new->email = NULL;
	new->language = NULL;

	return new;
}

static void free_zuser(zrpc_user *user)
{
	if (!user) return;

	eina_stringshare_del(user->name);
	eina_stringshare_del(user->email);
	eina_stringshare_del(user->language);

	free(user);
	user = NULL;

}


#endif
