static void
gl_sel(void *data, Evas_Object *obj, void *event_info)
{
#ifdef DEBUG
	zwin *zwin = data;
	Elm_Genlist_Item *gitem;
	const vmitem *vitem;
	const useritem *uitem;
	if (streq(zwin->view, "main_vm"))
	{
		gitem = elm_genlist_selected_item_get(zwin->zmain->list);
		vitem = elm_genlist_item_data_get(gitem);
		printf("sel vm [%s:%s], item pointer [%p]\n", vitem->vm->name, vitem->vm->uuid, event_info);
	}
	else if (streq(zwin->view, "main_user"))
	{
		gitem = elm_genlist_selected_item_get(zwin->zmain_user->list);
		uitem = elm_genlist_item_data_get(gitem);
		printf("sel user [%d:%s], item pointer [%p]\n", uitem->user->uid, uitem->user->name, event_info);

	}
#endif
}

static void
logout(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	if (strstr(zwin->view, "main_"))
		zmain_to_zlogin(zwin, NULL, NULL);
	else if (streq(zwin->view, "info_vm"))
		zinfo_to_zlogin(zwin, NULL, NULL);
}

static void
zmain_to_zlogin(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	vmitem *vitem;
	useritem *uitem;
	int zwidth = 396, zheight = 390;

	elm_toolbar_item_unselect_all(zwin->zmain->bar);

	ecore_timer_del(zwin->timerget);
	create_zlogin(zwin);
	elm_win_title_set(zwin->win, "zEntific Login");

	zrpc_User_logout(zwin->zcon, NULL, NULL);
		
	elm_flip_content_front_set(zwin->fl, zwin->zlogin->box);
	elm_flip_go(zwin->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
	evas_object_resize(zwin->win, zwidth, zheight);
	evas_object_move(zwin->win, (zwin->xres/2)-(zwidth/2), (zwin->yres/2)-(zheight/2));

	evas_object_key_ungrab(zwin->win, "Up", 0, 0);
	evas_object_key_ungrab(zwin->win, "Down", 0, 0);
	evas_object_key_ungrab(zwin->win, "Home", 0, 0);
	evas_object_key_ungrab(zwin->win, "End", 0, 0);
	evas_object_hide(zwin->zmain->fl);
	evas_object_del(zwin->zmain->fl);
//	evas_object_hide(zwin->zmain->box2);
//	evas_object_del(zwin->zmain->box2);
	if (streq(zwin->view, "main_vm"))
	{
		evas_object_hide(zwin->zmain->bar);
		evas_object_del(zwin->zmain->bar);
		evas_object_hide(zwin->zmain->list);
		evas_object_del(zwin->zmain->list);
	}
	else if (streq(zwin->view, "main_user"))
	{
		evas_object_hide(zwin->zmain_user->bar);
		evas_object_del(zwin->zmain_user->bar);
		evas_object_hide(zwin->zmain_user->list);
		evas_object_del(zwin->zmain_user->list);
	}	
	evas_object_hide(zwin->zmain->box);
	evas_object_del(zwin->zmain->box);
	if (streq(zwin->view, "main_vm"))
		EINA_LIST_FREE(zwin->elist, vitem)
			free_vmitem(vitem);
	else if (streq(zwin->view, "main_user"))
		EINA_LIST_FREE(zwin->elist, uitem)
			free_useritem(uitem);
	sprintf(zwin->view, "login");
	zwin->elist = NULL;
	eina_list_free(zwin->list);
	zwin->list = NULL;
	eina_list_free(zwin->zmain->tb_list);
	zwin->zmain->tb_list = NULL;
	
}

static void
zmain_vm_keybind(void *data, Evas_Event_Key_Down *key)
{
		zwin *zwin = data;
		Elm_Genlist_Item *gi, *gi2;
		Eina_List *tb_list, *l;
		zmain *zmain;
		Elm_Toolbar_Item *tb;

		if (streq(zwin->view, "main_vm"))
			zmain = zwin->zmain;
		else if (streq(zwin->view, "main_user"))
			zmain = zwin->zmain_user;
		else return;

		if (streq(key->keyname, "Escape"))
		{
			zmain_to_zlogin(zwin, NULL, NULL);
			return;
		}
		else if (streq(key->keyname, "Left"))
		{
			EINA_LIST_FOREACH(zwin->zmain->tb_list, l, tb)
				if (elm_toolbar_item_selected_get(tb))
					break;
			if (!l->prev) tb_list = eina_list_last(zwin->zmain->tb_list);
			else tb_list = l->prev;
			tb = tb_list->data;
			elm_toolbar_item_select(tb);
			return;
		}
		else if (streq(key->keyname, "Right"))
		{
			EINA_LIST_FOREACH(zwin->zmain->tb_list, l, tb)
				if (elm_toolbar_item_selected_get(tb))
					break;
			if (!l->next) tb_list = zwin->zmain->tb_list;
			else tb_list = l->next;
			tb = tb_list->data;
			elm_toolbar_item_select(tb);
			return;
		}
		else if (streq(key->keyname, "Down"))
		{
			if (!(gi = elm_genlist_selected_item_get(zmain->list)))
			{
				if (!(gi = elm_genlist_first_item_get(zmain->list)))
					return;
				elm_genlist_item_selected_set(gi, 1);
			}
			else
			{
				if (!(gi2 = elm_genlist_item_next_get(gi)))
					return;
				elm_genlist_item_selected_set(gi2, 1);
				elm_genlist_item_bring_in(gi2);
			}
		}
		else if (streq(key->keyname, "Up"))
		{
			if (!(gi = elm_genlist_selected_item_get(zmain->list)))
			{
				if (!(gi = elm_genlist_first_item_get(zmain->list)))
					return;
				elm_genlist_item_selected_set(gi, 1);
			}
			else
			{
				if (!(gi2 = elm_genlist_item_prev_get(gi)))
					return;
				elm_genlist_item_selected_set(gi2, 1);
				elm_genlist_item_bring_in(gi2);
			}
		}
		else if (streq(key->keyname, "Home"))
		{
			if (!(gi = elm_genlist_first_item_get(zmain->list)))
				return;
			elm_genlist_item_selected_set(gi, 1);
			elm_genlist_item_bring_in(gi);
		}
		else if (streq(key->keyname, "End"))
		{
			if (!(gi = elm_genlist_last_item_get(zmain->list)))
				return;
			elm_genlist_item_selected_set(gi, 1);
			elm_genlist_item_bring_in(gi);
		}
		else if (streq(key->keyname, "Return") || streq(key->keyname, "KP_Enter"))
			if (streq(zwin->view, "main_vm"))
				vm_info_cb(zwin, NULL, NULL);

}

static void zmain_vm_view(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	useritem *uitem;

	if (streq(zwin->view, "main_vm") || streq(zwin->view, "login"))
		return;
	
	create_zmain_vm(zwin);
	elm_flip_content_front_set(zwin->zmain->fl, zwin->zmain->box2);
	elm_label_label_set(zwin->zmain->status, "Fetching vms...");
	evas_object_show(zwin->zmain->notify);
	ecore_timer_del(zwin->timerget);

	elm_flip_go(zwin->zmain->fl, ELM_FLIP_ROTATE_Y_CENTER_AXIS);
	if (streq(zwin->view, "main_user"))
	{
		evas_object_hide(zwin->zmain_user->box2);
		evas_object_del(zwin->zmain_user->box2);
		EINA_LIST_FREE(zwin->elist, uitem)
			free_useritem(uitem);
		zwin->elist = NULL;
		eina_list_free(zwin->list);
		zwin->list = NULL;
		
	}
	else if (streq(zwin->view, "info_vm"))
	{
		evas_object_hide(zwin->zinfo->frame);
		evas_object_hide(zwin->zinfo->hbox);
		evas_object_del(zwin->zinfo->hbox);
	}
	zmain_job_getvms(zwin);
	zwin->timerget = ecore_timer_add(zwin->vmtimer, zmain_job_getvms, zwin);
	sprintf(zwin->view, "main_vm");
}

static void zmain_user_view(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	vmitem *vitem;

	if (streq(zwin->view, "main_user") || streq(zwin->view, "login"))
		return;

	
	create_zmain_user(zwin);
	if (strstr(zwin->view, "info"))
		elm_flip_content_front_set(zwin->zmain->fl, zwin->zmain_user->box2);
	elm_flip_content_back_set(zwin->zmain->fl, zwin->zmain_user->box2);
	elm_label_label_set(zwin->zmain->status, "Fetching users...");
	evas_object_show(zwin->zmain->notify);
	ecore_timer_del(zwin->timerget);

	elm_flip_go(zwin->zmain->fl, ELM_FLIP_ROTATE_Y_CENTER_AXIS);
	if (streq(zwin->view, "main_vm"))
	{
		evas_object_hide(zwin->zmain->box2);
		evas_object_del(zwin->zmain->box2);
		EINA_LIST_FREE(zwin->elist, vitem)
			free_vmitem(vitem);
		zwin->elist = NULL;
		eina_list_free(zwin->list);
		zwin->list = NULL;
	}
	else if (streq(zwin->view, "info_vm"))
	{
		evas_object_hide(zwin->zinfo->frame);
		evas_object_hide(zwin->zinfo->hbox);
		evas_object_del(zwin->zinfo->hbox);
	}
	zmain_job_getusers(zwin);
	zwin->timerget = ecore_timer_add(zwin->usertimer, zmain_job_getusers, zwin);
	sprintf(zwin->view, "main_user");
}

static void create_zmain_vm(void *data)
{
	zwin *zwin = data;
	zmain *zmain = zwin->zmain;

	zmain->box2 = elm_box_add(zwin->win);
	elm_object_focus_allow_set(zmain->box2, 0);
	evas_object_size_hint_weight_set(zmain->box2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->box2, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zmain->box2);

	zmain->bar = elm_toolbar_add(zwin->win);
	elm_toolbar_homogenous_set(zmain->bar, 0);
	elm_toolbar_scrollable_set(zmain->bar, 0);
	evas_object_size_hint_weight_set(zmain->bar, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zmain->bar, EVAS_HINT_FILL, 0.0);
	elm_box_pack_end(zmain->box2, zmain->bar);
	evas_object_show(zmain->bar);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/screwdriver.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Info", vm_info_cb, zwin);
	
	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/pause.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Pause", vm_pause_cb, zwin);
	
	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/shutdown.png", NULL);
	zmain->tbitem = elm_toolbar_item_add(zmain->bar, zmain->icon, "Shutdown", vm_shutdown_cb, zwin);
	
	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/reboot.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Reboot", vm_reboot_cb, zwin);
	
	zmain->list = elm_genlist_add(zwin->win);
	evas_object_smart_callback_add(zmain->list, "clicked", vm_info_cb, zwin);
	evas_object_size_hint_weight_set(zmain->list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zmain->box2, zmain->list);
	evas_object_show(zmain->list);

}

static void create_zmain_user(void *data)
{
	zwin *zwin = data;
	zmain *zmain = zwin->zmain_user;

	zmain->box2 = elm_box_add(zwin->win);
	elm_object_focus_allow_set(zmain->box2, 0);
	evas_object_size_hint_weight_set(zmain->box2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->box2, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zmain->box2);

	zmain->bar = elm_toolbar_add(zwin->win);
	elm_toolbar_homogenous_set(zmain->bar, 0);
	elm_toolbar_scrollable_set(zmain->bar, 0);
	evas_object_size_hint_weight_set(zmain->bar, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zmain->bar, EVAS_HINT_FILL, 0.0);
	elm_box_pack_end(zmain->box2, zmain->bar);
	evas_object_show(zmain->bar);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/kfind.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Info", NULL, zwin);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/add_user.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Add", NULL, zwin);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/edit_user.png", NULL);
	zmain->tbitem = elm_toolbar_item_add(zmain->bar, zmain->icon, "Edit", NULL, zwin);
	
	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/delete_user.png", NULL);
	elm_toolbar_item_add(zmain->bar, zmain->icon, "Remove", user_remove_cb, zwin);

	zmain->list = elm_genlist_add(zwin->win);
//	evas_object_smart_callback_add(zmain->list, "clicked", info_cb, zwin);
	evas_object_size_hint_weight_set(zmain->list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zmain->box2, zmain->list);
	evas_object_show(zmain->list);
}

static void create_zmain(void *data)
{
	zwin *zwin = data;
	zmain *zmain = zwin->zmain;
	Elm_Toolbar_Item *tb;
	int x;

	zmain->box = elm_box_add(zwin->win);
	elm_object_focus_allow_set(zmain->box, 0);
	evas_object_size_hint_weight_set(zmain->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zmain->box);

	zmain->fl = elm_flip_add(zwin->win);
	evas_object_size_hint_weight_set(zmain->fl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zmain->fl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zmain->box, zmain->fl);

	create_zmain_vm(zwin);

	elm_flip_content_front_set(zwin->zmain->fl, zwin->zmain->box2);
	evas_object_show(zwin->zmain->fl);

	zmain->viewbar = elm_toolbar_add(zwin->win);
	elm_toolbar_homogenous_set(zmain->viewbar, 0);
	elm_toolbar_scrollable_set(zmain->viewbar, 0);
	evas_object_size_hint_weight_set(zmain->viewbar, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zmain->viewbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zmain->viewbar);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/exit.png", NULL);
	tb = elm_toolbar_item_add(zmain->viewbar, zmain->icon, "Logout", logout, zwin);

	tb = elm_toolbar_item_add(zmain->bar, NULL, NULL, NULL, NULL);
	elm_toolbar_item_separator_set(tb, 1);
	
	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/computer.png", NULL);
	tb = elm_toolbar_item_add(zmain->viewbar, zmain->icon, "VM view", zmain_vm_view, zwin);
	elm_toolbar_item_select(tb);

	zmain->tb_list = eina_list_append(zmain->tb_list, tb);

	zmain->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zmain->icon, "images/user.png", NULL);
	tb = elm_toolbar_item_add(zmain->viewbar, zmain->icon, "User view", zmain_user_view, zwin);

	zmain->tb_list = eina_list_append(zmain->tb_list, tb);

	zmain->panel = elm_panel_add(zwin->win);
	elm_panel_orient_set(zmain->panel, ELM_PANEL_ORIENT_LEFT);
	elm_panel_content_set(zmain->panel, zmain->viewbar);
	evas_object_size_hint_weight_set(zmain->panel, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zmain->panel, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zmain->box, zmain->panel);
	evas_object_show(zmain->panel);

	zmain->notify = elm_notify_add(zwin->win);
	elm_object_focus_allow_set(zmain->notify, 0);
	zmain->status = elm_label_add(zwin->win);
	elm_object_focus_allow_set(zmain->status, 0);
	elm_notify_content_set(zmain->notify, zmain->status);
	elm_notify_orient_set(zmain->notify, ELM_NOTIFY_ORIENT_BOTTOM_RIGHT);
	elm_notify_timeout_set(zmain->notify, 3);
	elm_box_pack_end(zmain->box, zmain->notify);
	evas_object_show(zmain->status);

	
	x = evas_object_key_grab(zwin->win, "Return", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Up", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Down", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Left", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Right", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "KP_Enter", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Home", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "End", 0, 0, 1);
}

static void zmain_getvms(void *data, zrpc_handle h)
{
	zwin *zwin = data;
	Eina_List *l, *n, *elist = zwin->elist;
	char *xmlvms, *charxml;
	zrpc_vm *vm;
	xmlNode *r;
	vmitem *update, *vmitem;
	int vmfound;

	if (!streq(zwin->view, "main_vm"))
	{
		free(zwin->zcon->recbuf[h]);
		zwin->zcon->recbuf[h] = NULL;
		return;
	}
	
	xmlvms = zwin->zcon->recbuf[h];
	charxml = strdup(strchr(xmlvms, '<'));
	free(xmlvms);
	zwin->zcon->recbuf[h] = NULL;
	
	r = parsechar(charxml);
	l = zwin->list;
	if (!(zwin->list = parsevmsfull(r)))
	{
		elm_label_label_set(zwin->zmain->status, "Response parsing failed!");
		evas_object_show(zwin->zmain->notify);
		xmlFreeNode(r);
		zwin->list = l;
		return;
	}

	EINA_LIST_FREE(l, vm)
		free_zvm(vm);
	/* ensure list exists */
	if (elist)
	{

		/*actually search the vm list*/
		EINA_LIST_FOREACH(zwin->list, n, vm)
		{
#ifdef DEBUG
			printf("DEBUG: Checking genlist for vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
#endif
//			char *find = NULL;
			vmfound = 0;
			/*can't use list_data_find because pointers are different :(*/
			EINA_LIST_FOREACH(zwin->elist, l, update)
				if (streq(update->uuid, vm->uuid))
				{
					vmfound = 1;
					break;
				}
			if (vmfound)
				EINA_LIST_FOREACH(zwin->elist, l, update)
				{	/*if uuid exists, update vm*/
					if (streq(update->uuid, vm->uuid))
					{
#ifdef DEBUG
						printf("GENLIST: Updating vm with uuid: %s\n", update->uuid);
#endif
						/* re-set the data */
						update->vm = vm;
						elm_genlist_item_data_set(update->item, update);
						break;
					}
				}
			else
			{
#ifdef DEBUG
				printf("GENLIST: Not found!\n");
				printf("GENLIST: Adding new vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
#endif
				vmitem = new_vmitem();
				vmitem->uuid = strdup(vm->uuid);
				vmitem->state = strdup(vm->state);
				vmitem->vm = vm;
				vmitem->item = elm_genlist_item_append(zwin->zmain->list, zwin->zmain->itc,
                                      (void *)vmitem /* item data */,
                                      NULL/* parent */,
                                      ELM_GENLIST_ITEM_NONE,
                                      gl_sel/* func */,
                                      (void *)zwin/* func data */);
				/*add to list of vmitems*/
				zwin->elist = eina_list_append(zwin->elist, vmitem);
			}

		}
	}
	else 
		EINA_LIST_FOREACH(zwin->list, l, vm)
			{
#ifdef DEBUG
				printf("GENLIST: Adding new vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
#endif
				vmitem = new_vmitem();
				vmitem->uuid = strdup(vm->uuid);
				vmitem->state = strdup(vm->state);
				vmitem->vm = vm;
				vmitem->item = elm_genlist_item_append(zwin->zmain->list, zwin->zmain->itc,
					(void *)vmitem /* item data */,
					NULL/* parent */,
					ELM_GENLIST_ITEM_NONE,
					gl_sel/* func */,
					(void *)zwin/* func data */);
				/*add to list of vmitems*/
				zwin->elist = eina_list_append(zwin->elist, vmitem);
			}

	EINA_LIST_FOREACH_SAFE(zwin->elist, l, elist, update)
	{
		vmfound = 0;
		EINA_LIST_FOREACH(zwin->list, n, vm)
			if (streq(update->uuid, vm->uuid))
			{
				vmfound = 1;
				break;
			}

		if (!vmfound)
		{
			elm_genlist_item_del(update->item);
			zwin->elist = eina_list_remove_list(zwin->elist, l);
			free_vmitem(update);
		}
	}

	elm_label_label_set(zwin->zmain->status, "VM info successfully refreshed!");
	evas_object_show(zwin->zmain->notify);
}

static void zmain_getusers(void *data, zrpc_handle h)
{
	zrpc_meta_struct *meta;
	zwin *zwin;
	Eina_List *l, *n, *elist, *users;
	useritem *update, *useritem;
	zrpc_user *user;
	int ufound;

	if (!(meta = data)) return;
	if (!(zwin = meta->cbd)) return;
	if (!(users = meta->extra)) return;

	if (!streq(zwin->view, "main_user")) return;
	elist = zwin->elist;
	zwin->list = users;
	
	/* ensure list exists */
	if (elist)
	{

		/*actually search the user list*/
		EINA_LIST_FOREACH(zwin->list, n, user)
		{
#ifdef DEBUG
			printf("DEBUG: Checking genlist for user:\n\tuid {%d}\n\tname {%s}\n", user->uid, user->name);
#endif
//			char *find = NULL;
			ufound = 0;
			/*can't use list_data_find because it's just an int :(*/
			EINA_LIST_FOREACH(zwin->elist, l, update)
				if (update->uid == user->uid)
				{
					ufound = 1;
					break;
				}
			if (ufound)
				EINA_LIST_FOREACH(zwin->elist, l, update)
				{	/*if uid exists, update user*/
					if (update->uid == user->uid)
					{
#ifdef DEBUG
						printf("GENLIST: Updating user with uid: %d\n", update->uid);
#endif
						/* re-set the data */
						update->user = user;
						elm_genlist_item_data_set(update->item, update);
						break;
					}
				}
			else
			{
#ifdef DEBUG
				printf("GENLIST: Not found!\n");
				printf("GENLIST: Adding new user:\n\tuid {%d}\n\tname {%s}\n", user->uid, user->name);
#endif
				useritem = new_useritem();
				useritem->uid = user->uid;
				useritem->user = user;
				useritem->item = elm_genlist_item_append(zwin->zmain_user->list, zwin->zmain_user->itc,
                                      (void *)useritem /* item data */,
                                      NULL/* parent */,
                                      ELM_GENLIST_ITEM_NONE,
                                      gl_sel/* func */,
                                      (void *)zwin/* func data */);
				/*add to list of useritems*/
				zwin->elist = eina_list_append(zwin->elist, useritem);
			}

		}
	}
	else 
		EINA_LIST_FOREACH(zwin->list, l, user)
			{
				useritem = new_useritem();
				useritem->uid = user->uid;
				useritem->user = user;
#ifdef DEBUG
				printf("GENLIST: Adding new user:\n\tuid {%d}\n\tname {%s}\n", useritem->uid, useritem->user->name);
#endif
				useritem->item = elm_genlist_item_append(zwin->zmain_user->list, zwin->zmain_user->itc,
					(void *)useritem /* item data */,
					NULL/* parent */,
					ELM_GENLIST_ITEM_NONE,
					gl_sel/* func */,
					(void *)zwin/* func data */);
				/*add to list of useritems*/
				zwin->elist = eina_list_append(zwin->elist, useritem);
			}

	EINA_LIST_FOREACH_SAFE(zwin->elist, l, elist, update)
	{
		ufound = 0;
		EINA_LIST_FOREACH(zwin->list, n, user)
			if (update->uid == user->uid)
			{
				ufound = 1;
				break;
			}

		if (!ufound)
		{
			elm_genlist_item_del(update->item);
			zwin->elist = eina_list_remove_list(zwin->elist, l);
			free_useritem(update);
		}
	}

	elm_label_label_set(zwin->zmain->status, "User info successfully refreshed!");
	evas_object_show(zwin->zmain->notify);
}

static int zmain_job_getvms(void *data)
{
	zwin *zwin = data;
	if (!zrpc_VM_getVMsFull(zwin->zcon, &zmain_getvms, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection failed, retrying");
	else
		elm_label_label_set(zwin->zmain->status, "Adding job to refresh vm info...");

	evas_object_show(zwin->zmain->notify);
	
	return ECORE_CALLBACK_RENEW;
}

static int zmain_job_getusers(void *data)
{
	zwin *zwin = data;
	if (!meta_getUsersFull(zwin->zcon, &zmain_getusers, zwin))
		elm_label_label_set(zwin->zmain->status, "Connection failed, retrying");
	else
		elm_label_label_set(zwin->zmain->status, "Adding job to refresh user info...");

	evas_object_show(zwin->zmain->notify);
	
	return ECORE_CALLBACK_RENEW;
}

Eina_Bool gl_state_get(const void *data, Evas_Object *obj, const char *part)
{
	return EINA_FALSE;
}
void gl_del(const void *data, Evas_Object *obj)
{
}
char *gl_vm_label_get(const void *data, Evas_Object *obj, const char *part)
{
	const vmitem *item = data;
	const zrpc_vm *vm;
	char buf[256];
	char *type;

	vm = item->vm;
	if (streq(vm->type, "para"))
		type = "Paravirtualized";
	else
		type = "HVM";
		
	if (streq(part, "elm.text"))
		snprintf(buf, sizeof(buf), "%s (%s guest: %s)", vm->name, type, vm->os);
	else if (streq(part, "elm.text.sub"))
		snprintf(buf, sizeof(buf), "UUID: %s", vm->uuid);

#ifdef EDEBUG
printf("GENLIST: setting label for %s to %s\n", part, buf);
#endif
	
	return strdup(buf);
}

char *gl_user_label_get(const void *data, Evas_Object *obj, const char *part)
{
	const useritem *item = data;
	const zrpc_user *user;
	char buf[256];

	user = item->user;

	if (streq(part, "elm.text"))
		snprintf(buf, sizeof(buf), "%s (%s)", user->name, user->email);
	else if (streq(part, "elm.text.sub"))
		snprintf(buf, sizeof(buf), "UID: %d", user->uid);
#ifdef EDEBUG
printf("GENLIST: setting label for %s to %s\n", part, buf);
#endif

	return strdup(buf);
}


Evas_Object *gl_vm_icon_get(const void *data, Evas_Object *obj, const char *part)
{
	const vmitem *item = data;
	const zrpc_vm *vm;
	char *buf;
	Evas_Object *ic;

	vm = item->vm;
	ic = elm_icon_add(obj);
	if (streq(part, "elm.swallow.icon"))
		buf = get_os_icon(vm);
/* 	sets icon at right side of list item */
	else if (streq(part, "elm.swallow.end"))
		buf = get_state_icon(vm->state);

#ifdef EDEBUG
printf("GENLIST: setting icon for %s to %s\n", part, buf);
#endif

	elm_icon_file_set(ic, buf, NULL);
	free(buf);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	return ic;
}

Evas_Object *gl_user_icon_get(const void *data, Evas_Object *obj, const char *part)
{

	const useritem *item = data;
	const zrpc_user *user;
	char *buf;
	Evas_Object *ic;

	user = item->user;
	ic = elm_icon_add(obj);
	if (streq(part, "elm.swallow.icon"))
	{
		buf = get_access_icon(user->uid);
		elm_icon_file_set(ic, buf, NULL);
		free(buf);
	}
/*
	else if (streq(part, "elm.swallow.end"))
	{
		buf = get_lang_icon(user->language);
		elm_icon_file_set(ic, buf, NULL);
		free(buf);
	}
*/

#ifdef EDEBUG
printf("GENLIST: setting icon for %s to %s\n", part, buf);
#endif

	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	return ic;

	return NULL;
}

