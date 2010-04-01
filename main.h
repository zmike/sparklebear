#include <Elementary.h>
#include <Ecore_X.h>
#include <mcheck.h>
#include "zrpc.h"

/*adds some noise*/
#define DEBUG 1
/*this one makes this VERY noisy*/
//#define EDEBUG 1
/*this one prints the calls/receives*/
//#define XML_DEBUG 1

//BEGIN ZRPC.C
#include "zrpc.c"
//END ZRPC.C



static char *zlogo = "images/logo.png";

static void create_zmain_vm(void *data);
static void create_zmain_user(void *data);
static int zmain_job_getvms(void *data);
static int zmain_job_getusers(void *data);
static void create_zlogin(void *data);
static void vm_info_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_unpause_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_pause_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_reboot_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_hibernate_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_destroy_cb(void *data, Evas_Object *obj, void *event_info);
static void vm_shutdown_cb(void *data, Evas_Object *obj, void *event_info);
static void create_zinfo_vm(void *data);
static int zinfo_job_updatevm(void *data);
static void zinfo_destroy_hover(void *data, Evas_Object *obj, void *event_info);
static void zmain_to_zlogin(void *data, Evas_Object *obj, void *event_info);
static void zinfo_to_zlogin(void *data, Evas_Object *obj, void *event_info);
void zinfo_job_updateuser(void *data, Evas_Object *obj, void *event_info);
void create_zinfo_user(void *data);

typedef struct _vmitem
{
	Elm_Genlist_Item *item;
	zrpc_vm *vm;
	char *uuid;
	char *state;
} vmitem;

vmitem *new_vmitem()
{
	vmitem *new = NULL;
	new = calloc(1, sizeof(vmitem));
	
	new->item = NULL;
	new->vm = NULL;
	new->uuid = NULL;
	new->state = NULL;
	
	return new;
}

void free_vmitem(vmitem *item)
{
	if (!item) return;

	zfree(item->uuid);
	item->uuid = NULL;
	zfree(item->state);
	item->state = NULL;
	if (item->vm)
	{
		free_zvm(item->vm);
		item->vm = NULL;
	}

	zfree(item);
	item = NULL;

}

typedef struct _useritem
{
	Elm_Genlist_Item *item;
	zrpc_user *user;
	int uid;
} useritem;

useritem *new_useritem()
{
	useritem *new;
	if (!(new = calloc(1, sizeof(useritem))))
		return NULL;

	new->item = NULL;
	new->user = NULL;
	new->uid = -1;

	return new;
}

void free_useritem(useritem *item)
{
	if (!item) return;

	if (item->user)
	{
		free_zuser(item->user);
		item->user = NULL;
	}

	zfree(item);
	item = NULL;

}

typedef struct _zlogin
{
	Evas_Object *box, *icon,
		*pb,
		*hbox, *loginbutton, *cancelbutton,
		*fr, *fr2,
		*fr3, *box2, *status, *stl;
	Ecore_Timer *lt;
	Eina_List *lp;
} zlogin;

typedef struct _zmain
{
	Evas_Object *box, *panel, *viewbar,
		*fl,
		*box2,
		*bar, *icon,
		*list,
		*notify, *status;
	Elm_Genlist_Item_Class *itc;
	Elm_Toolbar_Item *tbitem;
	Ecore_Animator *anim;
	Eina_List *tb_list;
} zmain;

typedef struct _zinfo
{
	Evas_Object *frame,
		*hbox, *sp,
		*hover, *ic, *hb, *lb, *pass, *email, *level, *level_icon,
		*vbox1, *back, *bi,
		*os_icon, *id, *os, *name, *uuid, *puuid, *disks,
		*vbox2,
		*uptime, *state_icon, *state_label, *cpus, *pct, *vifs,
		*vbox3, *vbox4,
		*kernel, *ramdisk, *cmdline,
			*notesframe, *notes, *notesend;
	Ecore_Timer *update;
	char *vmuuid, *state;
	int uid, newuid, ulevel;
} zinfo;

typedef struct _zwin
{
	zlogin *zlogin;
	zmain *zmain, *zmain_user;
	zinfo *zinfo;
	Evas_Object *fl, *win, *box, *bg, *rect;
	Eina_List *list, /*zrpc_$type *list*/
		*elist; /*$typeitem *list*/
	Ecore_Timer *timerget;
	int vmtimer, usertimer;
	zrpc_con *zcon;
	int xres, yres;
	char view[10];
} zwin;

static void
exit_wrapper(void *data, Evas_Object *obj, void *event_info)
{
#ifdef DEBUG
	zwin *zwin = data;
	vmitem *item;
	
	if (streq(zwin->view, "main_vm"))
		EINA_LIST_FREE(zwin->elist, item)
			free_vmitem(item);
#endif

	xmlCleanupParser();
	elm_exit();
}

char *get_os_icon(const zrpc_vm *vm)
{
	char *buf;

	if (strstr(vm->os, "inux"))
		buf = strdup("images/tux.png");
	else if (strstr(vm->os, "indows"))
		buf = strdup("images/windows.png");
	else buf = strdup("images/unknown.png");

	return buf;
}

char *get_state_icon(const char *state)
{
	char buf[PATH_MAX], *ret;

	if (streq(state, "") || streq(state, "r"))
		sprintf(buf, "images/player_play.png");
	else if (streq(state, "b"))
		sprintf(buf, "images/player_time.png");
	else if (streq(state, "d") || streq(state, "s"))
		sprintf(buf, "images/player_stop.png");
	else if (streq(state, "p"))
		sprintf(buf, "images/player_pause.png");
	else
		sprintf(buf, "images/dialog_close.png");

	ret = strdup(buf);
	return ret;
}

char *get_state_name(const char *state)
{
	char buf[15], *ret;

	if (streq(state, "") || streq(state, "r"))
		sprintf(buf, "Running");
	else if (streq(state, "b"))
		sprintf(buf, "Blocked");
	else if (streq(state, "d") || streq(state, "s"))
		sprintf(buf, "Dying");
	else if (streq(state, "p"))
		sprintf(buf, "Paused");
	else
		sprintf(buf, "Shut Down");

	ret = strdup(buf);
	return ret;
}

char *get_access_icon(int level)
{
	char buf[PATH_MAX], *ret;

	if (level == 0)/*SuperUser*/
		sprintf(buf, "images/configure.png");
	else if (level == 1)/*Maintenance*/
		sprintf(buf, "images/configure_toolbars.png");
	else if (level == 2)/*Owner*/
		sprintf(buf, "images/exec.png");
	else if (level == 3)/*Admin*/
		sprintf(buf, "images/edit_find_user.png");
	else if (level == 4)/*R/O Admin*/
		sprintf(buf, "images/document_preview_archive.png");
	else if (level == 5)/*none*/
		sprintf(buf, "images/edit_clear_locationbar.png");

	ret = strdup(buf);
	return ret;
}

char *get_access_name(int level)
{
	char buf[PATH_MAX], *ret;

	if (level == 0)/*SuperUser*/
		sprintf(buf, "SuperUser");
	else if (level == 1)/*Maintenance*/
		sprintf(buf, "Maintenance");
	else if (level == 2)/*Owner*/
		sprintf(buf, "Owner");
	else if (level == 3)/*Admin*/
		sprintf(buf, "Admin");
	else if (level == 4)/*R/O Admin*/
		sprintf(buf, "Read-Only Admin");
	else if (level == 5)/*none*/
		sprintf(buf, "NONE");

	ret = strdup(buf);
	return ret;

}
