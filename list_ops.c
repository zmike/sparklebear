#include "sparklebear.h"

void
list_op_sel(void *data, Evas_Object *obj, void *event_info)
{
#ifdef DEBUG
	Elm_Genlist_Item *gitem;
	const vmitem *vitem;
	const useritem *uitem;
	if (win->view == win->main_vm->view)
	{
		gitem = elm_genlist_selected_item_get(win->main_vm->list);
		vitem = elm_genlist_item_data_get(gitem);
		printf("sel vm [%s:%s], item pointer [%p]\n", vitem->vm->name, vitem->vm->uuid, event_info);
	}
	else if (win->view == win->main_user->view)
	{
		gitem = elm_genlist_selected_item_get(win->main_user->list);
		uitem = elm_genlist_item_data_get(gitem);
		printf("sel user [%d:%s], item pointer [%p]\n", uitem->user->uid, uitem->user->name, event_info);
	}
#endif
}

Eina_Bool
list_op_state_get(const void *data, Evas_Object *obj, const char *part)
{
	return EINA_FALSE;
}
void
list_op_del(const void *data, Evas_Object *obj)
{
}
char *
list_op_vm_label_get(const void *data, Evas_Object *obj, const char *part)
{
	const vmitem *item = data;
	const zrpc_vm *vm;
	const char *type;
	char buf[256];
	

	vm = item->vm;
	if (!strcmp(vm->type, "para"))
		type = "Paravirtualized";
	else
		type = "HVM";
		
	if (!strcmp(part, "elm.text"))
		snprintf(buf, sizeof(buf), "%s (%s guest: %s)", vm->name, type, vm->os);
	else if (!strcmp(part, "elm.text.sub"))
		snprintf(buf, sizeof(buf), "UUID: %s", vm->uuid);

#ifdef EDEBUG
printf("GENLIST: setting label for %s to %s\n", part, buf);
#endif
	
	return strdup(buf);
}

char *
list_op_user_label_get(const void *data, Evas_Object *obj, const char *part)
{
	const useritem *item = data;
	const zrpc_user *user;
	char buf[256];

	user = item->user;

	if (!strcmp(part, "elm.text"))
		snprintf(buf, sizeof(buf), "%s (%s)", user->name, user->email);
	else if (!strcmp(part, "elm.text.sub"))
		snprintf(buf, sizeof(buf), "UID: %d", user->uid);
#ifdef EDEBUG
printf("GENLIST: setting label for %s to %s\n", part, buf);
#endif

	return strdup(buf);
}


Evas_Object *
list_op_vm_icon_get(const void *data, Evas_Object *obj, const char *part)
{
	const vmitem *item = data;
	const zrpc_vm *vm;
	const char *buf;
	Evas_Object *ic;

	vm = item->vm;
	ic = elm_icon_add(obj);
	if (!strcmp(part, "elm.swallow.icon"))
		buf = get_os_icon(vm);
/* 	sets icon at right side of list item */
	else if (!strcmp(part, "elm.swallow.end"))
		buf = get_state_icon(vm->state);

#ifdef EDEBUG
printf("GENLIST: setting icon for %s to %s\n", part, buf);
#endif

	elm_icon_file_set(ic, buf, NULL);
	eina_stringshare_del(buf);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	return ic;
}

Evas_Object *
list_op_user_icon_get(const void *data, Evas_Object *obj, const char *part)
{
	const useritem *item = data;
	const zrpc_user *user;
	const char *buf;
	Evas_Object *ic;

	user = item->user;
	ic = elm_icon_add(obj);
	if (!strcmp(part, "elm.swallow.icon"))
	{
		buf = get_access_icon(user->type);
		elm_icon_file_set(ic, buf, NULL);
		eina_stringshare_del(buf);
	}

/*
	else if (!strcmp(part, "elm.swallow.end"))
		buf = get_lang_icon(user->language);
*/

#ifdef EDEBUG
printf("GENLIST: setting icon for %s to %s\n", part, buf);
#endif


	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	return ic;
}

