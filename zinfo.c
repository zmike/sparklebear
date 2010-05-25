#include "sparklebear.h"

static void
zinfo_updatevm(const char *reply, void *data)
{
	zinfo *info = win->info;
//	Eina_List *l, *l2, *hsel;
	zrpc_vm *vm;
//	zrpc_disk *d, *s;
//	zrpc_vif *v, *b;
//	Elm_Hoversel_Item *it;
//	int found = 0;
	const char *icon, *state;
	char tmp[13];
	xmlNode *r;
	
	if (!(r = xml_parse_xml(reply)))
                return;
	if (!(vm = xml_parse_vm(r)))
	{
		fprintf(stderr, "No vm returned!\n");
		return;
	}

/*
	hsel = elm_hoversel_items_get(info->disks);

	EINA_LIST_FOREACH(hsel, l, it)
	{
		s = (zrpc_disk*)elm_hoversel_item_data_get(it);
		EINA_LIST_FOREACH(vm->disks, l, d)
			if (!strcmp(s->ext_dev, d->ext_dev))
			{
				elm_hoversel_item_del(it);
				elm_hoversel_item_add(info->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);
				found = 1;
				break;
			}
		if (!found)
			elm_hoversel_item_add(info->disks, d->ext_dev, NULL, ELM_ICON_NONE, NULL, d);

		found = 0;
	}
	hsel = elm_hoversel_items_get(info->disks);
	EINA_LIST_FOREACH(vm->disks, l, d)
		if (!eina_list_data_find(hsel, */
		
	icon = get_state_icon(vm->state);
	elm_icon_file_set(info->state_icon, icon, NULL);

	info->state = eina_stringshare_add(vm->state);

	state = get_state_name(info->state);
	elm_label_label_set(info->state_label, state);
	
	sprintf(tmp, "%d", vm->uptime);
	elm_label_label_set(info->uptime, tmp);
	elm_progressbar_value_set(info->pct, vm->cpupct);
	/*
	EINA_LIST_FOREACH(vm->vifs, l, v)
		elm_hoversel_item_add(info->vifs, v->name, NULL, ELM_ICON_NONE, NULL, v);
*/
	
	zvm_free(vm);
	eina_stringshare_del(info->state);
	eina_stringshare_del(icon);
	eina_stringshare_del(state);
}

void
zinfo_vm_state_change(void *data, Evas_Object *obj, void *event_info)
{
	zinfo *info = win->info;
	const char *state = info->state;

	info->hover = elm_hover_add(win->win);
	elm_object_style_set(info->hover, "popout");
	elm_hover_parent_set(info->hover, win->win);
	elm_hover_target_set(info->hover, info->state_label);
	evas_object_smart_callback_add(info->hover, "clicked", zinfo_destroy_hover, NULL);

	if ((!state) || !strcmp(state, "b") || !strcmp(state, "r") || !strcmp(state, "NULL"))
	{
		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_suspend.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Pause");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_pause_cb, NULL);
		elm_hover_content_set(info->hover, "top", info->hb);
		evas_object_show(info->hb);
		
		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_restart.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Reboot");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_reboot_cb, NULL);
		elm_hover_content_set(info->hover, "left", info->hb);
		evas_object_show(info->hb);

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Suspend");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_hibernate_cb, NULL);
		elm_hover_content_set(info->hover, "right", info->hb);
		evas_object_show(info->hb);

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_log_out.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Shutdown");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_shutdown_cb, NULL);
		elm_hover_content_set(info->hover, "middle", info->hb);
		evas_object_show(info->hb);


	}
	else if (!strcmp(state, "p"))
	{
		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/1rightarrow.png", NULL);

		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Unpause");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_unpause_cb, NULL);
		elm_hover_content_set(info->hover, "top", info->hb);
		evas_object_show(info->hb);

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Suspend");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_hibernate_cb, NULL);
		elm_hover_content_set(info->hover, "right", info->hb);
		evas_object_show(info->hb);

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_log_out.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Shutdown");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_shutdown_cb, NULL);
		elm_hover_content_set(info->hover, "middle", info->hb);
		evas_object_show(info->hb);
	}
	else if (!strcmp(state, "d"))
	{

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_suspend_hibernate.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Suspend");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_hibernate_cb, NULL);
		elm_hover_content_set(info->hover, "right", info->hb);
		evas_object_show(info->hb);

		info->ic = elm_icon_add(win->win);
		elm_icon_file_set(info->ic, "images/system_suspend.png", NULL);
		evas_object_show(info->ic);
		info->hb = elm_button_add(win->win);
		elm_button_icon_set(info->hb, info->ic);
		elm_button_label_set(info->hb, "Pause");
		elm_object_style_set(info->hb, "anchor");
		evas_object_smart_callback_add(info->hb, "clicked", vm_pause_cb, NULL);
		elm_hover_content_set(info->hover, "top", info->hb);
		evas_object_show(info->hb);
	}

	info->ic = elm_icon_add(win->win);
	elm_icon_file_set(info->ic, "images/button_cancel.png", NULL);
	evas_object_show(info->ic);
	info->hb = elm_button_add(win->win);
	elm_button_icon_set(info->hb, info->ic);
	elm_button_label_set(info->hb, "Destroy");
	elm_object_style_set(info->hb, "anchor");
	evas_object_smart_callback_add(info->hb, "clicked", vm_destroy_cb, NULL);
	elm_hover_content_set(info->hover, "bottom", info->hb);
	evas_object_show(info->hb);

	win->view = info->vmhover;
	evas_object_show(info->hover);	
}
void
zinfo_updateuser_level(void *data, Evas_Object *obj, void *event_info)
{
	const char *tmp;
	char buf[128];
	int x;
	
	x = (int)elm_slider_value_get(win->info->level);

	if (x == win->info->ulevel) return;

	win->info->ulevel = x;

	tmp = get_access_icon(x);
	elm_icon_file_set(win->info->level_icon, tmp, NULL);
	eina_stringshare_del(tmp);

	tmp = get_access_name(x);
#ifdef DEBUG
printf("DEBUG: setting level to %s\n", tmp);
#endif
	sprintf(buf, "Access level: %s", tmp);
	elm_label_label_set(win->info->lb, buf);

	eina_stringshare_del(tmp);
}


void
zinfo_updateuser_state(void *data, Evas_Object *obj, void *event_info)
{
	Eina_Bool x;

	x = elm_toggle_state_get(win->info->state_label);

#ifdef DEBUG
printf("DEBUG: setting user to %s state\n", (x) ? "active" : "inactive");
#endif

	if (x)
	{
		elm_toggle_label_set(win->info->state_label, "Active");
		elm_icon_file_set(win->info->state_icon, "images/dialog_ok.png", NULL);
	}
	else
	{
		elm_toggle_label_set(win->info->state_label, "Inctive");
		elm_icon_file_set(win->info->state_icon, "images/dialog_close.png", NULL);
	}
}

int
zinfo_job_updatevm(void *data)
{
	if (!zrpc_VM_getVM(win->info->vmuuid, zcon, &zinfo_updatevm, NULL))
	{
		elm_label_label_set(win->main_vm->status, "Connection failed");
		evas_object_show(win->main_vm->notify);
	}

	return 1;
}

zrpc_user*
zinfo_user_findbyuid(int id)
{
	Eina_List *l;
	zrpc_user *user;
	int uid;

	if (id >= 0)
		uid = id;
	else
		uid = win->info->uid;

	EINA_LIST_FOREACH(win->list, l, user)
		if (user->uid == uid)
		{
			win->info->newuid = -1;
			return user;
		}
		
	EINA_LIST_FOREACH(win->list, l, user)
		if (user->uid == win->info->newuid)
		{
			win->info->uid = win->info->newuid;
			win->info->newuid = -1;
			return user;
		}

	return NULL;
}

void
zinfo_updateuser(void *data, Evas_Object *obj, void *event_info)
{
	zrpc_user *user;
	zinfo *info = win->info;
	const char *tmp;
	char buf[128];


	if (!(user = zinfo_user_findbyuid(-1)))
	{
		elm_label_label_set(win->main_vm->status, "Invalid UID!");
		evas_object_show(win->main_vm->notify);
		zinfo_destroy_hover(NULL, NULL, NULL);
		return;
	}

	tmp = get_access_name(user->type);
#ifdef DEBUG
printf("DEBUG: setting access type to %s\n", tmp);
#endif
	sprintf(buf, "Access level: %s", tmp);
	elm_label_label_set(info->lb, buf);
	eina_stringshare_del(tmp);

	tmp = get_access_icon(user->type);
#ifdef DEBUG
printf("DEBUG: setting access icon to %s\n", tmp);
#endif
	elm_icon_file_set(info->level_icon, tmp, NULL);
	eina_stringshare_del(tmp);

#ifdef DEBUG
printf("DEBUG: user is %s\n", (user->active) ? "active" : "inactive");
#endif
	if (user->active)
		elm_icon_file_set(win->info->state_icon, "images/dialog_ok.png", NULL);
	else
		elm_icon_file_set(win->info->state_icon, "images/dialog_close.png", NULL);
	elm_toggle_state_set(info->state_label, user->active);
#ifdef DEBUG
printf("DEBUG: access type is %d\n", user->type);
#endif
	elm_slider_value_set(info->level, user->type);

	eina_convert_itoa(user->uid, buf);
	elm_scrolled_entry_entry_set(info->id, buf);

	elm_scrolled_entry_entry_set(info->name, user->name);
	elm_scrolled_entry_entry_set(info->email, user->email);
}

void
zinfo_destroy_hover(void *data, Evas_Object *obj, void *event_info)
{
	zinfo *info = win->info;
	int x;

//	evas_object_hide(info->vbox1);
//	evas_object_del(info->vbox1);
	evas_object_hide(info->hover);
	evas_object_del(info->hover);

	if (win->view == info->vmhover)
		win->view = info->vmview;
	else if ((win->view == info->useradd) || (win->view == info->useredit))
	{
		evas_object_hide(info->lb);
		evas_object_del(info->lb);
		info->uid = -1;
		info->newuid = -1;
		win->view = win->main_user->view;
	}

	x = evas_object_key_grab(win->win, "Up", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Down", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Left", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Right", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Home", 0, 0, 1);
	x = evas_object_key_grab(win->win, "End", 0, 0, 1);
}

void
zinfo_keybind(void *data, Evas_Event_Key_Down *key)
{
	if (win->view == win->info->vmview)
		if (!strcmp(key->keyname, "Escape"))
			change_zinfo_to_zmain(NULL, NULL, NULL);
	if ((win->view == win->info->vmhover) || (win->view == win->info->useradd) || (win->view == win->info->useredit))
		if (!strcmp(key->keyname, "Escape"))
			zinfo_destroy_hover(NULL, NULL, NULL);

}
