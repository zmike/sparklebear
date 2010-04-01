void zlogin_try(void *data, Evas_Object *obj, void *event_info);

static void
zlogin_keybind(void *data, Evas_Event_Key_Down *key)
{
		zwin *zwin = data;
		zlogin *zlogin = zwin->zlogin;
		Evas_Object *f;

		if (streq(key->keyname, "Escape"))
			exit_wrapper(zwin, NULL, NULL);
		else if (streq(key->keyname, "Return") || streq(key->keyname, "KP_Enter"))
			zlogin_try(zwin, NULL, NULL);
		else if (streq(key->keyname, "Tab"))
		{
			if (!zlogin->lp->next) zlogin->lp = zlogin->lp->prev;
			else zlogin->lp = zlogin->lp->next;
			f = zlogin->lp->data;
			elm_object_focus(f);
		}
}

static int label_update(void *data)
{
	zlogin *zlogin = data;
	if (!zlogin->lt)
		return ECORE_CALLBACK_CANCEL;
	Evas_Object *label = zlogin->stl;
	const char *text = elm_label_label_get(label);
	if streq(text, "Authenticating.")
		elm_label_label_set(label, "Authenticating..");
	else if streq(text, "Authenticating..")
		elm_label_label_set(label, "Authenticating...");
	else
		elm_label_label_set(label, "Authenticating.");
	return ECORE_CALLBACK_RENEW;
}

void zlogin_start(void *data)
{
	zwin *zwin = data;
	zlogin *zlogin = zwin->zlogin;
	
	zlogin->pb = elm_progressbar_add(zwin->win);
	elm_object_style_set(zlogin->pb, "wheel");
	elm_progressbar_label_set(zlogin->pb, "Style: wheel");
	elm_progressbar_pulse(zlogin->pb, EINA_TRUE);
	evas_object_size_hint_weight_set(zlogin->pb, EVAS_HINT_EXPAND, 0.0);
	elm_box_pack_start(zlogin->box2, zlogin->pb);
	evas_object_show(zlogin->pb);

	elm_label_label_set(zlogin->stl, "Authenticating.");
	elm_notify_timeout_set(zlogin->status, 100);

	zlogin->lt = ecore_timer_add(0.5, label_update, zlogin);

}

void zlogin_stop(void *data)
{
	zlogin *zlogin = data;
	elm_notify_timeout_set(zlogin->status, 3);
	elm_progressbar_pulse(zlogin->pb, 0);
	evas_object_del(zlogin->pb);
	ecore_timer_del(zlogin->lt);
	
}

void zlogin_test(void *data, zrpc_handle h)
{
	zwin *zwin = data;
	zlogin *zlogin = zwin->zlogin;
	Eina_List *lp = zlogin->lp;
	Evas_Object *l = lp->data;
	Evas_Object *p = lp->next->data;
	int zwidth = 800, zheight = 600;
	char *ret, *tmp, *charxml;
	xmlNode *r;
	
	if (!zwin->zcon->zcookie) zwin->zcon->zcookie = calloc(37, sizeof(char));

	if ((ret = zwin->zcon->recbuf[h]))
	{
		tmp = strstr(ret, "sessid=");
		sscanf(tmp, "sessid=%[^;];", zwin->zcon->zcookie);
		printf("Cookie grabbed: %s\n", zwin->zcon->zcookie);
		tmp = NULL;
		charxml = strdup(strchr(ret, '<'));
		free(ret);
		zwin->zcon->recbuf[h] = NULL;

		printf("parsing login...\n");
		r = parsechar(charxml);
	
		if (parseint(r))
		{
			evas_object_key_ungrab(zwin->win, "Tab", 0, 0);
			evas_object_smart_callback_del(zlogin->loginbutton, "clicked", zlogin_try);
			evas_object_smart_callback_del(zlogin->cancelbutton, "clicked", exit_wrapper);
			printf("SUCCESS!\n");

			zlogin_stop(zlogin);

			create_zmain(zwin);
			zmain_job_getvms(zwin);
			
			elm_flip_content_back_set(zwin->fl, zwin->zmain->box);

			elm_label_label_set(zwin->zmain->status, "Fetching vms...");
			evas_object_show(zwin->zmain->notify);
			evas_object_show(zwin->zmain->fl);
			elm_flip_go(zwin->fl, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
			sprintf(zwin->view, "main_vm");
			evas_object_del(zlogin->box);
			eina_list_free(zlogin->lp);
			zlogin->lp = NULL;
			elm_win_title_set(zwin->win, "zEntific Control Center");

			evas_object_resize(zwin->win, zwidth, zheight);
			evas_object_move(zwin->win, (zwin->xres/2)-(zwidth/2), (zwin->yres/2)-(zheight/2));
			printf("Starting vm info timer...\n");
			zwin->timerget = ecore_timer_add(zwin->vmtimer, zmain_job_getvms, zwin);

			return;
		}
	}

	zlogin_stop(zlogin);
	elm_label_label_set(zlogin->stl, "Login failed!");
	evas_object_show(zlogin->status);
	elm_object_disabled_set(l, EINA_FALSE);
	elm_object_disabled_set(p, EINA_FALSE);
	elm_object_focus(l);
	elm_scrolled_entry_cursor_end_set(l);

}

void zlogin_try(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zlogin *zlogin = zwin->zlogin;
	Eina_List *lp = zlogin->lp;
	Evas_Object *l = lp->data;
	Evas_Object *p = lp->next->data;
	
	const char *username = elm_scrolled_entry_entry_get(l);
	const char *password = elm_scrolled_entry_entry_get(p);
	printf("%s:%s\n", username, password);
	
	elm_object_disabled_set(l, EINA_TRUE);
	elm_object_disabled_set(p, EINA_TRUE);

	zlogin_start(zwin);

	if (!zrpc_User_login(username, password, zwin->zcon, &zlogin_test, zwin))
	{
		zlogin_stop(zlogin);
		elm_label_label_set(zlogin->stl, "Remote host could not be reached!");
		evas_object_show(zlogin->status);
		elm_object_disabled_set(l, EINA_FALSE);
		elm_object_disabled_set(p, EINA_FALSE);
		elm_object_focus(l);
		elm_scrolled_entry_cursor_end_set(l);
	}

}

static void
create_zlogin(void *data)
{
	zwin *zwin = data;
	zlogin *zlogin = zwin->zlogin;
	int x;
	zlogin->lp = NULL;

	Evas_Object *l, *p;

	zlogin->box = elm_box_add(zwin->win);
	elm_object_focus_allow_set(zlogin->box, 0);
	evas_object_size_hint_weight_set(zlogin->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zlogin->box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(zlogin->box);

	zlogin->icon = elm_icon_add(zwin->win);
	elm_icon_file_set(zlogin->icon, zlogo, NULL);
	elm_icon_scale_set(zlogin->icon, 0, 0);
	elm_icon_smooth_set(zlogin->icon, 1);
	elm_box_pack_end(zlogin->box, zlogin->icon);
	elm_object_focus_allow_set(zlogin->icon, 0);
	evas_object_show(zlogin->icon);
	
	zlogin->fr = elm_frame_add(zwin->win);
	evas_object_size_hint_weight_set(zlogin->fr, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zlogin->fr, EVAS_HINT_FILL, 0.0);
	elm_frame_label_set(zlogin->fr, "Username");
	
	l = elm_scrolled_entry_add(zwin->win);
	elm_scrolled_entry_scrollbar_policy_set(l, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(l, 1);
	elm_scrolled_entry_entry_set(l, "admin");
	elm_scrolled_entry_select_all(l);
	elm_object_focus(l);
	elm_scrolled_entry_cursor_end_set(l);
	evas_object_show(l);
		
	elm_frame_content_set(zlogin->fr, l);
	elm_box_pack_end(zlogin->box, zlogin->fr);
	evas_object_show(zlogin->fr);


	zlogin->fr2 = elm_frame_add(zwin->win);
	elm_frame_label_set(zlogin->fr2, "Password");
	evas_object_size_hint_weight_set(zlogin->fr2, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(zlogin->fr2, EVAS_HINT_FILL, 0.0);

	p = elm_scrolled_entry_add(zwin->win);
	elm_scrolled_entry_scrollbar_policy_set(p, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(p, 1);
	elm_scrolled_entry_password_set(p, 1);
	elm_scrolled_entry_entry_set(p, "sparklebear");
	evas_object_show(p);

	elm_frame_content_set(zlogin->fr2, p);
	elm_box_pack_end(zlogin->box, zlogin->fr2);
	evas_object_show(zlogin->fr2);
	
	zlogin->hbox = elm_box_add(zwin->win);
	elm_box_horizontal_set(zlogin->hbox, 1);
	elm_box_pack_end(zlogin->box, zlogin->hbox);
	elm_object_focus_allow_set(zlogin->hbox, 0);
	evas_object_show(zlogin->hbox);
	
	
	zlogin->loginbutton = elm_button_add(zwin->win);
	elm_button_label_set(zlogin->loginbutton, "Login");
	elm_object_focus_allow_set(zlogin->loginbutton, 0);
	elm_box_pack_end(zlogin->hbox, zlogin->loginbutton);
	evas_object_smart_callback_add(zlogin->loginbutton, "clicked", zlogin_try, zwin);
	evas_object_show(zlogin->loginbutton);
	
	
	zlogin->cancelbutton = elm_button_add(zwin->win);
	elm_button_label_set(zlogin->cancelbutton, "Cancel");
	elm_object_focus_allow_set(zlogin->cancelbutton, 0);
	elm_box_pack_end(zlogin->hbox, zlogin->cancelbutton);
	evas_object_smart_callback_add(zlogin->cancelbutton, "clicked", exit_wrapper, NULL);
	evas_object_show(zlogin->cancelbutton);

	zlogin->box2 = elm_box_add(zwin->win);
	elm_object_focus_allow_set(zlogin->box2, 0);
	elm_box_horizontal_set(zlogin->box2, 1);
	elm_box_pack_after(zlogin->box, zlogin->box2, zlogin->icon);
	zlogin->status = elm_notify_add(zwin->win);
	elm_object_focus_allow_set(zlogin->status, 0);
	zlogin->stl = elm_label_add(zwin->win);
	elm_object_focus_allow_set(zlogin->stl, 0);
	elm_notify_content_set(zlogin->status, zlogin->stl);
	elm_notify_orient_set(zlogin->status, ELM_NOTIFY_ORIENT_CENTER);
	elm_notify_timeout_set(zlogin->status, 3);
	elm_box_pack_end(zlogin->box2, zlogin->status);
	evas_object_show(zlogin->stl);

	zlogin->lp = eina_list_append(zlogin->lp, l);
	zlogin->lp = eina_list_append(zlogin->lp, p);

	x = evas_object_key_grab(zwin->win, "Return", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "Tab", 0, 0, 1);
	x = evas_object_key_grab(zwin->win, "KP_Enter", 0, 0, 1);
}
