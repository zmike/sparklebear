#include "sparklebear.h"

static void
user_action_cb(const char *reply, void *data)
{
	xmlNode *r;
	Elm_Genlist_Item *gl;
	useritem *item;
	zrpc_user *user;

	if (!reply) return;
	if (!(r = xml_parse_xml(reply)))
                return;
	if (xml_parse_int(r))
	{
		elm_label_label_set(win->main_vm->status, "Action was successful!");
		evas_object_show(win->main_vm->notify);
		if (strstr(win->view, "main"))
		{
			gl = elm_genlist_selected_item_get(win->main_user->list);
			if (gl)
			{
				item = (useritem*)elm_genlist_item_data_get(gl);
				user = item->user;
				win->list = eina_list_remove(win->list, user);
				#ifdef DEBUG
				printf("Removing %d:%s from all lists...\n", user->uid, user->name);
				#endif
				win->elist = eina_list_remove(win->elist, item);
				free_useritem(item);
				elm_genlist_item_del(gl);
			}
		}
/*		else if (strstr(win->view, "info"))
			free(stat);*/
		return;
	}
	else
	{
		elm_label_label_set(win->main_vm->status, "Action failed!");
		evas_object_show(win->main_vm->notify);
	}
}

void
user_remove_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Genlist_Item *gl;
	int uid;
	useritem *item;

	if (!strcmp(win->view, "main_user"))
	{
		gl = elm_genlist_selected_item_get(win->main_user->list);
		if (!gl)
			return;
		item = (useritem*)elm_genlist_item_data_get(gl);
		elm_toolbar_item_unselect_all(win->main_user->bar);
		uid = item->user->uid;
	}
	else if (strstr(win->view, "info"))
		uid = win->info->uid;

	/*FIXME: error checking?*/

		
	if (!zrpc_User_removeUser(uid, zcon, user_action_cb, NULL))
		elm_label_label_set(win->main_vm->status, "Connection to zrpc failed!");
	else
		elm_label_label_set(win->main_vm->status, "Connection succeeded!");

	evas_object_show(win->main_vm->notify);
	if (strstr(win->view, "hover")) zinfo_destroy_hover(win, NULL, NULL);
}

void
user_edit_cb(void *data, Evas_Object *obj, void *event_info)
{
	zrpc_user *user;

	if ((user = zinfo_user_findbyuid(win->info)))
	{/*assume edit mode*/

	}
	else
	{/*new user mode*/
		
	}
	
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
	zinfo_job_updateuser(win, NULL, NULL);

	win->view = win->info->userview;

	evas_object_key_ungrab(win->win, "Up", 0, 0);
	evas_object_key_ungrab(win->win, "Down", 0, 0);
	evas_object_key_ungrab(win->win, "Left", 0, 0);
	evas_object_key_ungrab(win->win, "Right", 0, 0);
	evas_object_key_ungrab(win->win, "Home", 0, 0);
	evas_object_key_ungrab(win->win, "End", 0, 0);
}
