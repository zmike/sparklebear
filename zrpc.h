/*zrpc efl c bindings
 * Mike Blumenkrantz 2010
 */

#ifndef ZRPC_H
#define ZRPC_H

/*for zrpc_user->type*/
#define USER_LEVEL_MIN 0
#define USER_LEVEL_MAX 5

#include <Eina.h>
#include <Ecore_Con.h>
#include <Ecore.h>
#include <ctype.h>
#include <string.h>


typedef int PLATFORM;

typedef int zrpc_handle;
/*generic callback for every function call*/
typedef void (*zrpc_network_cb)(const char*, void*);

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
	const char *call[100], 	/*rpc call name*/
	*zcookie; /*session cookie from login*/
        Eina_Strbuf *buf[100], *recbuf[100];

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
	const char *partition_type;
	const char *mapped_dev;
	int ooreq;
	int rdreq;
	int wrreq;
	int num_sectors;
	int size_sector;
	int start_sector;
	int block_size;
	int free;
} zrpc_disk;

typedef struct _zrpc_vif {
	const char *name;
	const char *mac;
	const char *bridge;
	const char *script;
	const char *type;

	const char *ip;
	const char *netmask;
	const char *gateway;
	const char *broadcast;

	int loopback;
	int connected;
	int promisc;
		
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

zrpc_meta_struct *zmeta_new();
zrpc_disk *zdisk_new();
void zdisk_free(zrpc_disk *disk);
zrpc_vif *zvif_new();
void zvif_free(zrpc_vif *vif);
zrpc_vm *zvm_new();
void zvm_free(zrpc_vm *vm);
zrpc_user *zuser_new();
void zuser_free(zrpc_user *user);
int meta_getUsersFull(zrpc_con *zcon, zrpc_network_cb cb, void *cbd);
int zrpc_meta(const char *call, Eina_List *params, zrpc_con *zcon, zrpc_network_cb cb, void *cbd);

#endif
