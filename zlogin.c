#include "sparklebear.h"

static int label_update(void *data)
{
	zlogin *login = data;
	if (!login->lt)
		return ECORE_CALLBACK_CANCEL;
	Evas_Object *label = login->stl;
	const char *text = elm_label_label_get(label);
	if (!strcmp(text, "Authenticating."))
		elm_label_label_set(label, "Authenticating..");
	else if (!strcmp(text, "Authenticating.."))
		elm_label_label_set(label, "Authenticating...");
	else
		elm_label_label_set(label, "Authenticating.");
	return 1;
}

void
zlogin_keybind(void *data, Evas_Event_Key_Down *key)
{
	zlogin *login = win->login;
	Evas_Object *f;

	if (!strcmp(key->keyname, "Escape"))
		exit_wrapper(NULL, NULL, NULL);
	else if (!strcmp(key->keyname, "Return") || !strcmp(key->keyname, "KP_Enter"))
		zlogin_try(NULL, NULL, NULL);
	else if (!strcmp(key->keyname, "Tab"))
	{
		if (!login->lp->next) login->lp = login->lp->prev;
		else login->lp = login->lp->next;
		f = login->lp->data;
		elm_object_focus(f);
	}
}

void zlogin_start(void *data)
{
	zlogin *login = win->login;
	
	login->pb = elm_progressbar_add(win->win);
	elm_object_style_set(login->pb, "wheel");
	elm_progressbar_label_set(login->pb, "Style: wheel");
	elm_progressbar_pulse(login->pb, EINA_TRUE);
	evas_object_size_hint_weight_set(login->pb, 1, 0.0);
	elm_box_pack_start(login->box2, login->pb);
	evas_object_show(login->pb);

	elm_label_label_set(login->stl, "Authenticating.");
	elm_notify_timeout_set(login->status, 100);

	login->lt = ecore_timer_add(0.5, label_update, login);

}

void zlogin_stop(void *data)
{
	zlogin *login = data;
	elm_notify_timeout_set(login->status, 3);
	elm_progressbar_pulse(login->pb, 0);
	evas_object_del(login->pb);
	ecore_timer_del(login->lt);
}

void zlogin_try(void *data, Evas_Object *obj, void *event_info)
{
	zlogin *login = win->login;
	Eina_List *lp = login->lp;
	Evas_Object *l = lp->data;
	Evas_Object *p = lp->next->data;
	
	const char *username = elm_scrolled_entry_entry_get(l);
	const char *password = elm_scrolled_entry_entry_get(p);
#ifdef DEBUG
printf("%s:%s\n", username, password);
#endif
	
	elm_object_disabled_set(l, EINA_TRUE);
	elm_object_disabled_set(p, EINA_TRUE);

	zlogin_start(win);

	if (zrpc_User_login(username, password, zcon, change_zlogin_to_zmain, NULL))
		return;

	zlogin_stop(login);
	elm_label_label_set(login->stl, "Remote host could not be reached!");
	evas_object_show(login->status);
	elm_object_disabled_set(l, EINA_FALSE);
	elm_object_disabled_set(p, EINA_FALSE);
	elm_object_focus(l);
	elm_scrolled_entry_cursor_end_set(l);
}
