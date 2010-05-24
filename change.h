#ifndef CHANGE_H
#define CHANGE_H

void change_zlogin_to_zmain(const char *reply, void *data);
void change_zmain_to_zlogin(void *data, Evas_Object *obj, void *event_info);
void change_zinfo_to_zlogin(void *data, Evas_Object *obj, void *event_info);
void change_zinfo_to_zmain(void *data, Evas_Object *obj, void *event_info);

#endif
