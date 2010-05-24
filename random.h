#ifndef RANDOM_H
#define RANDOM_H

void key_press(void *data, Evas *a, Evas_Object *obj, void *event_info);
vmitem *new_vmitem(void);
void free_vmitem(vmitem *item);
useritem *new_useritem(void);
void free_useritem(useritem *item);
void exit_wrapper(void *data, Evas_Object *obj, void *event_info);

const char *get_os_icon(const zrpc_vm *vm);
const char *get_state_icon(const char *state);
const char *get_state_name(const char *state);
const char *get_access_icon(int level);
const char *get_access_name(int level);
const char *get_access_name(int level);

#endif
