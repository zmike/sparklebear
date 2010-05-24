#include "sparklebear.h"

void
panel_logout(void *data, Evas_Object *obj, void *event_info)
{
	if ((win->view == win->main_vm->view) || (win->view == win->main_user->view))
		change_zmain_to_zlogin(win, NULL, NULL);
	else if (win->view == win->info->vmview)
		change_zinfo_to_zlogin(win, NULL, NULL);
}
