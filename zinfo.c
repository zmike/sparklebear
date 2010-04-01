static void
zinfo_updatevm(void *data, zrpc_handle h)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;
//	Eina_List *l, *l2, *hsel;
	zrpc_vm *vm;
//	zrpc_disk *d, *s;
//	zrpc_vif *v, *b;
//	Elm_Hoversel_Item *it;
//	int found = 0;
	char *xmlvm, *charxml, *icon, *state, tmp[13];
	xmlNode *r;
	
	xmlvm = zwin->zcon->recbuf[h];
	charxml = strdup(strchr(xmlvm, '<'));
	free(xmlvm);
	zwin->zcon->recbuf[h] = NULL;
	r = parsechar(charxml);
	if (!(vm = parsevm(r)))
	{
		fprintf(stderr, "No vm returned!\n");
		return;
	}

/*
	hsel = elm_hoversel_items_get(zinfo->disks);

	EINA_LIST_FOREACH(hsel, l, it)
	{
		s = (zrpc_disk*)elm_hoversel_item_data_get(it);
		EINA_LIST_FOREACH(vm->disks, l, d)
			if (streq(s->ext_dev, d->ext_dev))
			{
				elm_hoversel_item_del(it);
				elm_hoversel_item_add(zinfo->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);
				found = 1;
				break;
			}
		if (!found)
			elm_hoversel_item_add(zinfo->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);

		found = 0;
	}
	hsel = elm_hoversel_items_get(zinfo->disks);
	EINA_LIST_FOREACH(vm->disks, l, d)
		if (!eina_list_data_find(hsel, */
		
	icon = get_state_icon(vm->state);
	elm_icon_file_set(zinfo->state_icon, icon, NULL);

	zfree(zinfo->state);
	zinfo->state = NULL;
	zinfo->state = strdup(vm->state);

	state = get_state_name(zinfo->state);
	elm_label_label_set(zinfo->state_label, state);
	
	sprintf(tmp, "%d", vm->uptime);
	elm_label_label_set(zinfo->uptime, tmp);
	elm_progressbar_value_set(zinfo->pct, vm->cpupct);
	/*
	EINA_LIST_FOREACH(vm->vifs, l, v)
		elm_hoversel_item_add(zinfo->vifs, v->name, NULL, ELM_ICON_NONE, NULL, v);
*/

	free_zvm(vm);
	vm = NULL;
	free(icon);
	free(state);
}

static void
zinfo_to_zlogin(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	int zwidth = 396, zheight = 390;

	ecore_timer_del(zwin->timerget);
	create_zlogin(zwin);
	elm_win_title_set(zwin->win, "zEntific Login");

	zrpc_User_logout(zwin->zcon, NULL, NULL);
		
	elm_flip_content_front_set(zwin->fl, zwin->zlogin->box);
	elm_flip_go(zwin->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
	evas_object_resize(zwin->win, zwidth, zheight);
	evas_object_move(zwin->win, (zwin->xres/2)-(zwidth/2), (zwin->yres/2)-(zheight/2));

	sprintf(zwin->view, "login");

	evas_object_hide(zwin->zinfo->frame);
//	evas_object_del(zwin->zinfo->frame);
//	evas_object_hide(zwin->zmain->fl);

	evas_object_hide(zwin->zmain->box);
	evas_object_del(zwin->zmain->box);

	zfree(zwin->zinfo->vmuuid);
	zwin->zinfo->vmuuid = NULL;
	zfree(zwin->zinfo->state);
	zwin->zinfo->state = NULL;
}

static int
zinfo_job_updatevm(void *data)
{
	zwin *zwin = data;	

	if (!zrpc_VM_getVM(zwin->zinfo->vmuuid, zwin->zcon, &zinfo_updatevm, zwin))
	{
		elm_label_label_set(zwin->zmain->status, "Connection failed");
		evas_object_show(zwin->zmain->notify);
	}

	return ECORE_CALLBACK_RENEW;
}

static void
zinfo_to_zmain(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	int zwidth = 800, zheight = 600;
	
	ecore_timer_del(zwin->timerget);
	create_zmain_vm(zwin);

	zwin->timerget = ecore_timer_add(zwin->vmtimer, zmain_job_getvms, zwin);
	ecore_job_add((void*)zmain_job_getvms, zwin);
	
	elm_flip_content_front_set(zwin->zmain->fl, zwin->zmain->box2);
	elm_flip_go(zwin->zmain->fl, ELM_FLIP_ROTATE_X_CENTER_AXIS);
	sprintf(zwin->view, "main_vm");
	evas_object_hide(zwin->zinfo->frame);
	evas_object_hide(zwin->zinfo->hbox);
	evas_object_del(zwin->zinfo->hbox);

	evas_object_resize(zwin->win, zwidth, zheight);
	evas_object_move(zwin->win, (zwin->xres/2)-(zwidth/2), (zwin->yres/2)-(zheight/2));
}

static void
zinfo_destroy_hover(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;

	evas_object_hide(zinfo->hover);
	evas_object_del(zinfo->hover);

	sprintf(zwin->view, "info_vm");
}

static void
zinfo_vm_state_change(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;
	char *state = zinfo->state;

	zinfo->hover = elm_hover_add(zwin->win);
	elm_object_style_set(zinfo->hover, "popout");
	elm_hover_parent_set(zinfo->hover, zwin->win);
	elm_hover_target_set(zinfo->hover, zinfo->state_label);
	evas_object_smart_callback_add(zinfo->hover, "clicked", zinfo_destroy_hover, zwin);

	if ((!state) || streq(state, "b") || streq(state, "r") || streq(state, "NULL"))
	{
		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_suspend.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Pause");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_pause_cb, zwin);
		elm_hover_content_set(zinfo->hover, "top", zinfo->hb);
		evas_object_show(zinfo->hb);
		
		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_restart.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Reboot");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_reboot_cb, zwin);
		elm_hover_content_set(zinfo->hover, "left", zinfo->hb);
		evas_object_show(zinfo->hb);

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Suspend");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_hibernate_cb, zwin);
		elm_hover_content_set(zinfo->hover, "right", zinfo->hb);
		evas_object_show(zinfo->hb);

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_log_out.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Shutdown");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_shutdown_cb, zwin);
		elm_hover_content_set(zinfo->hover, "middle", zinfo->hb);
		evas_object_show(zinfo->hb);


	}
	else if (streq(state, "p"))
	{
		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/1rightarrow.png", NULL);

		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Unpause");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_unpause_cb, zwin);
		elm_hover_content_set(zinfo->hover, "top", zinfo->hb);
		evas_object_show(zinfo->hb);

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Suspend");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_hibernate_cb, zwin);
		elm_hover_content_set(zinfo->hover, "right", zinfo->hb);
		evas_object_show(zinfo->hb);

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_log_out.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Shutdown");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_shutdown_cb, zwin);
		elm_hover_content_set(zinfo->hover, "middle", zinfo->hb);
		evas_object_show(zinfo->hb);
	}
	else if (streq(state, "d"))
	{

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Suspend");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_hibernate_cb, zwin);
		elm_hover_content_set(zinfo->hover, "right", zinfo->hb);
		evas_object_show(zinfo->hb);

		zinfo->ic = elm_icon_add(zwin->win);
		elm_icon_file_set(zinfo->ic, "images/system_suspend.png", NULL);
		evas_object_show(zinfo->ic);
		zinfo->hb = elm_button_add(zwin->win);
		elm_button_icon_set(zinfo->hb, zinfo->ic);
		elm_button_label_set(zinfo->hb, "Pause");
		elm_object_style_set(zinfo->hb, "anchor");
		evas_object_smart_callback_add(zinfo->hb, "clicked", vm_pause_cb, zwin);
		elm_hover_content_set(zinfo->hover, "top", zinfo->hb);
		evas_object_show(zinfo->hb);
	}

	zinfo->ic = elm_icon_add(zwin->win);
	elm_icon_file_set(zinfo->ic, "images/button_cancel.png", NULL);
	evas_object_show(zinfo->ic);
	zinfo->hb = elm_button_add(zwin->win);
	elm_button_icon_set(zinfo->hb, zinfo->ic);
	elm_button_label_set(zinfo->hb, "Destroy");
	elm_object_style_set(zinfo->hb, "anchor");
	evas_object_smart_callback_add(zinfo->hb, "clicked", vm_destroy_cb, zwin);
	elm_hover_content_set(zinfo->hover, "bottom", zinfo->hb);
	evas_object_show(zinfo->hb);

	sprintf(zwin->view, "info_hover");
	evas_object_show(zinfo->hover);	

}

static void
zinfo_vm_keybind(void *data, Evas_Event_Key_Down *key)
{
	zwin *zwin = data;

	if (streq(zwin->view, "info_vm"))
		if (streq(key->keyname, "Escape"))
			zinfo_to_zmain(zwin, NULL, NULL);
	if (streq(zwin->view, "info_hover"))
		if (streq(key->keyname, "Escape"))
			zinfo_destroy_hover(zwin, NULL, NULL);

}

static void
create_zinfo_vm(void *data)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;

	zinfo->frame = elm_frame_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zinfo->frame);

	zinfo->hbox = elm_box_add(zwin->win);
//	elm_box_homogenous_set(zinfo->hbox, 1);
	elm_box_horizontal_set(zinfo->hbox, 1);
	evas_object_size_hint_weight_set(zinfo->hbox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->hbox, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_frame_content_set(zinfo->frame, zinfo->hbox);
	evas_object_show(zinfo->hbox);
	
	zinfo->vbox1 = elm_box_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->vbox1, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->vbox1, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zinfo->hbox, zinfo->vbox1);
	evas_object_show(zinfo->vbox1);

	zinfo->bi = elm_icon_add(zwin->win);
	elm_icon_file_set(zinfo->bi, "images/player_rew.png", NULL);
	evas_object_show(zinfo->bi);

	zinfo->back = elm_button_add(zwin->win);
	elm_button_icon_set(zinfo->back, zinfo->bi);
	elm_button_label_set(zinfo->back, "Back");
	evas_object_size_hint_weight_set(zinfo->back, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->back, 0.0, 0.0);
	elm_box_pack_end(zinfo->vbox1, zinfo->back);
	evas_object_smart_callback_add(zinfo->back, "clicked", zinfo_to_zmain, zwin);
	evas_object_show(zinfo->back);

	zinfo->os_icon = elm_icon_add(zwin->win);
	elm_icon_scale_set(zinfo->os_icon, 0, 0);
	elm_icon_smooth_set(zinfo->os_icon, 1);
	evas_object_size_hint_weight_set(zinfo->os_icon, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->os_icon, 0.0, 0.0);
	elm_box_pack_end(zinfo->vbox1, zinfo->os_icon);
	evas_object_show(zinfo->os_icon);

	zinfo->os = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->os, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->os, 0.5, 0.5);
	elm_box_pack_end(zinfo->vbox1, zinfo->os);
	evas_object_show(zinfo->os);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox1, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->uuid = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->uuid, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->uuid, 0.5, 0.5);
	elm_box_pack_end(zinfo->vbox1, zinfo->uuid);
	evas_object_show(zinfo->uuid);
	
	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox1, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->puuid = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->puuid, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->puuid, 0.5, 0.5);
	elm_box_pack_end(zinfo->vbox1, zinfo->puuid);
	evas_object_show(zinfo->puuid);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox1, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->disks = elm_hoversel_add(zwin->win);
	elm_hoversel_label_set(zinfo->disks, "VBDs");
	elm_hoversel_hover_parent_set(zinfo->disks, zwin->win);
	evas_object_size_hint_weight_set(zinfo->disks, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->disks, 0.5, 0.5);
	elm_box_pack_end(zinfo->vbox1, zinfo->disks);
	evas_object_show(zinfo->disks);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_box_pack_end(zinfo->hbox, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->vbox2 = elm_box_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->vbox2, 1.0, 1.0);
	evas_object_size_hint_align_set(zinfo->vbox2, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zinfo->hbox, zinfo->vbox2);
	evas_object_show(zinfo->vbox2);

	zinfo->uptime = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->uptime, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->uptime, 0.5, EVAS_HINT_FILL);
	elm_box_pack_end(zinfo->vbox2, zinfo->uptime);
	evas_object_show(zinfo->uptime);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_box_pack_end(zinfo->vbox2, zinfo->sp);
	evas_object_show(zinfo->sp);
	
	zinfo->state_icon = elm_icon_add(zwin->win);
	elm_icon_scale_set(zinfo->state_icon, 0, 0);
	elm_icon_smooth_set(zinfo->state_icon, 1);
	evas_object_size_hint_weight_set(zinfo->state_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->state_icon, 0.0, EVAS_HINT_FILL);
	elm_box_pack_end(zinfo->vbox2, zinfo->state_icon);
	evas_object_smart_callback_add(zinfo->state_icon, "clicked", zinfo_vm_state_change, zwin);
	evas_object_show(zinfo->state_icon);

	zinfo->state_label = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->state_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->state_label, 0.5, 0.0);
	elm_box_pack_end(zinfo->vbox2, zinfo->state_label);
	evas_object_show(zinfo->state_label);

	/* cpus goes here */

	zinfo->pct = elm_progressbar_add(zwin->win);
	elm_progressbar_horizontal_set(zinfo->pct, 1);
	elm_progressbar_value_set(zinfo->pct, 0);
	evas_object_size_hint_weight_set(zinfo->pct, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->pct, 0.5, 1.0);
	elm_box_pack_end(zinfo->vbox2, zinfo->pct);
	evas_object_show(zinfo->pct);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox2, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->vifs = elm_hoversel_add(zwin->win);
	elm_hoversel_label_set(zinfo->vifs, "VIFs");
	elm_hoversel_hover_parent_set(zinfo->vifs, zwin->win);
	evas_object_size_hint_weight_set(zinfo->vifs, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->vifs, 0.5, 1.0);
	elm_box_pack_end(zinfo->vbox2, zinfo->vifs);
	evas_object_show(zinfo->vifs);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_box_pack_end(zinfo->hbox, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->vbox3 = elm_box_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->vbox3, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->vbox3, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(zinfo->hbox, zinfo->vbox3);
	evas_object_show(zinfo->vbox3);

	zinfo->kernel = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->kernel, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->kernel, EVAS_HINT_FILL, 0.5);
	elm_box_pack_end(zinfo->vbox3, zinfo->kernel);
	evas_object_show(zinfo->kernel);

	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox3, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->ramdisk = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->ramdisk, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->ramdisk, EVAS_HINT_FILL, 0.5);
	elm_box_pack_end(zinfo->vbox3, zinfo->ramdisk);
	evas_object_show(zinfo->ramdisk);
	
	zinfo->sp = elm_separator_add(zwin->win);
	elm_separator_horizontal_set(zinfo->sp, 1);
	elm_box_pack_end(zinfo->vbox3, zinfo->sp);
	evas_object_show(zinfo->sp);

	zinfo->cmdline = elm_label_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->cmdline, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zinfo->cmdline, EVAS_HINT_FILL, 0.5);
	elm_box_pack_end(zinfo->vbox3, zinfo->cmdline);
	evas_object_show(zinfo->cmdline);

	zinfo->notesframe = elm_frame_add(zwin->win);
	elm_frame_label_set(zinfo->notesframe, "Notes");
	evas_object_size_hint_weight_set(zinfo->notesframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->notesframe, 0.5, 1.0);
	elm_box_pack_end(zinfo->vbox3, zinfo->notesframe);
	evas_object_show(zinfo->notesframe);

	zinfo->vbox4 = elm_box_add(zwin->win);
	evas_object_size_hint_weight_set(zinfo->vbox4, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->vbox4, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_frame_content_set(zinfo->notesframe, zinfo->vbox4);
	evas_object_show(zinfo->vbox4);

	zinfo->notes = elm_scrolled_entry_add(zwin->win);
	elm_scrolled_entry_scrollbar_policy_set(zinfo->notes, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_line_wrap_set(zinfo->notes, 1);
	evas_object_size_hint_weight_set(zinfo->notes, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zinfo->notes, 0.5, 0.5);
	elm_box_pack_end(zinfo->vbox4, zinfo->notes);
	evas_object_show(zinfo->notes);

	zinfo->notesend = elm_button_add(zwin->win);
	elm_button_label_set(zinfo->notesend, "Save");
	evas_object_smart_callback_add(zinfo->notesend, "clicked", NULL, zwin);
	evas_object_size_hint_weight_set(zinfo->notesend, 0.0, 0.0);
	evas_object_size_hint_align_set(zinfo->notesend, 1.0, 1.0);
	elm_box_pack_end(zinfo->vbox4, zinfo->notesend);
	evas_object_show(zinfo->notesend);
}
