#include "sparklebear.h"

void
change_zlogin_to_zmain(const char *reply, void *data)
{
	zlogin *login = win->login;
	Eina_List *lp = login->lp;
	Evas_Object *l = lp->data;
	Evas_Object *p = lp->next->data;
	int zwidth = 800, zheight = 600;
	xmlNode *r;
	
	if (!zcon->zcookie) zcon->zcookie = calloc(37, sizeof(char));

#ifdef DEBUG
printf("parsing login...\n");
#endif
        if ((r = xml_parse_xml(reply)))
        {
	
		if (xml_parse_int(r))
		{
			printf("SUCCESS!\n");

			zlogin_stop(login);

			evas_object_key_ungrab(win->win, "Tab", 0, 0);
			evas_object_smart_callback_del(login->loginbutton, "clicked", zlogin_try);
			evas_object_smart_callback_del(login->cancelbutton, "clicked", exit_wrapper);
			create_main();
			zmain_job_getvms(win);
			
			elm_flip_content_back_set(win->fl, win->main_vm->box);

			elm_label_label_set(win->main_vm->status, "Fetching vms...");
			evas_object_show(win->main_vm->notify);
			evas_object_show(win->main_vm->fl);
			elm_flip_go(win->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
			win->view = win->main_vm->view;
#ifdef DEBUG
printf("current view: %s\nshould be: %s\n",win->view,win->main_vm->view);
#endif
			evas_object_del(login->box);
			eina_list_free(login->lp);
			login->lp = NULL;
			elm_win_title_set(win->win, "zEntific Control Center");

			evas_object_resize(win->win, zwidth, zheight);
			evas_object_move(win->win, (win->xres/2)-(zwidth/2), (win->yres/2)-(zheight/2));
			printf("Starting vm info timer...\n");
			win->timerget = ecore_timer_add(win->vmtimer, zmain_job_getvms, NULL);

			return;
		}
	}

	zlogin_stop(login);
	elm_label_label_set(login->stl, "Login failed!");
	evas_object_show(login->status);
	elm_object_disabled_set(l, EINA_FALSE);
	elm_object_disabled_set(p, EINA_FALSE);
	elm_object_focus(l);
	elm_scrolled_entry_cursor_end_set(l);
}

void
change_zmain_to_zlogin(void *data, Evas_Object *obj, void *event_info)
{
	zmain *view;
	vmitem *vitem;
	useritem *uitem;
	int zwidth = 396, zheight = 390;

	ecore_timer_del(win->timerget);
	create_login();
	elm_win_title_set(win->win, "zEntific Login");

	zrpc_User_logout(zcon, NULL, NULL);
		
	elm_flip_content_front_set(win->fl, win->login->box);
	elm_flip_go(win->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
	evas_object_resize(win->win, zwidth, zheight);
	evas_object_move(win->win, (win->xres/2)-(zwidth/2), (win->yres/2)-(zheight/2));

	evas_object_key_ungrab(win->win, "Up", 0, 0);
	evas_object_key_ungrab(win->win, "Down", 0, 0);
	evas_object_key_ungrab(win->win, "Home", 0, 0);
	evas_object_key_ungrab(win->win, "End", 0, 0);
	evas_object_del(win->main_vm->box);
	if (win->view == win->main_vm->view)
		view = win->main_vm;
	else if (win->view == win->main_user->view)
		view = win->main_user;


	if (win->view == win->main_vm->view)
		EINA_LIST_FREE(win->elist, vitem)
			free_vmitem(vitem);
	else if (win->view == win->main_user->view)
		EINA_LIST_FREE(win->elist, uitem)
			free_useritem(uitem);

	win->view = win->login->view;
	win->elist = NULL;
	eina_list_free(win->list);
	win->list = NULL;
	eina_list_free(win->main_vm->view_list);
	win->main_vm->view_list = NULL;
	
}

void
change_zinfo_to_zlogin(void *data, Evas_Object *obj, void *event_info)
{
	int zwidth = 396, zheight = 390;

	ecore_timer_del(win->timerget);
	create_login();
	elm_win_title_set(win->win, "zEntific Login");

	zrpc_User_logout(zcon, NULL, NULL);
		
	elm_flip_content_front_set(win->fl, win->login->box);
	elm_flip_go(win->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
	evas_object_resize(win->win, zwidth, zheight);
	evas_object_move(win->win, (win->xres/2)-(zwidth/2), (win->yres/2)-(zheight/2));

	win->view = win->login->view;

	evas_object_del(win->info->frame);

	eina_stringshare_del(win->info->vmuuid);
	win->info->vmuuid = NULL;
	eina_stringshare_del(win->info->state);
	win->info->state = NULL;
}

void
change_zinfo_to_zmain(void *data, Evas_Object *obj, void *event_info)
{
	int x;

	x = evas_object_key_grab(win->win, "Up", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Down", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Left", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Right", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Home", 0, 0, 1);
	x = evas_object_key_grab(win->win, "End", 0, 0, 1);
	ecore_timer_del(win->timerget);
	if (data == win->main_user->view)
		return;
	create_main_vm();

	win->timerget = ecore_timer_add(win->vmtimer, zmain_job_getvms, NULL);
	ecore_job_add((void*)zmain_job_getvms, NULL);
	elm_flip_content_front_set(win->main_vm->fl, win->main_vm->box2);
	elm_flip_go(win->main_vm->fl, ELM_FLIP_ROTATE_X_CENTER_AXIS);
	win->view = win->main_vm->view;
	evas_object_del(win->info->frame);
}
