/* 
 * login window for EFL Zentific UI
 * do NOT put other window functions in here!
 * (there shouldn't be any other windows anyway)
 * Mike Blumenkrantz 2010
 */

#define HOST "10.10.10.6"

#include "main.h"

//begin vm_actions.c
#include "vm_actions.c"
//end vm_actions.c

//begin user_actions.c
#include "user_actions.c"
//end user_actions.c

//begin zinfo.c
#include "zinfo.c"
//end zinfo.c

//begin zmain.c
#include "zmain.c"
//end zmain.c

//begin zlogin.c
#include "zlogin.c"
//end zlogin.c



static void
key_press(void *data, Evas *a, Evas_Object *obj, void *event_info)
{
	Evas_Event_Key_Down *key = event_info;
	zwin *zwin = data;
	
	if ((!key) || (!zwin->view)) return;
#ifdef DEBUG
	printf("You pressed: %s\n", key->keyname);
#endif
	if (streq(zwin->view, "login"))
		zlogin_keybind(zwin, key);
	else if (strstr(zwin->view, "main_"))
		zmain_vm_keybind(zwin, key);
	else if (strstr(zwin->view, "info"))
		zinfo_vm_keybind(zwin, key);	
}



EAPI int
elm_main(int argc, char **argv)
{
	mtrace();
	eina_init();
	ecore_con_init();
	ecore_x_init(NULL);
	LIBXML_TEST_VERSION;
	signal(SIGCHLD, SIG_IGN);
	static zlogin zlogin;
	static zmain zmain, zmain_user;
	static zwin zwin;
	static zrpc_con zcon;
	zwin.zcon = &zcon;
	zwin.list = NULL;
	zwin.elist = NULL;
	zwin.timerget = NULL;
	zwin.zmain = &zmain;
	zwin.zmain_user = &zmain_user;
	zwin.zlogin = &zlogin;
	zinfo zinfo;
	zwin.zinfo = &zinfo;
	int zwidth = 396, zheight = 390;
	zwin.vmtimer = 30;
	zwin.usertimer = 30;
	zcon.host = HOST;
	zcon.port = 65534;


	
	static Elm_Genlist_Item_Class itc;
	zmain.itc = &itc;
	itc.item_style     = "double_label";
	itc.func.label_get = gl_vm_label_get;
	itc.func.icon_get  = gl_vm_icon_get;
	itc.func.state_get = gl_state_get;
	itc.func.del       = gl_del;

	static Elm_Genlist_Item_Class itc2;
	zmain_user.itc = &itc2;
	itc2.item_style     = "double_label";
	itc2.func.label_get = gl_user_label_get;
	itc2.func.icon_get  = gl_user_icon_get;
	itc2.func.state_get = gl_state_get;
	itc2.func.del       = gl_del;


	zwin.win = elm_win_add(NULL, "zEntific", ELM_WIN_BASIC);
	Ecore_X_Window zw, zwr, *roots;
	zw = elm_win_xwindow_get(zwin.win);
	zwr = ecore_x_window_root_get(zw);
	int num_wins, nw;
	roots = ecore_x_window_root_list(&num_wins);

	if ((!roots) || (num_wins <= 0))
		printf("Couldn't determine compositing ability of window manager, transparency disabled.\n");
	else
	{
		for (nw = 0; nw < num_wins; nw++)
			if (roots[nw] == zwr)
			{
				
				ecore_x_window_size_get(zwr, &zwin.xres, &zwin.yres);
				evas_object_move(zwin.win, (zwin.xres/2)-(zwidth/2), (zwin.yres/2)-(zheight/2));
				if (ecore_x_screen_is_composited(zwr))
					elm_win_alpha_set(zwin.win, 1);
				break;
			}
		free(roots);
	}
	elm_win_title_set(zwin.win, "zEntific Login");
//	elm_win_borderless_set(zwin.win, 1);
	evas_object_smart_callback_add(zwin.win, "delete,request", exit_wrapper, NULL);
	if (!evas_object_key_grab(zwin.win, "Escape", 0, 0, 1))
		printf("Could not grab key 'Escape'\n");
	evas_object_event_callback_add(zwin.win, EVAS_CALLBACK_KEY_DOWN, key_press, &zwin);

	if (!elm_win_alpha_get(zwin.win))
	{
		zwin.bg = elm_bg_add(zwin.win);
		evas_object_size_hint_weight_set(zwin.bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(zwin.bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_win_resize_object_add(zwin.win, zwin.bg);
		evas_object_show(zwin.bg);
	}	

	zwin.fl = elm_flip_add(zwin.win);
	evas_object_size_hint_weight_set(zwin.fl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(zwin.fl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_win_resize_object_add(zwin.win, zwin.fl);

	create_zlogin(&zwin);

	elm_flip_content_front_set(zwin.fl, zlogin.box);
	evas_object_show(zwin.fl);
	evas_object_show(zwin.win);
	sprintf(zwin.view, "login");

	elm_run();
	xmlCleanupParser();
	elm_shutdown();
	return 0;
}
ELM_MAIN()


