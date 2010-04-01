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
typedef void (*zrpc_network_cb)(void *, zrpc_handle);

/*lazy attempt to avoid double free*/
inline void zfree(void *data)
{
	if (data) free(data);
}

/*generic itoa*/
char *itoa(int x)
{
        char y[13];
        sprintf(y, "%d", x);
        return strdup(y);
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
	char *buf[100], /*send buffer*/
	*recbuf[100], /*receive buffer*/
	*call[100], 	/*rpc call name*/
	*zcookie; /*session cookie from login*/
	int bufsize[100], recbufsize[100];

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
	char *int_dev;
	char *ext_dev;
	char *mode;
	char *type;
	int ooreq;
	int rdreq;
	int wrreq;
	int num_sectors;
	int size_sector;
	char *partition_type;
	int start_sector;
	int block_size;
	int free;
	char *mapped_dev;
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

	zfree(disk->int_dev);
	disk->int_dev = NULL;
	zfree(disk->ext_dev);
	disk->ext_dev = NULL;
	zfree(disk->mode);
	disk->mode = NULL;
	zfree(disk->type);
	disk->type = NULL;
	zfree(disk->partition_type);
	disk->partition_type = NULL;
	zfree(disk->mapped_dev);
	disk->mapped_dev = NULL;

	zfree(disk);
	disk = NULL;
}

typedef struct _zrpc_vif {
	char *name;
	char *mac;
	char *bridge;
	char *script;
	char *type;

	Eina_Bool loopback;
	Eina_Bool connected;
	Eina_Bool promisc;

	char *ip;
	char *netmask;
	char *gateway;
	char *broadcast;
		
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

	zfree(vif->name);
	vif->name = NULL;
	zfree(vif->mac);
	vif->mac = NULL;
	zfree(vif->bridge);
	vif->bridge = NULL;
	zfree(vif->script);
	vif->script = NULL;
	zfree(vif->type);
	vif->type = NULL;
	zfree(vif->ip);
	vif->ip = NULL;
	zfree(vif->netmask);
	vif->netmask = NULL;
	zfree(vif->gateway);
	vif->gateway = NULL;
	zfree(vif->broadcast);
	vif->broadcast = NULL;

	zfree(vif);

}

typedef struct _zrpc_vm {
	char *name;
	char *uuid;
	char *puuid;
	char *type;
	char *os;
	int id;

	char *kernel;
	char *ramdisk;	
	char *cmdline;
	char *on_reboot;
	char *on_poweroff;	
	char *on_crash; 

	int mem;
	int maxmem;

	int vcpus;
	double cpupct;
	double cputime;
	int uptime;

	int vncport;
	char *vncpasswd;
	
	char *state;

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

	zfree(vm->name);
	vm->name = NULL;
	zfree(vm->uuid);
	vm->uuid = NULL;
	zfree(vm->puuid);
	vm->puuid = NULL;
	zfree(vm->type);
	vm->type = NULL;
	zfree(vm->os);
	vm->os = NULL;
	zfree(vm->kernel);
	vm->kernel = NULL;
	zfree(vm->ramdisk);
	vm->ramdisk = NULL;
	zfree(vm->cmdline);
	vm->cmdline = NULL;
	zfree(vm->on_reboot);
	vm->on_reboot = NULL;
	zfree(vm->on_poweroff);
	vm->on_poweroff = NULL;
	zfree(vm->on_crash);
	vm->on_crash = NULL;
	zfree(vm->vncpasswd);
	vm->vncpasswd = NULL;
	zfree(vm->state);
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

	zfree(vm);
	vm = NULL;

}

typedef struct _zrpc_node {

  	char *hwuuid;
	char *kernel;
	char *address;
	char *os;
	char *architecture;
	char *hostname;
	char *domainname;
	char *platformver;
	char *platform;
	char *default_vnc_pass;
	int  num_cpus;
	int  cores_per_socket;
	int  threads_per_core;
	int  num_cpu_nodes;
	int  sockets_per_node;
	double  cpu_mhz;
	double  total_memory;

	Eina_Bool hvm;
	char *capabilities;
} zrpc_node;

typedef struct _zrpc_nodestats {

  	int timestamp;	
	double iowait;
    	char *loadavg;
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
    	char *domainname;
    	char *hostname;
    	char *address;
    	double total_phys_mem;
    	double free_phys_mem;

} zrpc_nodestats;

typedef struct _zrpc_user {

        int uid;
        char *name;
        char *email;
        int active;
        int type;
        char *language;
        
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

	zfree(user->name);
	zfree(user->email);
	zfree(user->language);

	free(user);
	user = NULL;

}


#endif
