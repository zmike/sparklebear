static void
vm_action_cb(void *data, const char *reply)
{
	zwin *zwin = data;
	const char *charxml;
	xmlNode *r;
	Elm_Genlist_Item *gl;
	vmitem *item;
	zrpc_vm *vm;

	if (!reply) return;
	charxml = eina_stringshare_add(strchr(reply, '<'));
	eina_stringshare_del(reply);
	r = parsechar(charxml);
	if (!parseint(r))
	{
		elm_label_label_set(zwin->zmain->status, "Job add failed!");
		evas_object_show(zwin->zmain->notify);
		return;
	}

	elm_label_label_set(zwin->zmain->status, "Job add was successful!");
	evas_object_show(zwin->zmain->notify);
	if ((zwin->view == zwin->zmain->view) || (zwin->view == zwin->zmain_user->view))
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (gl)
		{
			item = (vmitem*)elm_genlist_item_data_get(gl);
			vm = item->vm;
			zwin->list = eina_list_remove(zwin->list, vm);
#ifdef DEBUG
printf("Removing %s from all lists...\n", vm->uuid);
#endif
			zwin->elist = eina_list_remove(zwin->elist, item);
			free_vmitem(item);
			elm_genlist_item_del(gl);
		}
	}
}

static void
vm_hibernate_cb(void *data, Evas_Object *obj, void *event_info)
{
/*
	zwin *zwin = data;
	char *stat, *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_save(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
*/}

static void
vm_destroy_cb(void *data, Evas_Object *obj, void *event_info)
{
/*
	zwin *zwin = data;
	char *stat, *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");	
	else if (!zrpc_VM_destroy(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
*/
}

static void
vm_shutdown_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	const const char *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover))
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_shutdown(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
	if (zwin->view == zwin->zinfo->vmhover)
		zinfo_destroy_hover(zwin, NULL, NULL);
}


static void
vm_reboot_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	const char *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover))
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_reboot(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
	if (zwin->view == zwin->zinfo->vmhover) zinfo_destroy_hover(zwin, NULL, NULL);
}

static void
vm_pause_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	const char *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover))
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_pause(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
	if (zwin->view == zwin->zinfo->vmhover) zinfo_destroy_hover(zwin, NULL, NULL);
}

static void
vm_unpause_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	const char *uuid = NULL;
	Elm_Genlist_Item *gl;
	vmitem *item;

	if (zwin->view == zwin->zmain->view)
	{
		gl = elm_genlist_selected_item_get(zwin->zmain->list);
		if (!gl)
			return;
		item = (vmitem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain->bar);
		uuid = item->vm->uuid;
	}
	else if ((zwin->view == zwin->zinfo->vmview) || (zwin->view == zwin->zinfo->vmhover))
		uuid = zwin->zinfo->vmuuid;

	if (!uuid || (strlen(uuid) != 36))
		elm_label_label_set(zwin->zmain->status, "Could not retrieve valid uuid for operation!");
	else if (!zrpc_VM_unpause(uuid, zwin->zcon, vm_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
	if (zwin->view == zwin->zinfo->vmhover) zinfo_destroy_hover(zwin, NULL, NULL);
}

static void
vm_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;
	zmain *zmain = zwin->zmain;
	Elm_Genlist_Item *gl;
	vmitem *item;
	zrpc_vm *vm;
	const char *os_icon, *state;
	char tmp[PATH_MAX];
	Eina_List *l = NULL;
	zrpc_disk *d;
	zrpc_vif *v;
	int cpus;

	elm_toolbar_item_unselect_all(zmain->bar);
	gl = elm_genlist_selected_item_get(zmain->list);
	if (!gl) return;

	ecore_timer_del(zwin->timerget);

	item = (vmitem*)elm_genlist_item_data_get(gl);
	vm = item->vm;
	zinfo->vmuuid = eina_stringshare_ref(vm->uuid);
	evas_object_smart_callback_del(zwin->zmain->list, "clicked", vm_info_cb);
	create_zinfo_vm(zwin);
	zinfo->state = NULL;
	zinfo_job_updatevm(zwin);


	for (cpus = 0;cpus < vm->vcpus;cpus++)
	{
		
		zinfo->cpus = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->cpus, "images/cpu.png", NULL);
		elm_icon_scale_set(zinfo->cpus, 0, 0);
		elm_icon_smooth_set(zinfo->cpus, 1);
		evas_object_size_hint_weight_set(zinfo->state_icon, 0.0, 0.0);
		evas_object_size_hint_align_set(zinfo->state_icon, 0.0, 1.0);
		elm_box_pack_after(zinfo->vbox2, zinfo->cpus, zinfo->state_label);
		evas_object_show(zinfo->cpus);
	}

	elm_frame_label_set(zinfo->frame, vm->name);
	os_icon = get_os_icon(vm);
	elm_icon_file_set(zinfo->os_icon, os_icon, NULL);
	eina_stringshare_del(os_icon);
	elm_label_label_set(zinfo->os, vm->os);
	elm_label_label_set (zinfo->uuid, vm->uuid);
	elm_label_label_set(zinfo->puuid, vm->puuid);
	EINA_LIST_FOREACH(vm->disks, l, d)
		elm_hoversel_item_add(zinfo->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);
		
	state = get_state_icon(vm->state);
	elm_icon_file_set(zinfo->state_icon, state, NULL);
	eina_stringshare_del(state);

	EINA_LIST_FOREACH(vm->vifs, l, v)
		elm_hoversel_item_add(zinfo->vifs, v->name, NULL, ELM_ICON_NONE, NULL, v);


	sprintf(tmp, "Kernel: %s", vm->kernel);
	elm_label_label_set(zinfo->kernel, tmp);
	sprintf(tmp, "Ramdisk: %s", vm->ramdisk);
	elm_label_label_set(zinfo->ramdisk, tmp);
	sprintf(tmp, "Kernel args: %s", vm->cmdline);
	elm_label_label_set(zinfo->cmdline, tmp);

	evas_object_key_ungrab(zwin->win, "Up", 0, 0);
	evas_object_key_ungrab(zwin->win, "Down", 0, 0);
	evas_object_key_ungrab(zwin->win, "Left", 0, 0);
	evas_object_key_ungrab(zwin->win, "Right", 0, 0);
	evas_object_key_ungrab(zwin->win, "Home", 0, 0);
	evas_object_key_ungrab(zwin->win, "End", 0, 0);
	
	elm_flip_content_back_set(zwin->zmain->fl, zwin->zinfo->frame);
	zwin->view = zwin->zinfo->vmview;
	elm_flip_go(zwin->zmain->fl, ELM_FLIP_ROTATE_X_CENTER_AXIS);

	EINA_LIST_FREE(zwin->elist, item)
		free_vmitem(item);
	zwin->elist = NULL;
	eina_list_free(zwin->list);
	zwin->list = NULL;
	evas_object_hide(zwin->zmain->box2);
	evas_object_del(zwin->zmain->box2);

	zwin->timerget = ecore_timer_add(5, zinfo_job_updatevm, zwin);
}
