#ifndef VM_ACTIONS_H
#define VM_ACTIONS_H

void vm_hibernate_cb(void *data, Evas_Object *obj, void *event_info);
void vm_destroy_cb(void *data, Evas_Object *obj, void *event_info);
void vm_shutdown_cb(void *data, Evas_Object *obj, void *event_info);
void vm_reboot_cb(void *data, Evas_Object *obj, void *event_info);
void vm_pause_cb(void *data, Evas_Object *obj, void *event_info);
void vm_unpause_cb(void *data, Evas_Object *obj, void *event_info);
void vm_info_cb(void *data, Evas_Object *obj, void *event_info);

#endif
