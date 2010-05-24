#ifndef LIST_OPS_H
#define LIST_OPS_H

void list_op_sel(void *data, Evas_Object *obj, void *event_info);
Eina_Bool list_op_state_get(const void *data, Evas_Object *obj, const char *part);
void list_op_del(const void *data, Evas_Object *obj);
char *list_op_vm_label_get(const void *data, Evas_Object *obj, const char *part);
char *list_op_user_label_get(const void *data, Evas_Object *obj, const char *part);
Evas_Object *list_op_vm_icon_get(const void *data, Evas_Object *obj, const char *part);
Evas_Object *list_op_user_icon_get(const void *data, Evas_Object *obj, const char *part);

#endif
