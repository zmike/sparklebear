#include "sparklebear.h"

static void
user_action_cb(const char *reply, void *data)
{
	xmlNode *r;
	useritem *item;
	zrpc_user *user;
	Eina_List *l;

	if (!reply) return;
	if (!(r = xml_parse_xml(reply)))
                return;
	if (xml_parse_int(r))
	{
		elm_label_label_set(win->main_vm->status, "Action was successful!");
		evas_object_show(win->main_vm->notify);
		if (win->view == win->info->useredit)
		{
			EINA_LIST_FOREACH(win->elist, l, item)
				if ((item->user->uid == win->info->uid) || (item->user->uid == win->info->newuid))
					break;

			if ((item->user->uid == win->info->uid) || (item->user->uid == win->info->newuid))
			{
				user = item->user;
				win->list = eina_list_remove(win->list, user);
				#ifdef DEBUG
				printf("Removing %d:%s from all lists...\n", user->uid, user->name);
				#endif
				win->elist = eina_list_remove_list(win->elist, l);
				elm_genlist_item_del(item->item);
				free_useritem(item);
			}
		}
		zmain_job_getusers(NULL);
		return;
	}

	elm_label_label_set(win->main_vm->status, "Action failed!");
	evas_object_show(win->main_vm->notify);
}

void
user_remove_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Genlist_Item *gl;
	int uid;
	useritem *item;

	if (win->view == win->main_user->view)
	{
		gl = elm_genlist_selected_item_get(win->main_user->list);
		if (!gl)
			return;
		item = (useritem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_user->bar);
		uid = item->user->uid;
	}
	else if (win->view == win->info->useredit)
		uid = win->info->uid;

	/*FIXME: error checking?*/

		
	if (!zrpc_User_remove(uid, zcon, user_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (win->view == win->main_user->view) zinfo_destroy_hover(NULL, NULL, NULL);
}

void
user_apply_cb(void *data, Evas_Object *obj, void *event_info)
{
	const char *id, *name, *email, *test;
	int type = -1, active = -1, uid = -1;
	zrpc_user *user, *moduser;

	active = elm_toggle_state_get(win->info->state_label);
		
	type = elm_slider_value_get(win->info->level);
	if (!(id = elm_scrolled_entry_entry_get(win->info->id)) || (atoi(id) < 0))
	{
		elm_label_label_set(win->main_vm->status, "Error! UID must be set and non-negative!");
		evas_object_show(win->main_vm->notify);
		return;
	}
	uid = atoi(id);
	if (!(name = elm_scrolled_entry_entry_get(win->info->name)))
	{
		elm_label_label_set(win->main_vm->status, "Error! Name must be set!");
		evas_object_show(win->main_vm->notify);
		return;
	}
	if ((email = elm_scrolled_entry_entry_get(win->info->email)))
	{/* FIXME: more stupid error checking for annoying people */
		if (!(test = strchr(email, '@')))
		{
			elm_label_label_set(win->main_vm->status, "Error! email must be blank or valid!");
			evas_object_show(win->main_vm->notify);
			return;
		}
	}

	if (win->view == win->info->useradd)
	{
		if (zinfo_user_findbyuid(atoi(id)))
		{
			elm_label_label_set(win->main_vm->status, "Error! That UID is already in use!");
			evas_object_show(win->main_vm->notify);
			return;
		}


	}
	else
	{
		if (!(moduser = zinfo_user_findbyuid(win->info->uid)))
		{
			elm_label_label_set(win->main_vm->status, "Error! That UID does not exist somehow! WTF!");
			evas_object_show(win->main_vm->notify);
			return;
		}
		if ((uid != win->info->uid) && (zinfo_user_findbyuid(uid)))
		{
			elm_label_label_set(win->main_vm->status, "Error! That UID belongs to someone else!");
			evas_object_show(win->main_vm->notify);
			return;
		}
	}

	user = zuser_new();
	user->active = active;
	user->type = type;
	user->uid = uid;
	user->name = eina_stringshare_add(name);
	user->email = eina_stringshare_add(email);
	user->language = eina_stringshare_add("en_US");
	if (win->view == win->info->useradd)
		active = zrpc_User_add(user, zcon, user_action_cb, NULL);
	else
		active = zrpc_User_modify(win->info->uid, user, zcon, user_action_cb, NULL);
	if (!active)
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
	{
		if (win->view == win->info->useredit) win->info->newuid = user->uid;
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");
	}
	evas_object_show(win->main_vm->notify);
	zuser_free(user);
}

void
user_add_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_toolbar_item_unselect_all(win->main_user->bar);
	create_info_user();

	elm_label_label_set(win->info->lb, "Access level: NONE");
	elm_icon_file_set(win->info->level_icon, "images/edit_clear_locationbar.png", NULL);
	elm_icon_file_set(win->info->state_icon, "images/dialog_close.png", NULL);
	/* inactive */
	elm_toggle_state_set(win->info->state_label, 0);
	/* no access */
	elm_slider_value_set(win->info->level, 5);
	/* error-producing uid */
	elm_scrolled_entry_entry_set(win->info->id, "-1");
	/* dummy data */
	elm_scrolled_entry_entry_set(win->info->name, "username");
	elm_scrolled_entry_entry_set(win->info->email, "email@address.suffix");
	

	win->view = win->info->useradd;

	evas_object_key_ungrab(win->win, "Up", 0, 0);
	evas_object_key_ungrab(win->win, "Down", 0, 0);
	evas_object_key_ungrab(win->win, "Left", 0, 0);
	evas_object_key_ungrab(win->win, "Right", 0, 0);
	evas_object_key_ungrab(win->win, "Home", 0, 0);
	evas_object_key_ungrab(win->win, "End", 0, 0);
}

void
user_info_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Genlist_Item *gl;
	useritem *item;

	elm_toolbar_item_unselect_all(win->main_user->bar);
	gl = elm_genlist_selected_item_get(win->main_user->list);
	if (!gl) return;

	if (!(item = (useritem*)elm_genlist_item_data_get(gl))) return;
	win->info->uid = item->user->uid;
	win->info->ulevel = item->user->type;

	create_info_user();
	zinfo_updateuser(NULL, NULL, NULL);

	win->view = win->info->useredit;

	evas_object_key_ungrab(win->win, "Up", 0, 0);
	evas_object_key_ungrab(win->win, "Down", 0, 0);
	evas_object_key_ungrab(win->win, "Left", 0, 0);
	evas_object_key_ungrab(win->win, "Right", 0, 0);
	evas_object_key_ungrab(win->win, "Home", 0, 0);
	evas_object_key_ungrab(win->win, "End", 0, 0);
}
