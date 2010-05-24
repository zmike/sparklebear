#ifndef MAIN_H
#define MAIN_H

#include <Elementary.h>
#include <Ecore_X.h>
#include "zrpc.h"
#include "zrpc_functions.h"
#include "xml.h"

/*adds some noise*/
#define DEBUG 1
/*this one makes this VERY noisy*/
//#define EDEBUG 1
/*this one prints the calls/receives*/
//#define XML_DEBUG 1

#define WEIGHT(X, Y, Z) evas_object_size_hint_weight_set(X, Y, Z)
#define ALIGN(X, Y, Z) evas_object_size_hint_align_set(X, Y, Z)

typedef struct _vmitem
{
	Elm_Genlist_Item *item;
	zrpc_vm *vm;
	const char *uuid;
	const char *state;
} vmitem;

typedef struct _useritem
{
	Elm_Genlist_Item *item;
	zrpc_user *user;
	int uid;
} useritem;

typedef struct _zlogin
{
	Evas_Object *box, *icon,
		*pb,
		*hbox, *loginbutton, *cancelbutton,
		*fr, *fr2,
		*fr3, *box2, *status, *stl;
	Ecore_Timer *lt;
	Eina_List *lp;
	const char *view;
} zlogin;

typedef struct _zmain
{
	Evas_Object *box, *panel, *viewbar,
		*fl,
		*box2,
		*bar, *icon,
		*list,
		*notify, *status;
	Ecore_Animator *anim;
	Eina_List *view_list, *tb_list;
	const char *view;
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
	const char *vmuuid, *state;
	const char *userview, *vmview, *vmhover;
	int uid, newuid, ulevel;
} zinfo;

typedef struct _zwin
{
	zlogin *login;
	zmain *main_vm, *main_user;
	zinfo *info;
	Evas_Object *fl, *win, *box, *bg, *rect;
	Eina_List *list, /*zrpc_$type *list*/
		*elist; /*$typeitem *list*/
	Ecore_Timer *timerget;
	int vmtimer, usertimer;
	zrpc_con *zcon;
	int xres, yres;
	const char *view;
} zwin;

#endif
