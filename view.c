#include "sparklebear.h"

void
view_main_vm(void *data, Evas_Object *obj, void *event_info)
{
	useritem *uitem;

	if ((win->view == win->main_vm->view) || (win->view == win->login->view))
		return;
	
	create_main_vm();
	if (elm_flip_front_get(win->main_vm->fl))
		elm_flip_content_back_set(win->main_vm->fl, win->main_vm->box2);
	else
		elm_flip_content_front_set(win->main_vm->fl, win->main_vm->box2);
	elm_label_label_set(win->main_vm->status, "Fetching vms...");
	evas_object_show(win->main_vm->notify);
	ecore_timer_del(win->timerget);

	elm_flip_go(win->main_vm->fl, ELM_FLIP_ROTATE_Y_CENTER_AXIS);
	if (win->view == win->main_user->view)
	{
		evas_object_del(win->main_user->box2);
		EINA_LIST_FREE(win->elist, uitem)
			free_useritem(uitem);
		win->elist = NULL;
		eina_list_free(win->list);
		win->list = NULL;
		eina_list_free(win->main_user->tb_list);
		
	}
	else if (win->view == win->info->vmview)
		evas_object_del(win->info->hbox);

	zmain_job_getvms(win);
	win->timerget = ecore_timer_add(win->vmtimer, zmain_job_getvms, NULL);
	win->view = win->main_vm->view;
}

void
view_main_user(void *data, Evas_Object *obj, void *event_info)
{
	vmitem *vitem;

	if ((win->view == win->main_user->view) || (win->view == win->login->view))
		return;

	if (win->view == win->info->vmview)
		change_zinfo_to_zmain((void*)win->main_user->view, NULL, NULL);
	create_main_user();
	if (elm_flip_front_get(win->main_vm->fl))
		elm_flip_content_back_set(win->main_vm->fl, win->main_user->box2);
	else
		elm_flip_content_front_set(win->main_vm->fl, win->main_user->box2);
	elm_label_label_set(win->main_vm->status, "Fetching users...");
	evas_object_show(win->main_vm->notify);
	ecore_timer_del(win->timerget);

	elm_flip_go(win->main_vm->fl, ELM_FLIP_ROTATE_Y_CENTER_AXIS);
	if (win->view == win->main_vm->view)
	{
		evas_object_del(win->main_vm->box2);
		EINA_LIST_FREE(win->elist, vitem)
			free_vmitem(vitem);
		win->elist = NULL;
		eina_list_free(win->main_vm->tb_list);
		eina_list_free(win->list);
		win->list = NULL;
	}
	else if (win->view == win->info->vmview)
		evas_object_del(win->info->frame);

	zmain_job_getusers(win);
	win->timerget = ecore_timer_add(win->usertimer, zmain_job_getusers, NULL);
	win->view = win->main_user->view;
}

