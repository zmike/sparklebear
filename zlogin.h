#ifndef ZLOGIN_H
#define ZLOGIN_H

void zlogin_keybind(void *data, Evas_Event_Key_Down *key);
void zlogin_try(void *data, Evas_Object *obj, void *event_info);
void zlogin_stop(void *data);
void zlogin_start(void *data);

#endif
