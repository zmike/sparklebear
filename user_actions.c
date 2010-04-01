static void
user_action_cb(void *data, zrpc_handle h)
{
	zwin *zwin = data;
	char *xmlchar, *charxml;
	xmlNode *r;
	Elm_Genlist_Item *gl;
	useritem *item;
	zrpc_user *user;

	if (!(xmlchar = zwin->zcon->recbuf[h]))
		return;
	charxml = strdup(strchr(xmlchar, '<'));
	free(xmlchar);
	r = parsechar(charxml);
	if (parseint(r))
	{
		elm_label_label_set(zwin->zmain->status, "Action was successful!");
		evas_object_show(zwin->zmain->notify);
		if (strstr(zwin->view, "main"))
		{
			gl = elm_genlist_selected_item_get(zwin->zmain_user->list);
			if (gl)
			{
				item = (useritem*)elm_genlist_item_data_get(gl);
				user = item->user;
				zwin->list = eina_list_remove(zwin->list, user);
				#ifdef DEBUG
				printf("Removing %d:%s from all lists...\n", user->uid, user->name);
				#endif
				zwin->elist = eina_list_remove(zwin->elist, item);
				free_useritem(item);
				elm_genlist_item_del(gl);
			}
		}
/*		else if (strstr(zwin->view, "info"))
			free(stat);*/
		return;
	}
	else
	{
		elm_label_label_set(zwin->zmain->status, "Action failed!");
		evas_object_show(zwin->zmain->notify);
	}
}

void
user_remove_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	Elm_Genlist_Item *gl;
	int uid;
	useritem *item;

	if (streq(zwin->view, "main_user"))
	{
		gl = elm_genlist_selected_item_get(zwin->zmain_user->list);
		if (!gl)
			return;
		item = (useritem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(zwin->zmain_user->bar);
		uid = item->user->uid;
	}
	else if (strstr(zwin->view, "info"))
		uid = zwin->zinfo->uid;

	/*FIXME: error checking?*/

		
	if (!zrpc_User_removeUser(uid, zwin->zcon, user_action_cb, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(zwin->zmain->status, "Connection succeeded!");

	evas_object_show(zwin->zmain->notify);
	if (strstr(zwin->view, "hover")) zinfo_destroy_hover(zwin, NULL, NULL);
}

void
user_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;
	zmain *zmain = zwin->zmain_user;
	Elm_Genlist_Item *gl;
	useritem *item;
	zrpc_user *user;
	char tmp[PATH_MAX];
	Eina_List *l = NULL;

	elm_toolbar_item_unselect_all(zmain->bar);
	gl = elm_genlist_selected_item_get(zmain->list);
	if (!gl) return;
/*
	ecore_timer_del(zwin->timerget);

	item = (useritem*)elm_genlist_item_data_get(gl);
	user = item->user;
	zinfo->uid = user->uid;
	evas_object_smart_callback_del(zwin->zmain_user->list, "clicked", vm_info_cb);

	create_zinfo_user(zwin);
	zinfo_job_updateuser(zwin);

	snprintf(tmp, sizeof(tmp), "%d:%s", user->uid, user->name);
	elm_frame_label_set(zinfo->frame, tmp);

	elm_icon_file_set(zinfo->os_icon, os_icon, NULL);
	free(os_icon);
	elm_label_label_set(zinfo->os, vm->os);
	elm_label_label_set (zinfo->uuid, vm->uuid);
	elm_label_label_set(zinfo->puuid, vm->puuid);
	EINA_LIST_FOREACH(vm->disks, l, d)
		elm_hoversel_item_add(zinfo->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);
		
	state = get_state_icon(vm->state);
	elm_icon_file_set(zinfo->state_icon, state, NULL);
	free(state);

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
	evas_object_key_ungrab(zwin->win, "Home", 0, 0);
	evas_object_key_ungrab(zwin->win, "End", 0, 0);
	
	elm_flip_content_back_set(zwin->zmain->fl, zwin->zinfo->frame);
	sprintf(zwin->view, "info_vm");
	elm_flip_go(zwin->zmain->fl, ELM_FLIP_ROTATE_Y_CENTER_AXIS);

	EINA_LIST_FREE(zwin->elist, item)
		free_vmitem(item);
	zwin->elist = NULL;
	eina_list_free(zwin->list);
	zwin->list = NULL;
	evas_object_hide(zwin->zmain->box2);
	evas_object_del(zwin->zmain->box2);

	zwin->timerget = ecore_timer_add(5, zinfo_job_updatevm, zwin);
*/
}
