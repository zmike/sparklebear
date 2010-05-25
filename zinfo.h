#ifndef ZINFO_H
#define ZINFO_H

int zinfo_job_updatevm(void *data);
zrpc_user* zinfo_user_findbyuid(int id);
void zinfo_updateuser(void *data, Evas_Object *obj, void *event_info);
void zinfo_destroy_hover(void *data, Evas_Object *obj, void *event_info);
void zinfo_keybind(void *data, Evas_Event_Key_Down *key);
void zinfo_vm_state_change(void *data, Evas_Object *obj, void *event_info);
void zinfo_updateuser_state(void *data, Evas_Object *obj, void *event_info);
void zinfo_updateuser_level(void *data, Evas_Object *obj, void *event_info);

#endif
