#ifndef XML_H
#define XML_H

#include <libxml/parser.h>
#include <libxml/tree.h>

inline xmlNode *xml_safenext(xmlNode *node);

int 		xml_parse_int(xmlNode *node);
int*		xml_parse_users(xmlNode *node);
zrpc_user *	xml_parse_user(xmlNode *node);
zrpc_vm*	xml_parse_vm(xmlNode *node);
Eina_List *	xml_parse_vmsfull(xmlNode *node);
xmlNode *	xml_parse_xml(const char *charxml);

void		xml_new_call(xmlDocPtr doc, const char *method);
void		xml_new_string(xmlDocPtr doc, const char *string);
void		xml_new_int(xmlDocPtr doc, int i, int array);
void		xml_new_array(xmlDocPtr doc);
void		xml_new_user(xmlDocPtr doc, zrpc_user *user);
void		xml_new_moduser(xmlDocPtr doc, Eina_List *uid);

#endif
