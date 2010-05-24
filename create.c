#include "sparklebear.h"

static char *zlogo = "images/logo.png";

void
create_info_vm(void)
{
	win->info->frame = elm_frame_add(win->win);
	WEIGHT(win->info->frame, 1, 1);
	ALIGN(win->info->frame, -1, -1);
	evas_object_show(win->info->frame);

	win->info->hbox = elm_box_add(win->win);
//	elm_box_homogenous_set(win->info->hbox, 1);
	elm_box_horizontal_set(win->info->hbox, 1);
	WEIGHT(win->info->hbox, 1, 1);
	ALIGN(win->info->hbox, -1, -1);
	elm_frame_content_set(win->info->frame, win->info->hbox);
	evas_object_show(win->info->hbox);
	
	win->info->vbox1 = elm_box_add(win->win);
	WEIGHT(win->info->vbox1, 0.0, 0.0);
	ALIGN(win->info->vbox1, -1, -1);
	elm_box_pack_end(win->info->hbox, win->info->vbox1);
	evas_object_show(win->info->vbox1);

	win->info->bi = elm_icon_add(win->win);
	elm_icon_file_set(win->info->bi, "images/player_rew.png", NULL);
	evas_object_show(win->info->bi);

	win->info->back = elm_button_add(win->win);
	elm_button_icon_set(win->info->back, win->info->bi);
	elm_button_label_set(win->info->back, "Back");
	WEIGHT(win->info->back, 0.0, 0.0);
	ALIGN(win->info->back, 0.0, 0.0);
	elm_box_pack_end(win->info->vbox1, win->info->back);
	evas_object_smart_callback_add(win->info->back, "clicked", change_zinfo_to_zmain, win);
	evas_object_show(win->info->back);

	win->info->os_icon = elm_icon_add(win->win);
	elm_icon_scale_set(win->info->os_icon, 0, 0);
	elm_icon_smooth_set(win->info->os_icon, 1);
	WEIGHT(win->info->os_icon, 0.0, 0.0);
	ALIGN(win->info->os_icon, 0.0, 0.0);
	elm_box_pack_end(win->info->vbox1, win->info->os_icon);
	evas_object_show(win->info->os_icon);

	win->info->os = elm_label_add(win->win);
	WEIGHT(win->info->os, 1, 0.0);
	ALIGN(win->info->os, 0.5, 0.5);
	elm_box_pack_end(win->info->vbox1, win->info->os);
	evas_object_show(win->info->os);

	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox1, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->uuid = elm_label_add(win->win);
	WEIGHT(win->info->uuid, 1, 0.0);
	ALIGN(win->info->uuid, 0.5, 0.5);
	elm_box_pack_end(win->info->vbox1, win->info->uuid);
	evas_object_show(win->info->uuid);
	
	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox1, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->puuid = elm_label_add(win->win);
	WEIGHT(win->info->puuid, 1, 0.0);
	ALIGN(win->info->puuid, 0.5, 0.5);
	elm_box_pack_end(win->info->vbox1, win->info->puuid);
	evas_object_show(win->info->puuid);

	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox1, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->disks = elm_hoversel_add(win->win);
	elm_hoversel_label_set(win->info->disks, "VBDs");
	elm_hoversel_hover_parent_set(win->info->disks, win->win);
	WEIGHT(win->info->disks, 0.0, 0.0);
	ALIGN(win->info->disks, 0.5, 0.5);
	elm_box_pack_end(win->info->vbox1, win->info->disks);
	evas_object_show(win->info->disks);

	win->info->sp = elm_separator_add(win->win);
	elm_box_pack_end(win->info->hbox, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->vbox2 = elm_box_add(win->win);
	WEIGHT(win->info->vbox2, 1.0, 1.0);
	ALIGN(win->info->vbox2, -1, -1);
	elm_box_pack_end(win->info->hbox, win->info->vbox2);
	evas_object_show(win->info->vbox2);

	win->info->uptime = elm_label_add(win->win);
	WEIGHT(win->info->uptime, 1, 0.0);
	ALIGN(win->info->uptime, 0.5, -1);
	elm_box_pack_end(win->info->vbox2, win->info->uptime);
	evas_object_show(win->info->uptime);

	win->info->sp = elm_separator_add(win->win);
	elm_box_pack_end(win->info->vbox2, win->info->sp);
	evas_object_show(win->info->sp);
	
	win->info->state_icon = elm_icon_add(win->win);
	elm_icon_scale_set(win->info->state_icon, 0, 0);
	elm_icon_smooth_set(win->info->state_icon, 1);
	WEIGHT(win->info->state_icon, 1, 1);
	ALIGN(win->info->state_icon, 0.0, -1);
	elm_box_pack_end(win->info->vbox2, win->info->state_icon);
	evas_object_smart_callback_add(win->info->state_icon, "clicked", zinfo_vm_state_change, win);
	evas_object_show(win->info->state_icon);

	win->info->state_label = elm_label_add(win->win);
	WEIGHT(win->info->state_label, 1, 1);
	ALIGN(win->info->state_label, 0.5, 0.0);
	elm_box_pack_end(win->info->vbox2, win->info->state_label);
	evas_object_show(win->info->state_label);

	/* cpus goes here */

	win->info->pct = elm_progressbar_add(win->win);
	elm_progressbar_horizontal_set(win->info->pct, 1);
	elm_progressbar_value_set(win->info->pct, 0);
	WEIGHT(win->info->pct, 1, 0.0);
	ALIGN(win->info->pct, 0.5, 1.0);
	elm_box_pack_end(win->info->vbox2, win->info->pct);
	evas_object_show(win->info->pct);

	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox2, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->vifs = elm_hoversel_add(win->win);
	elm_hoversel_label_set(win->info->vifs, "VIFs");
	elm_hoversel_hover_parent_set(win->info->vifs, win->win);
	WEIGHT(win->info->vifs, 0.0, 0.0);
	ALIGN(win->info->vifs, 0.5, 1.0);
	elm_box_pack_end(win->info->vbox2, win->info->vifs);
	evas_object_show(win->info->vifs);

	win->info->sp = elm_separator_add(win->win);
	elm_box_pack_end(win->info->hbox, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->vbox3 = elm_box_add(win->win);
	WEIGHT(win->info->vbox3, 1, 1);
	ALIGN(win->info->vbox3, -1, -1);
	elm_box_pack_end(win->info->hbox, win->info->vbox3);
	evas_object_show(win->info->vbox3);

	win->info->kernel = elm_label_add(win->win);
	WEIGHT(win->info->kernel, 1, 0.0);
	ALIGN(win->info->kernel, -1, 0.5);
	elm_box_pack_end(win->info->vbox3, win->info->kernel);
	evas_object_show(win->info->kernel);

	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox3, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->ramdisk = elm_label_add(win->win);
	WEIGHT(win->info->ramdisk, 1, 0.0);
	ALIGN(win->info->ramdisk, -1, 0.5);
	elm_box_pack_end(win->info->vbox3, win->info->ramdisk);
	evas_object_show(win->info->ramdisk);
	
	win->info->sp = elm_separator_add(win->win);
	elm_separator_horizontal_set(win->info->sp, 1);
	elm_box_pack_end(win->info->vbox3, win->info->sp);
	evas_object_show(win->info->sp);

	win->info->cmdline = elm_label_add(win->win);
	WEIGHT(win->info->cmdline, 1, 0.0);
	ALIGN(win->info->cmdline, -1, 0.5);
	elm_box_pack_end(win->info->vbox3, win->info->cmdline);
	evas_object_show(win->info->cmdline);

	win->info->notesframe = elm_frame_add(win->win);
	elm_frame_label_set(win->info->notesframe, "Notes");
	WEIGHT(win->info->notesframe, 1, 1);
	ALIGN(win->info->notesframe, 0.5, 1.0);
	elm_box_pack_end(win->info->vbox3, win->info->notesframe);
	evas_object_show(win->info->notesframe);

	win->info->vbox4 = elm_box_add(win->win);
	WEIGHT(win->info->vbox4, 1, 1);
	ALIGN(win->info->vbox4, -1, -1);
	elm_frame_content_set(win->info->notesframe, win->info->vbox4);
	evas_object_show(win->info->vbox4);

	win->info->notes = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(win->info->notes, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_line_wrap_set(win->info->notes, 1);
	WEIGHT(win->info->notes, 1, 1);
	ALIGN(win->info->notes, 0.5, 0.5);
	elm_box_pack_end(win->info->vbox4, win->info->notes);
	evas_object_show(win->info->notes);

	win->info->notesend = elm_button_add(win->win);
	elm_button_label_set(win->info->notesend, "Save");
	evas_object_smart_callback_add(win->info->notesend, "clicked", NULL, win);
	WEIGHT(win->info->notesend, 0.0, 0.0);
	ALIGN(win->info->notesend, 1.0, 1.0);
	elm_box_pack_end(win->info->vbox4, win->info->notesend);
	evas_object_show(win->info->notesend);
}

void
create_info_user(void)
{
	Eina_List *gl_l;
	int count;

	gl_l = elm_genlist_realized_items_get(win->main_user->list);
	count = eina_list_count(gl_l);

	win->info->hover = elm_hover_add(win->win);
	elm_object_style_set(win->info->hover, "popout");
	elm_hover_parent_set(win->info->hover, win->win);
	elm_hover_target_set(win->info->hover, win->main_user->list);
	evas_object_smart_callback_add(win->info->hover, "clicked", zinfo_destroy_hover, win);


//hbox
	win->info->hbox = elm_box_add(win->win);
	elm_object_scale_set(win->info->hbox, 1.5);
	elm_box_horizontal_set(win->info->hbox, 1);

	win->info->lb = elm_label_add(win->win);
	elm_box_pack_end(win->info->hbox, win->info->lb);
	evas_object_show(win->info->lb);
	elm_hover_content_set(win->info->hover, "top", win->info->hbox);
	evas_object_show(win->info->hbox);
//hbox


//vbox2
	win->info->vbox2 = elm_box_add(win->win);
	elm_box_horizontal_set(win->info->vbox2, 1);
	elm_box_homogenous_set(win->info->vbox2, 1);

	win->info->state_icon = elm_icon_add(win->win);
	elm_object_scale_set(win->info->state_icon, 0.5);
	elm_icon_scale_set(win->info->state_icon, 0, 1);
	elm_icon_smooth_set(win->info->state_icon, 1);
	evas_object_show(win->info->state_icon);
	win->info->state_label = elm_toggle_add(win->win);
	evas_object_size_hint_expand_set(win->info->state_label, 0, 0);
	evas_object_size_hint_fill_set(win->info->state_label, 0, 0.5);
	elm_toggle_icon_set(win->info->state_label, win->info->state_icon);
	elm_toggle_label_set(win->info->state_label, "Active");
	elm_toggle_states_labels_set(win->info->state_label, "Yes", "No");
	elm_object_scale_set(win->info->state_label, 1.7);
	evas_object_smart_callback_add(win->info->state_label, "changed", zinfo_job_updateuser_state, win);
	elm_box_pack_end(win->info->vbox2, win->info->state_label);
	evas_object_show(win->info->state_label);


//vbox1
	win->info->vbox1 = elm_box_add(win->win);

	win->info->level_icon = elm_icon_add(win->win);
	elm_icon_scale_set(win->info->level_icon, 0, 0);
	elm_icon_smooth_set(win->info->level_icon, 1);
	elm_box_pack_end(win->info->vbox1, win->info->level_icon);
	evas_object_show(win->info->level_icon);


	win->info->frame = elm_frame_add(win->win);
	evas_object_size_hint_expand_set(win->info->frame, 1, 0);
	evas_object_size_hint_fill_set(win->info->frame, -1, 0);
	elm_frame_label_set(win->info->frame, "UID");
	elm_object_scale_set(win->info->frame, 1.5);
	win->info->id = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(win->info->id, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(win->info->id, 1);
	evas_object_show(win->info->id);

	elm_frame_content_set(win->info->frame, win->info->id);
	elm_box_pack_end(win->info->vbox1, win->info->frame);
	evas_object_show(win->info->frame);

	win->info->frame = elm_frame_add(win->win);
	elm_object_scale_set(win->info->frame, 1.5);
	evas_object_size_hint_expand_set(win->info->frame, 1, 0);
	evas_object_size_hint_fill_set(win->info->frame, -1, 0);
	elm_frame_label_set(win->info->frame, "Name");

	win->info->name = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(win->info->name, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(win->info->name, 1);
	evas_object_show(win->info->name);

	elm_frame_content_set(win->info->frame, win->info->name);
	evas_object_show(win->info->frame);
	elm_box_pack_end(win->info->vbox1, win->info->frame);


//hbox
	win->info->hbox = elm_box_add(win->win);
	elm_box_horizontal_set(win->info->hbox, 1);

	win->info->frame = elm_frame_add(win->win);
	elm_object_scale_set(win->info->frame, 1.5);
	evas_object_size_hint_expand_set(win->info->frame, 1, 0);
	evas_object_size_hint_fill_set(win->info->frame, -1, 0);
	elm_frame_label_set(win->info->frame, "Password");

	win->info->pass = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_password_set(win->info->pass, 1);
	elm_scrolled_entry_entry_set(win->info->pass, "password");
	elm_scrolled_entry_select_all(win->info->pass);
	elm_scrolled_entry_scrollbar_policy_set(win->info->pass, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(win->info->pass, 1);
	evas_object_show(win->info->pass);

	elm_frame_content_set(win->info->frame, win->info->pass);
	elm_box_pack_end(win->info->hbox, win->info->frame);
	evas_object_show(win->info->frame);	

	elm_box_pack_end(win->info->vbox1, win->info->hbox);
	evas_object_show(win->info->hbox);
//hbox

	win->info->frame = elm_frame_add(win->win);
	evas_object_size_hint_expand_set(win->info->frame, 1, 0);
	evas_object_size_hint_fill_set(win->info->frame, -1, -1);
	elm_object_scale_set(win->info->frame, 1.5);
	elm_frame_label_set(win->info->frame, "Email");
	win->info->email = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(win->info->email, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(win->info->email, 1);
	evas_object_show(win->info->email);
	elm_frame_content_set(win->info->frame, win->info->email);
	elm_box_pack_end(win->info->vbox1, win->info->frame);
	evas_object_show(win->info->email);
	evas_object_show(win->info->frame);

	elm_box_pack_end(win->info->vbox2, win->info->vbox1);
	evas_object_show(win->info->vbox1);
//vbox1

	win->info->level = elm_slider_add(win->win);
	elm_slider_horizontal_set(win->info->level, 0);
	elm_slider_label_set(win->info->level, "Access Level");
	elm_slider_min_max_set(win->info->level, USER_LEVEL_MIN, USER_LEVEL_MAX);
	elm_slider_indicator_format_set(win->info->level, "%1.0f");
	elm_object_scale_set(win->info->level, 3);
	evas_object_smart_callback_add(win->info->level, "changed", zinfo_job_updateuser_level, win);
	elm_box_pack_end(win->info->vbox2, win->info->level);
	evas_object_show(win->info->level);

	elm_hover_content_set(win->info->hover, "middle", win->info->vbox2);
	evas_object_show(win->info->vbox2);
//vbox2


	win->info->hbox = elm_box_add(win->win);
	elm_box_homogenous_set(win->info->hbox, 1);
	elm_box_horizontal_set(win->info->hbox, 1);
	elm_hover_content_set(win->info->hover, "bottom", win->info->hbox);

	win->info->ic = elm_icon_add(win->win);
	elm_icon_file_set(win->info->ic, "images/reload.png", NULL);
	evas_object_show(win->info->ic);

	win->info->hb = elm_button_add(win->win);
	elm_button_icon_set(win->info->hb, win->info->ic);
	elm_button_label_set(win->info->hb, "Refresh");
	elm_object_style_set(win->info->hb, "anchor");
	evas_object_smart_callback_add(win->info->hb, "clicked", zinfo_job_updateuser, win);
	elm_box_pack_end(win->info->hbox, win->info->hb);
	evas_object_show(win->info->hb);

	win->info->ic = elm_icon_add(win->win);
	elm_icon_file_set(win->info->ic, "images/exit.png", NULL);
	evas_object_show(win->info->ic);

	win->info->hb = elm_button_add(win->win);
	elm_button_icon_set(win->info->hb, win->info->ic);
	elm_button_label_set(win->info->hb, "Back");
	elm_object_style_set(win->info->hb, "anchor");
	evas_object_smart_callback_add(win->info->hb, "clicked", zinfo_destroy_hover, win);
	elm_box_pack_end(win->info->hbox, win->info->hb);
	evas_object_show(win->info->hb);

	win->info->ic = elm_icon_add(win->win);
	elm_icon_file_set(win->info->ic, "images/button_ok.png", NULL);
	evas_object_show(win->info->ic);

	win->info->hb = elm_button_add(win->win);
	elm_button_icon_set(win->info->hb, win->info->ic);
	elm_button_label_set(win->info->hb, "Apply");
	elm_object_style_set(win->info->hb, "anchor");
	evas_object_smart_callback_add(win->info->hb, "clicked", user_edit_cb, win);
	elm_box_pack_end(win->info->hbox, win->info->hb);
	evas_object_show(win->info->hb);

	evas_object_show(win->info->hbox);
	evas_object_show(win->info->hover);
}

void
create_login(void)
{
	int x;
	zlogin *login = win->login;
	login->lp = NULL;

	Evas_Object *l, *p;

	login->box = elm_box_add(win->win);
	elm_object_focus_allow_set(login->box, 0);
	WEIGHT(login->box, 1, 1);
	ALIGN(login->box, -1, -1);
	evas_object_show(login->box);

	login->icon = elm_icon_add(win->win);
	elm_icon_file_set(login->icon, zlogo, NULL);
	elm_icon_scale_set(login->icon, 0, 0);
	elm_icon_smooth_set(login->icon, 1);
	elm_box_pack_end(login->box, login->icon);
	elm_object_focus_allow_set(login->icon, 0);
	evas_object_show(login->icon);
	
	login->fr = elm_frame_add(win->win);
	WEIGHT(login->fr, 1, 0.0);
	ALIGN(login->fr, -1, 0.0);
	elm_frame_label_set(login->fr, "Username");
	
	l = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(l, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(l, 1);
	elm_scrolled_entry_entry_set(l, "admin");
	elm_scrolled_entry_select_all(l);
	elm_object_focus(l);
	elm_scrolled_entry_cursor_end_set(l);
	evas_object_show(l);
		
	elm_frame_content_set(login->fr, l);
	elm_box_pack_end(login->box, login->fr);
	evas_object_show(login->fr);


	login->fr2 = elm_frame_add(win->win);
	elm_frame_label_set(login->fr2, "Password");
	WEIGHT(login->fr2, 1, 0.0);
	ALIGN(login->fr2, -1, 0.0);

	p = elm_scrolled_entry_add(win->win);
	elm_scrolled_entry_scrollbar_policy_set(p, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	elm_scrolled_entry_single_line_set(p, 1);
	elm_scrolled_entry_password_set(p, 1);
	elm_scrolled_entry_entry_set(p, "sparklebear");
	evas_object_show(p);

	elm_frame_content_set(login->fr2, p);
	elm_box_pack_end(login->box, login->fr2);
	evas_object_show(login->fr2);
	
	login->hbox = elm_box_add(win->win);
	elm_box_horizontal_set(login->hbox, 1);
	elm_box_pack_end(login->box, login->hbox);
	elm_object_focus_allow_set(login->hbox, 0);
	evas_object_show(login->hbox);
	
	
	login->loginbutton = elm_button_add(win->win);
	elm_button_label_set(login->loginbutton, "Login");
	elm_object_focus_allow_set(login->loginbutton, 0);
	elm_box_pack_end(login->hbox, login->loginbutton);
	evas_object_smart_callback_add(login->loginbutton, "clicked", zlogin_try, win);
	evas_object_show(login->loginbutton);
	
	
	login->cancelbutton = elm_button_add(win->win);
	elm_button_label_set(login->cancelbutton, "Cancel");
	elm_object_focus_allow_set(login->cancelbutton, 0);
	elm_box_pack_end(login->hbox, login->cancelbutton);
	evas_object_smart_callback_add(login->cancelbutton, "clicked", exit_wrapper, NULL);
	evas_object_show(login->cancelbutton);

	login->box2 = elm_box_add(win->win);
	elm_object_focus_allow_set(login->box2, 0);
	elm_box_horizontal_set(login->box2, 1);
	elm_box_pack_after(login->box, login->box2, login->icon);
	login->status = elm_notify_add(win->win);
	elm_object_focus_allow_set(login->status, 0);
	login->stl = elm_label_add(win->win);
	elm_object_focus_allow_set(login->stl, 0);
	elm_notify_content_set(login->status, login->stl);
	elm_notify_orient_set(login->status, ELM_NOTIFY_ORIENT_CENTER);
	elm_notify_timeout_set(login->status, 3);
	elm_box_pack_end(login->box2, login->status);
	evas_object_show(login->stl);

	login->lp = eina_list_append(login->lp, l);
	login->lp = eina_list_append(login->lp, p);

	x = evas_object_key_grab(win->win, "Return", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Tab", 0, 0, 1);
	x = evas_object_key_grab(win->win, "KP_Enter", 0, 0, 1);
}

void
create_main(void)
{
	Elm_Toolbar_Item *tb;
	zmain *main_vm = win->main_vm;
	int x;

	main_vm->box = elm_box_add(win->win);
	elm_object_focus_allow_set(main_vm->box, 0);
	WEIGHT(main_vm->box, 1, 1);
	ALIGN(main_vm->box, -1, -1);
	evas_object_show(main_vm->box);

	main_vm->fl = elm_flip_add(win->win);
	WEIGHT(main_vm->fl, 1, 1);
	ALIGN(main_vm->fl, -1, -1);
	elm_box_pack_end(main_vm->box, main_vm->fl);

	create_main_vm();

	elm_flip_content_front_set(win->main_vm->fl, win->main_vm->box2);
	evas_object_show(win->main_vm->fl);

	main_vm->viewbar = elm_toolbar_add(win->win);
	elm_toolbar_homogenous_set(main_vm->viewbar, 0);
	elm_toolbar_scrollable_set(main_vm->viewbar, 0);
	WEIGHT(main_vm->viewbar, 1, 0.0);
	ALIGN(main_vm->viewbar, -1, -1);
	evas_object_show(main_vm->viewbar);

	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/exit.png", NULL);
	tb = elm_toolbar_item_add(main_vm->viewbar, main_vm->icon, "Logout", panel_logout, win);

	tb = elm_toolbar_item_add(main_vm->bar, NULL, NULL, NULL, NULL);
	elm_toolbar_item_separator_set(tb, 1);
	
	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/computer.png", NULL);
	tb = elm_toolbar_item_add(main_vm->viewbar, main_vm->icon, "VM view", view_main_vm, win);
	elm_toolbar_item_select(tb);

	main_vm->view_list = eina_list_append(main_vm->view_list, tb);

	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/user.png", NULL);
	tb = elm_toolbar_item_add(main_vm->viewbar, main_vm->icon, "User view", view_main_user, win);

	main_vm->view_list = eina_list_append(main_vm->view_list, tb);

	main_vm->panel = elm_panel_add(win->win);
	elm_panel_orient_set(main_vm->panel, ELM_PANEL_ORIENT_LEFT);
	elm_panel_content_set(main_vm->panel, main_vm->viewbar);
	WEIGHT(main_vm->panel, 1, 0.0);
	ALIGN(main_vm->panel, -1, -1);
	elm_box_pack_end(main_vm->box, main_vm->panel);
	evas_object_show(main_vm->panel);

	main_vm->notify = elm_notify_add(win->win);
	elm_object_focus_allow_set(main_vm->notify, 0);
	main_vm->status = elm_label_add(win->win);
	elm_object_focus_allow_set(main_vm->status, 0);
	elm_notify_content_set(main_vm->notify, main_vm->status);
	elm_notify_orient_set(main_vm->notify, ELM_NOTIFY_ORIENT_BOTTOM_RIGHT);
	elm_notify_timeout_set(main_vm->notify, 3);
	elm_box_pack_end(main_vm->box, main_vm->notify);
	evas_object_show(main_vm->status);

	
	x = evas_object_key_grab(win->win, "Return", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Up", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Down", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Left", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Right", 0, 0, 1);
	x = evas_object_key_grab(win->win, "KP_Enter", 0, 0, 1);
	x = evas_object_key_grab(win->win, "Home", 0, 0, 1);
	x = evas_object_key_grab(win->win, "End", 0, 0, 1);
}

void
create_main_vm(void)
{
	Elm_Toolbar_Item *tb;
	zmain *main_vm = win->main_vm;
	Eina_List *l = NULL;

	main_vm->box2 = elm_box_add(win->win);
	elm_object_focus_allow_set(main_vm->box2, 0);
	WEIGHT(main_vm->box2, 1, 1);
	ALIGN(main_vm->box2, -1, -1);
	evas_object_show(main_vm->box2);

	main_vm->bar = elm_toolbar_add(win->win);
	elm_toolbar_homogenous_set(main_vm->bar, 0);
	elm_toolbar_scrollable_set(main_vm->bar, 0);
	WEIGHT(main_vm->bar, 1, 0.0);
	ALIGN(main_vm->bar, -1, 0.0);
	elm_box_pack_end(main_vm->box2, main_vm->bar);
	evas_object_show(main_vm->bar);

	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/screwdriver.png", NULL);
	tb = elm_toolbar_item_add(main_vm->bar, main_vm->icon, "Info", vm_info_cb, win);
	l = eina_list_append(l, tb);
	
	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/pause.png", NULL);
	tb = elm_toolbar_item_add(main_vm->bar, main_vm->icon, "Pause", vm_pause_cb, win);
	l = eina_list_append(l, tb);
	
	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/shutdown.png", NULL);
	tb = elm_toolbar_item_add(main_vm->bar, main_vm->icon, "Shutdown", vm_shutdown_cb, win);
	l = eina_list_append(l, tb);
	
	main_vm->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_vm->icon, "images/reboot.png", NULL);
	tb = elm_toolbar_item_add(main_vm->bar, main_vm->icon, "Reboot", vm_reboot_cb, win);
	l = eina_list_append(l, tb);

	main_vm->tb_list = l;
	main_vm->list = elm_genlist_add(win->win);
	evas_object_smart_callback_add(main_vm->list, "clicked", vm_info_cb, win);
	WEIGHT(main_vm->list, 1, 1);
	ALIGN(main_vm->list, -1, -1);
	elm_box_pack_end(main_vm->box2, main_vm->list);
	evas_object_show(main_vm->list);

}

void
create_main_user(void)
{
	Elm_Toolbar_Item *tb;
	zmain *main_user = win->main_user;
	Eina_List *l = NULL;

	main_user->box2 = elm_box_add(win->win);
	elm_object_focus_allow_set(main_user->box2, 0);
	WEIGHT(main_user->box2, 1, 1);
	ALIGN(main_user->box2, -1, -1);
	evas_object_show(main_user->box2);

	main_user->bar = elm_toolbar_add(win->win);
	elm_toolbar_homogenous_set(main_user->bar, 0);
	elm_toolbar_scrollable_set(main_user->bar, 0);
	WEIGHT(main_user->bar, 1, 0.0);
	ALIGN(main_user->bar, -1, 0.0);
	elm_box_pack_end(main_user->box2, main_user->bar);
	evas_object_show(main_user->bar);

	main_user->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_user->icon, "images/add_user.png", NULL);
	tb = elm_toolbar_item_add(main_user->bar, main_user->icon, "Add", NULL, win);
	l = eina_list_append(l, tb);

	main_user->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_user->icon, "images/edit_user.png", NULL);
	tb = elm_toolbar_item_add(main_user->bar, main_user->icon, "Edit", user_info_cb, win);
	l = eina_list_append(l, tb);
	
	main_user->icon = elm_icon_add(win->win);
	elm_icon_file_set(main_user->icon, "images/delete_user.png", NULL);
	tb = elm_toolbar_item_add(main_user->bar, main_user->icon, "Remove", user_remove_cb, win);
	l = eina_list_append(l, tb);

	main_user->tb_list = l;
	main_user->list = elm_genlist_add(win->win);
	evas_object_smart_callback_add(main_user->list, "clicked", user_info_cb, win);
	WEIGHT(main_user->list, 1, 1);
	ALIGN(main_user->list, -1, -1);
	elm_box_pack_end(main_user->box2, main_user->list);
	evas_object_show(main_user->list);
}

