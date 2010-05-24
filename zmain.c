#include "sparklebear.h"

static void zmain_getvms(const char *reply, void *data);
static void zmain_getusers(const char *reply, void *data);

static Elm_Genlist_Item_Class itc;


static void
zmain_getvms(const char *reply, void *data)
{
	Eina_List *l, *n, *elist = win->elist;
	zrpc_vm *vm;
	xmlNode *r;
	vmitem *update, *item;
	int vmfound;

	if (win->view != win->main_vm->view)
		return;
	
	if (!(r = xml_parse_xml(reply)))
                return;
	l = win->list;
	itc.item_style     = "double_label";
	itc.func.label_get = list_op_vm_label_get;
	itc.func.icon_get  = list_op_vm_icon_get;
	itc.func.state_get = list_op_state_get;
	itc.func.del       = list_op_del;
	if (!(win->list = xml_parse_vmsfull(r)))
	{
		elm_label_label_set(win->main_vm->status, "Response parsing failed!");
		evas_object_show(win->main_vm->notify);
		xmlFreeNode(r);
		win->list = l;
		return;
	}

	EINA_LIST_FREE(l, vm)
		zvm_free(vm);
	/* ensure list exists */
	if (elist)
	{

		/*actually search the vm list*/
		EINA_LIST_FOREACH(win->list, n, vm)
		{
#ifdef DEBUG
			printf("DEBUG: Checking genlist for vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
#endif
//			char *find = NULL;
			vmfound = 0;
			/*can't use list_data_find because pointers are different :(*/
			EINA_LIST_FOREACH(win->elist, l, update)
				if (update->uuid == vm->uuid)
				{
					vmfound = 1;
					break;
				}
			if (vmfound)
				EINA_LIST_FOREACH(win->elist, l, update)
				{	/*if uuid exists, update vm*/
					if (update->uuid == vm->uuid)
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
				item = new_vmitem();
				item->uuid = eina_stringshare_ref(vm->uuid);
				item->state = eina_stringshare_ref(vm->state);
				item->vm = vm;
				item->item = elm_genlist_item_append(win->main_vm->list, &itc,
                                      (void *)item /* item data */,
                                      NULL/* parent */,
                                      ELM_GENLIST_ITEM_NONE,
                                      list_op_sel/* func */,
                                      (void *)win/* func data */);
				/*add to list of vmitems*/
				win->elist = eina_list_append(win->elist, item);
			}

		}
	}
	else 
		EINA_LIST_FOREACH(win->list, l, vm)
			{
#ifdef DEBUG
				printf("GENLIST: Adding new vm:\n\tuuid {%s}\n\tname {%s}\n", vm->uuid, vm->name);
#endif
				item = new_vmitem();
				item->uuid = eina_stringshare_ref(vm->uuid);
				item->state = eina_stringshare_ref(vm->state);
				item->vm = vm;
				item->item = elm_genlist_item_append(win->main_vm->list, &itc,
					(void *)item /* item data */,
					NULL/* parent */,
					ELM_GENLIST_ITEM_NONE,
					list_op_sel/* func */,
					(void *)win/* func data */);
				/*add to list of vmitems*/
				win->elist = eina_list_append(win->elist, item);
			}

	EINA_LIST_FOREACH_SAFE(win->elist, l, elist, update)
	{
		vmfound = 0;
		EINA_LIST_FOREACH(win->list, n, vm)
			if (update->uuid == vm->uuid)
			{
				vmfound = 1;
				break;
			}

		if (!vmfound)
		{
			elm_genlist_item_del(update->item);
			win->elist = eina_list_remove_list(win->elist, l);
			free_vmitem(update);
		}
	}

	elm_label_label_set(win->main_vm->status, "VM info successfully refreshed!");
	evas_object_show(win->main_vm->notify);
}

static void
zmain_getusers(const char *reply, void *data)
{
	zrpc_meta_struct *meta;
	Eina_List *l, *n, *elist, *users;
	useritem *update, *item;
	zrpc_user *user;
	int ufound;

	if (!(meta = data)) return;
	if (!(users = meta->extra)) return;

	if (win->view != win->main_user->view) return;
	elist = win->elist;
	win->list = users;

	itc.item_style     = "double_label";
	itc.func.label_get = list_op_user_label_get;
	itc.func.icon_get  = list_op_user_icon_get;
	itc.func.state_get = list_op_state_get;
	itc.func.del       = list_op_del;
	
	/* ensure list exists */
	if (elist)
	{

		/*actually search the user list*/
		EINA_LIST_FOREACH(win->list, n, user)
		{
#ifdef DEBUG
			printf("DEBUG: Checking genlist for user:\n\tuid {%d}\n\tname {%s}\n", user->uid, user->name);
#endif
//			char *find = NULL;
			ufound = 0;
			/*can't use list_data_find because it's just an int :(*/
			EINA_LIST_FOREACH(win->elist, l, update)
				if (update->uid == user->uid)
				{
					ufound = 1;
					break;
				}
			if (ufound)
				EINA_LIST_FOREACH(win->elist, l, update)
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
				item = new_useritem();
				item->uid = user->uid;
				item->user = user;
#ifdef DEBUG
				printf("GENLIST: Not found!\n");
				printf("GENLIST: Adding new user:\n\tuid {%d}\n\tname {%s}\n", item->uid, item->user->name);
#endif
				item->item = elm_genlist_item_append(win->main_user->list, &itc,
                                      (void *)item /* item data */,
                                      NULL/* parent */,
                                      ELM_GENLIST_ITEM_NONE,
                                      list_op_sel/* func */,
                                      (void *)win/* func data */);
				/*add to list of useritems*/
				win->elist = eina_list_append(win->elist, item);
			}

		}
	}
	else 
		EINA_LIST_FOREACH(win->list, l, user)
			{
				item = new_useritem();
				item->uid = user->uid;
				item->user = user;
#ifdef DEBUG
				printf("GENLIST: Adding new user:\n\tuid {%d}\n\tname {%s}\n", item->uid, item->user->name);
#endif
				item->item = elm_genlist_item_append(win->main_user->list, &itc,
					(void *)item /* item data */,
					NULL/* parent */,
					ELM_GENLIST_ITEM_NONE,
					list_op_sel/* func */,
					(void *)win/* func data */);
				/*add to list of useritems*/
				win->elist = eina_list_append(win->elist, item);
			}

	EINA_LIST_FOREACH_SAFE(win->elist, l, elist, update)
	{
		ufound = 0;
		EINA_LIST_FOREACH(win->list, n, user)
			if (update->uid == user->uid)
			{
				ufound = 1;
				break;
			}

		if (!ufound)
		{
			elm_genlist_item_del(update->item);
			win->elist = eina_list_remove_list(win->elist, l);
			free_useritem(update);
		}
	}

	elm_label_label_set(win->main_vm->status, "User info successfully refreshed!");
	evas_object_show(win->main_vm->notify);
}


int
zmain_job_getusers(void *data)
{
	if (!meta_getUsersFull(zcon, &zmain_getusers, NULL))
		elm_label_label_set(win->main_vm->status, "Connection failed, retrying");
	else
		elm_label_label_set(win->main_vm->status, "Adding job to refresh user info...");

	evas_object_show(win->main_vm->notify);
	
	return 1;
}

void
zmain_vm_keybind(void *data, Evas_Event_Key_Down *key)
{
	Elm_Genlist_Item *gi, *gi2;
	Eina_List *view_list, *l;
	zmain *view;
	Elm_Toolbar_Item *tb;

	if (win->view == win->main_vm->view)
		view = win->main_vm;
	else if (win->view == win->main_user->view)
		view = win->main_user;
	else return;

	if (!strcmp(key->keyname, "Escape"))
	{
		change_zmain_to_zlogin(win, NULL, NULL);
		return;
	}
	else if (!strcmp(key->keyname, "Left"))
	{
		EINA_LIST_FOREACH(win->main_vm->view_list, l, tb)
			if (elm_toolbar_item_selected_get(tb))
				break;
		if (!l->prev) view_list = eina_list_last(win->main_vm->view_list);
		else view_list = l->prev;
		tb = view_list->data;
		elm_toolbar_item_select(tb);
		return;
	}
	else if (!strcmp(key->keyname, "Right"))
	{
		EINA_LIST_FOREACH(win->main_vm->view_list, l, tb)
			if (elm_toolbar_item_selected_get(tb))
				break;
		if (!l->next) view_list = win->main_vm->view_list;
		else view_list = l->next;
		tb = view_list->data;
		elm_toolbar_item_select(tb);
		return;
	}
	else if (!strcmp(key->keyname, "Down"))
	{
		if (!(gi = elm_genlist_selected_item_get(view->list)))
		{
			if (!(gi = elm_genlist_first_item_get(view->list)))
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
	else if (!strcmp(key->keyname, "Up"))
	{
		if (!(gi = elm_genlist_selected_item_get(view->list)))
		{
			if (!(gi = elm_genlist_first_item_get(view->list)))
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
	else if (!strcmp(key->keyname, "Home"))
	{
		if (!(gi = elm_genlist_first_item_get(view->list)))
			return;
		elm_genlist_item_selected_set(gi, 1);
		elm_genlist_item_bring_in(gi);
	}
	else if (!strcmp(key->keyname, "End"))
	{
		if (!(gi = elm_genlist_last_item_get(view->list)))
			return;
		elm_genlist_item_selected_set(gi, 1);
		elm_genlist_item_bring_in(gi);
	}
	else if (!strcmp(key->keyname, "Return") || !strcmp(key->keyname, "KP_Enter"))
	{
		if (win->view == win->main_vm->view)
			vm_info_cb(NULL, NULL, NULL);
		else if (win->view == win->main_user->view)
			user_info_cb(NULL, NULL, NULL);
	}
}

int
zmain_job_getvms(void *data)
{
	if (!zrpc_VM_getAllFull(zcon, &zmain_getvms, NULL))
		elm_label_label_set(win->main_vm->status, "Connection failed, retrying");
	else
		elm_label_label_set(win->main_vm->status, "Adding job to refresh vm info...");

	evas_object_show(win->main_vm->notify);
	
	return 1;
}
