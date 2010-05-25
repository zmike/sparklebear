#include "sparklebear.h"

void
key_press(void *data, Evas *a, Evas_Object *obj, void *event_info)
{
	Evas_Event_Key_Down *key = event_info;
	
	if ((!key) || (!win->view)) return;
#ifdef DEBUG
	printf("You pressed: %s\n", key->keyname);
#endif
	if (win->view == win->login->view)
		zlogin_keybind(NULL, key);
	else if ((win->view == win->main_vm->view) || (win->view == win->main_user->view))
		zmain_vm_keybind(NULL, key);
	else if ((win->view == win->info->vmview) || (win->view == win->info->vmhover)
		|| (win->view == win->info->useredit) || (win->view == win->info->useradd))
		zinfo_keybind(NULL, key);	
}

vmitem *
new_vmitem(void)
{
	vmitem *new = NULL;
	new = calloc(1, sizeof(vmitem));

	return new;
}

void
free_vmitem(vmitem *item)
{
	if (!item) return;

	eina_stringshare_del(item->uuid);
	eina_stringshare_del(item->state);
	zvm_free(item->vm);

	free(item);
}

useritem *
new_useritem(void)
{
	useritem *new;
	if (!(new = calloc(1, sizeof(useritem))))
		return NULL;

	new->item = NULL;
	new->user = NULL;
	new->uid = -1;

	return new;
}

void
free_useritem(useritem *item)
{
	if (!item) return;

	zuser_free(item->user);

	free(item);
}

void
exit_wrapper(void *data, Evas_Object *obj, void *event_info)
{
#ifdef DEBUG
	vmitem *item;
	
	if (win->view == win->main_vm->view)
		EINA_LIST_FREE(win->elist, item)
			free_vmitem(item);
#endif

	xmlCleanupParser();
	elm_exit();
}

const char *
get_os_icon(const zrpc_vm *vm)
{
	char *buf;

	if (strstr(vm->os, "inux"))
		buf = "images/tux.png";
	else if (strstr(vm->os, "indows"))
		buf = "images/windows.png";
	else buf = "images/unknown.png";

	return eina_stringshare_add(buf);
}

const char *
get_state_icon(const char *state)
{
	char *buf;

	if (!strcmp(state, "") || !strcmp(state, "r"))
		buf = "images/player_play.png";
	else if (!strcmp(state, "b"))
		buf = "images/player_time.png";
	else if (!strcmp(state, "d") || !strcmp(state, "s"))
		buf = "images/player_stop.png";
	else if (!strcmp(state, "p"))
		buf = "images/player_pause.png";
	else
		buf = "images/dialog_close.png";

	return eina_stringshare_add(buf);
}

const char *
get_state_name(const char *state)
{
	char *buf;

	if (!strcmp(state, "") || !strcmp(state, "r"))
		buf = "Running";
	else if (!strcmp(state, "b"))
		buf = "Blocked";
	else if (!strcmp(state, "d") || !strcmp(state, "s"))
		buf = "Dying";
	else if (!strcmp(state, "p"))
		buf = "Paused";
	else
		buf = "Shut Down";


	return eina_stringshare_add(buf);
}

const char *
get_access_icon(int level)
{
	char *buf;

	switch (level)
	{
		case 0:/*SuperUser*/
			buf = "images/configure.png";
			break;
		case 1:/*Maintenance*/
			buf = "images/configure_toolbars.png";
			break;
		case 2:/*Owner*/
			buf = "images/exec.png";
			break;
		case 3:/*Admin*/
			buf = "images/edit_find_user.png";
			break;
		case 4:/*R/O Admin*/
			buf = "images/document_preview_archive.png";
			break;
		default:/*none*/
			buf = "images/edit_clear_locationbar.png";
			break;
	}

	return eina_stringshare_add(buf);
}

const char *
get_access_name(int level)
{
	char *buf;

	switch (level)
	{
		case 0:/*SuperUser*/
			buf = "SuperUser";
			break;
		case 1:/*Maintenance*/
			buf = "Maintenance";
			break;
		case 2:/*Owner*/
			buf = "Owner";
			break;
		case 3:/*Admin*/
			buf = "Admin";
			break;
		case 4:/*R/O Admin*/
			buf = "Read-Only Admin";
			break;
		default:/*none*/
			buf = "NONE";
			break;
	}

	return eina_stringshare_add(buf);
}
