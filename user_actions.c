static void
user_action_cb(void *data, const char *reply)
{
	zwin *zwin = data;
	const char *charxml;
	xmlNode *r;
	Elm_Genlist_Item *gl;
	useritem *item;
	zrpc_user *user;

	if (!reply) return;
	charxml = eina_stringshare_add(strchr(reply, '<'));
	eina_stringshare_del(reply);
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
user_edit_cb(void *data, Evas_Object *obj, void *event_info)
{
}

void
user_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	zwin *zwin = data;
	zinfo *zinfo = zwin->zinfo;
	zmain *zmain = zwin->zmain_user;
	Elm_Genlist_Item *gl;
	useritem *item;

	elm_toolbar_item_unselect_all(zmain->bar);
	gl = elm_genlist_selected_item_get(zmain->list);
	if (!gl) return;

	if (!(item = (useritem*)elm_genlist_item_data_get(gl))) return;
	zinfo->uid = item->user->uid;
	zinfo->ulevel = item->user->type;

	create_zinfo_user(zwin);
	zinfo_job_updateuser(zwin, NULL, NULL);

	zwin->view = zinfo->userview;

	evas_object_key_ungrab(zwin->win, "Up", 0, 0);
	evas_object_key_ungrab(zwin->win, "Down", 0, 0);
	evas_object_key_ungrab(zwin->win, "Left", 0, 0);
	evas_object_key_ungrab(zwin->win, "Right", 0, 0);
	evas_object_key_ungrab(zwin->win, "Home", 0, 0);
	evas_object_key_ungrab(zwin->win, "End", 0, 0);
}
