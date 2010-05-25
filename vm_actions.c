#include "sparklebear.h"

static void
vm_action_cb(const char *reply, void *data)
{
	xmlNode *r;
	Elm_Genlist_Item *gl;
	vmitem *item;
	zrpc_vm *vm;

	if (!reply || !(r = xml_parse_xml(reply)) || (!xml_parse_int(r)))
	{
		elm_label_label_set(win->main_vm->status, "Job add failed!");
		evas_object_show(win->main_vm->notify);
		return;
	}

	elm_label_label_set(win->main_vm->status, "Job add was successful!");
	evas_object_show(win->main_vm->notify);
	if ((win->view == win->main_vm->view) || (win->view == win->main_user->view))
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (gl)
		{
			item = (vmitem*)elm_genlist_item_data_get(gl);
			vm = item->vm;
			win->list = eina_list_remove(win->list, vm);
#ifdef DEBUG
printf("Removing %s from all lists...\n", vm->uuid);
#endif
			win->elist = eina_list_remove(win->elist, item);
			free_vmitem(item);
			elm_genlist_item_del(gl);
		}
	}
}

void
vm_hibernate_cb(void *data, Evas_Object *obj, void *event_info)
{
/*
	char *stat, *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover
		uuid = win->info->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_save(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
*/}

void
vm_destroy_cb(void *data, Evas_Object *obj, void *event_info)
{
/*
	char *stat, *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover
		uuid = win->info->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");	
	else if (!zrpc_VM_destroy(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
*/
}

void
vm_shutdown_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *uuid;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover))
		uuid = win->info->vmuuid;

	if (!uuid || (eina_stringshare_strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_shutdown(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (win->view == win->info->vmhover)
		zinfo_destroy_hover(NULL, NULL, NULL);
}


void
vm_reboot_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *uuid;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover))
		uuid = win->info->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_reboot(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (win->view == win->info->vmhover) zinfo_destroy_hover(NULL, NULL, NULL);
}

void
vm_pause_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *uuid;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover))
		uuid = win->info->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_pause(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (win->view == win->info->vmhover) zinfo_destroy_hover(NULL, NULL, NULL);
}

void
vm_unpause_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *uuid;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (win->view == win->main_vm->view)
	{
		gl = elm_genlist_selected_item_get(win->main_vm->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_vm->bar);
		uuid = item->vm->uuid;
	}
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover))
		uuid = win->info->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(win->main_vm->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_unpause(uuid, zcon, vm_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (win->view == win->info->vmhover) zinfo_destroy_hover(NULL, NULL, NULL);
}

void
vm_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Genlist_Item *gl;
	vmitem *item;
	zrpc_vm *vm;
	const char *os_icon, *state;
	char tmp[PATH_MAX];
	Eina_List *l;
	zrpc_disk *d;
	zrpc_vif *v;
	int cpus;

	elm_toolbar_item_unselect_all(win->main_vm->bar);
	gl = elm_genlist_selected_item_get(win->main_vm->list);
	if (!gl) return;

	ecore_timer_del(win->timerget);

	item = (vmitem*)elm_genlist_item_data_get(gl);
	vm = item->vm;
	win->info->vmuuid = eina_stringshare_ref(vm->uuid);
	evas_object_smart_callback_del(win->main_vm->list, "clicked", vm_info_cb);
	create_info_vm();
	win->info->state = NULL;
	zinfo_job_updatevm(win);


	for (cpus = 0;cpus < vm->vcpus;cpus++)
	{
		
		win->info->cpus = elm_icon_add(win->win);
		elm_icon_file_set(win->info->cpus, "images/cpu.png", NULL);
		elm_icon_scale_set(win->info->cpus, 0, 0);
		elm_icon_smooth_set(win->info->cpus, 1);
		evas_object_size_hint_weight_set(win->info->state_icon, 0.0, 0.0);
		evas_object_size_hint_align_set(win->info->state_icon, 0.0, 1.0);
		elm_box_pack_after(win->info->vbox2, win->info->cpus, win->info->state_label);
		evas_object_show(win->info->cpus);
	}

	elm_frame_label_set(win->info->frame, vm->name);
	os_icon = get_os_icon(vm);
	elm_icon_file_set(win->info->os_icon, os_icon, NULL);
	eina_stringshare_del(os_icon);
	elm_label_label_set(win->info->os, vm->os);
	elm_label_label_set (win->info->uuid, vm->uuid);
	elm_label_label_set(win->info->puuid, vm->puuid);
	EINA_LIST_FOREACH(vm->disks, l, d)
		elm_hoversel_item_add(win->info->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);
		
	state = get_state_icon(vm->state);
	elm_icon_file_set(win->info->state_icon, state, NULL);
	eina_stringshare_del(state);

	EINA_LIST_FOREACH(vm->vifs, l, v)
		elm_hoversel_item_add(win->info->vifs, v->name, NULL, ELM_ICON_NONE, NULL, v);


	sprintf(tmp, "Kernel: %s", vm->kernel);
	elm_label_label_set(win->info->kernel, tmp);
	sprintf(tmp, "Ramdisk: %s", vm->ramdisk);
	elm_label_label_set(win->info->ramdisk, tmp);
	sprintf(tmp, "Kernel args: %s", vm->cmdline);
	elm_label_label_set(win->info->cmdline, tmp);

	evas_object_key_ungrab(win->win, "Up", 0, 0);
	evas_object_key_ungrab(win->win, "Down", 0, 0);
	evas_object_key_ungrab(win->win, "Left", 0, 0);
	evas_object_key_ungrab(win->win, "Right", 0, 0);
	evas_object_key_ungrab(win->win, "Home", 0, 0);
	evas_object_key_ungrab(win->win, "End", 0, 0);
	
	elm_flip_content_back_set(win->main_vm->fl, win->info->frame);
	win->view = win->info->vmview;
	elm_flip_go(win->main_vm->fl, ELM_FLIP_ROTATE_X_CENTER_AXIS);

	EINA_LIST_FREE(win->elist, item)
		free_vmitem(item);
	win->elist = NULL;
	eina_list_free(win->list);
	win->list = NULL;
	evas_object_hide(win->main_vm->box2);
	evas_object_del(win->main_vm->box2);

	win->timerget = ecore_timer_add(5, zinfo_job_updatevm, NULL);
}
