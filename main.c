/* 
 * login window for EFL Zentific UI
 * do NOT put other window functions in here!
 * (there shouldn't be any other windows anyway)
 * Mike Blumenkrantz 2010
 */

static const char *host = "10.10.10.6";
static int port = 65534;


#include "main.h"
#include "random.h"
#include "create.h"
#include "zlogin.h"

zwin *win;
zrpc_con *zcon;

EAPI int
elm_main(int argc, char **argv)
{
        zlogin *login;
        zmain *main_vm, *main_user;
        zinfo *info;
	int zwidth = 396, zheight = 390;
        
	eina_init();
	ecore_con_init();
	ecore_x_init(NULL);
	LIBXML_TEST_VERSION;
	signal(SIGCHLD, SIG_IGN);

	win = calloc(sizeof(zwin), 1);
	zcon = calloc(sizeof(zrpc_con), 1);
	login = calloc(sizeof(zlogin), 1);
	main_vm = calloc(sizeof(zmain), 1);
	main_user = calloc(sizeof(zmain), 1);
	info = calloc(sizeof(zinfo), 1);

	win->main_vm = main_vm;
	win->main_user = main_user;
	win->login = login;
	win->info = info;
	win->vmtimer = 30;
	win->usertimer = 30;
	zcon->host = eina_stringshare_add(host);
	zcon->port = port;


	login->view = eina_stringshare_add("login");
	info->vmview = eina_stringshare_add("info_vm");
	info->vmhover = eina_stringshare_add("info_vm_hover");
	info->userview = eina_stringshare_add("info_user");
	main_vm->view = eina_stringshare_add("main_vm");
	main_user->view = eina_stringshare_add("main_user");

	win->win = elm_win_add(NULL, "zEntific", ELM_WIN_BASIC);
	Ecore_X_Window zw, zwr, *roots;
	zw = elm_win_xwindow_get(win->win);
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
				
				ecore_x_window_size_get(zwr, &win->xres, &win->yres);
				evas_object_move(win->win, (win->xres/2)-(zwidth/2), (win->yres/2)-(zheight/2));
				if (ecore_x_screen_is_composited(zwr))
					elm_win_alpha_set(win->win, 1);
				break;
			}
		free(roots);
	}
	elm_win_title_set(win->win, "zEntific Login");
//	elm_win_borderless_set(win->win, 1);
	evas_object_smart_callback_add(win->win, "delete,request", exit_wrapper, NULL);
	if (!evas_object_key_grab(win->win, "Escape", 0, 0, 1))
		printf("Could not grab key 'Escape'\n");
	evas_object_event_callback_add(win->win, EVAS_CALLBACK_KEY_DOWN, key_press, NULL);

	if (!elm_win_alpha_get(win->win))
	{
		win->bg = elm_bg_add(win->win);
		WEIGHT(win->bg, 1, 1);
		ALIGN(win->bg, -1, -1);
		elm_win_resize_object_add(win->win, win->bg);
		evas_object_show(win->bg);
	}	

	win->fl = elm_flip_add(win->win);
	WEIGHT(win->fl, 1, 1);
	ALIGN(win->fl, -1, -1);
	elm_win_resize_object_add(win->win, win->fl);

	create_login();

	elm_flip_content_front_set(win->fl, win->login->box);
	evas_object_show(win->fl);
	evas_object_show(win->win);
	win->view = login->view;

	elm_run();
	xmlCleanupParser();
	elm_shutdown();
	return 0;
}
ELM_MAIN()


