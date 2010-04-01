/*zrpc efl c functions
 *2010 Mike Blumenkrantz*/

int zrpc_VM_unpause(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.unpause");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_pause(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.pause");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_boot(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.boot");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_poweroff(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.poweroff");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_shutdown(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.shutdown");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_reboot(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.reboot");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_disableStateHandling(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.disableStateHandling");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getGraphicalConsoleTunnelPort(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getGraphicalConsoleTunnelPort");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getName(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getName");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_enableStateHandling(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.enableStateHandling");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVM(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getVM");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVMs(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("VM.getVMs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVMsFull(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("VM.getVMsFull");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getAllUsers(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getAllUsers");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getPrivilege(const char *uuid, int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("VM.getPrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_grantPrivilege(const char *uuid, int uid, int level, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid) || (!level))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	l = eina_list_append(l, (void*)&level);
	char *call;
	call = strdup("VM.grantPrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_revokePrivilege(const char *uuid, int uid, int level, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid) || (!level))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	l = eina_list_append(l, (void*)&level);
	char *call;
	call = strdup("VM.revokePrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_hasTextConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.hasTextConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_hasGraphicalConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.hasGraphicalConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getSupportedConsoles(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getSupportedConsoles");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_disconnectTextConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.disconnectTextConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_disconnectGraphicalConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.disconnectGraphicalConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_connectGraphicalConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.connectGraphicalConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_connectTextConsole(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.connectTextConsole");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_hasConsoleLock(const char *uuid, const char *type, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!type))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(type));
	char *call;
	call = strdup("VM.hasConsoleLock");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getConsoleLockSession(const char *uuid, const char *type, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!type))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(type));
	char *call;
	call = strdup("VM.getConsoleLockSession");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getConsoleClientHost(const char *uuid, const char *type, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!type))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(type));
	char *call;
	call = strdup("VM.getConsoleClientHost");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getConsoleNodeHost(const char *uuid, const char *type, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!type))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(type));
	char *call;
	call = strdup("VM.getConsoleNodeHost");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getGraphicalConsolePort(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getGraphicalConsolePort");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTextConsolePort(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getTextConsolePort");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getConsoleLockUsername(const char *uuid, const char *type, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!type))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(type));
	char *call;
	call = strdup("VM.getConsoleLockUsername");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVMid(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getVMid");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getNotes(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getNotes");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_saveNotes(const char *uuid, const char *notes, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!notes))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(notes));
	char *call;
	call = strdup("VM.saveNotes");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getParentAddress(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getParentAddress");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getParentNode(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getParentNode");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getLogs(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getLogs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTemplates(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("VM.getTemplates");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTemplate(const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("VM.getTemplate");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_needsReboot(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.needsReboot");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_save(zrpc_vm *vm, Eina_Bool maketemplate, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!vm) || (!maketemplate))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, vm);
	l = eina_list_append(l, (void*)&maketemplate);
	char *call;
	call = strdup("VM.save");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_snapshot(const char *uuid, Eina_Bool memory, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!memory))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&memory);
	char *call;
	call = strdup("VM.snapshot");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVCPUs(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getVCPUs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVNCport(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getVNCport");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getCPUtime(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getCPUtime");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getNumNETIFs(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getNumNETIFs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getNumDisks(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getNumDisks");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getMemory(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getMemory");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getMaxMemory(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getMaxMemory");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getUptime(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getUptime");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getUptimeStr(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getUptimeStr");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getState(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getState");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getStateStr(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getStateStr");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getType(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getType");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getOS(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getOS");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVNCpass(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getVNCpass");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getCPUpct(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getCPUpct");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_hasZentificTools(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.hasZentificTools");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getCPUpctHist(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getCPUpctHist");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getAvgCPUpct(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getAvgCPUpct");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getNETIFs(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getNETIFs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_offlineVif(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.offlineVif");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_offlineVifByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.offlineVifByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_onlineVif(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.onlineVif");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_onlineVifByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.onlineVifByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_detachVif(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.detachVif");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_detachVifByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.detachVifByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifName(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifName");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifNameByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifNameByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifScript(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifScript");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifScriptByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifScriptByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifMAC(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifBridge(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifBridge");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifBridgeByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifBridgeByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifType(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifType");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getVifTypeByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getVifTypeByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getBytesTotal(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getBytesTotal");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesInByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesInByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesInByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesInByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesOutByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesOutByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTotalBytesOutByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTotalBytesOutByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxPacketsByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxPacketsByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxPacketsByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxPacketsByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxPacketsByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxPacketsByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxPacketsByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxPacketsByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxBytesByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxBytesByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxBytesByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxBytesByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxBytesByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxBytesByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxBytesByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxBytesByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxDropByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxDropByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxDropByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxDropByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxDropByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxDropByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxDropByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxDropByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxErrByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxErrByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getTxErrByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getTxErrByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxErrByVifID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxErrByVifID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getRxErrByMAC(const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.getRxErrByMAC");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDisks(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("VM.getDisks");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskType(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskType");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskPath(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskPath");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskIntDev(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskIntDev");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskMode(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskMode");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskWrites(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskWrites");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskOutof(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskOutof");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_getDiskReads(const char *uuid, const char *extdev, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!extdev))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(extdev));
	char *call;
	call = strdup("VM.getDiskReads");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_VM_detachDiskByID(const char *uuid, const char *mac, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!mac))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(mac));
	char *call;
	call = strdup("VM.detachDiskByID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getLogs(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getLogs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getNode(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getNode");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getNodes(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("Node.getNodes");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getByHostname(const char *hostname, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!hostname))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(hostname));
	char *call;
	call = strdup("Node.getByHostname");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getNetworks(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getNetworks");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getAddress(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getAddress");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getNodeLoadavg(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getNodeLoadavg");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getPrivilege(const char *uuid, int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("Node.getPrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_grantPrivilege(const char *uuid, int uid, int level, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid) || (!level))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	l = eina_list_append(l, (void*)&level);
	char *call;
	call = strdup("Node.grantPrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_revokePrivilege(const char *uuid, int uid, int level, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!uid) || (!level))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&uid);
	l = eina_list_append(l, (void*)&level);
	char *call;
	call = strdup("Node.revokePrivilege");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_supportsHVM(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.supportsHVM");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_maintenanceMode(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("Node.maintenanceMode");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getStat(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Node.getStat");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Node_getStats(const char *uuid, int start_epoch, int end_epoch, int max_events, int interval, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!start_epoch) || (!end_epoch) || (!max_events) || (!interval))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, (void*)&start_epoch);
	l = eina_list_append(l, (void*)&end_epoch);
	l = eina_list_append(l, (void*)&max_events);
	l = eina_list_append(l, (void*)&interval);
	char *call;
	call = strdup("Node.getStats");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_isUser(const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("User.isUser");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_isActive(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("User.isActive");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUsername(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("User.getUsername");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_logout(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("User.logout");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_logoutByUID(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (uid < 0))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("User.logoutByUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_login(const char *user, const char *pass, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!user) || (!pass))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(user));
	l = eina_list_append(l, strdup(pass));
	char *call;
	call = strdup("User.login");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUsers(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("User.getUsers");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUser(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("User.getUser");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUserByName(const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("User.getUserByName");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUserUID(const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("User.getUserUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_getUserByUID(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (uid < 0))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("User.getUserByUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_addUser(zrpc_user *new, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!new))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, new);
	char *call;
	call = strdup("User.addUser");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_setPassword(const char *oldpassword, const char *password, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!oldpassword) || (!password))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(oldpassword));
	l = eina_list_append(l, strdup(password));
	char *call;
	call = strdup("User.setPassword");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_setPasswordByUID(int uid, const char *password, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uid) || (!password))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	l = eina_list_append(l, strdup(password));
	char *call;
	call = strdup("User.setPasswordByUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_User_removeUser(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("User.removeUser");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Session_checkSession(const char *sessid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!sessid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(sessid));
	char *call;
	call = strdup("Session.checkSession");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Session_getSession(const char *sessid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!sessid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(sessid));
	char *call;
	call = strdup("Session.getSession");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_log(const char *msg, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!msg))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(msg));
	char *call;
	call = strdup("Zentific.log");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_getConfig(const char *key, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!key))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(key));
	char *call;
	call = strdup("Zentific.getConfig");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_getConfigPriv(const char *key, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!key))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(key));
	char *call;
	call = strdup("Zentific.getConfigPriv");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_setConfig(const char *key, const char *value, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!key) || (!value))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(key));
	l = eina_list_append(l, strdup(value));
	char *call;
	call = strdup("Zentific.setConfig");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_getFrontendPlugins(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("Zentific.getFrontendPlugins");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_modifyPlugin(const char *name, Eina_Bool enabled, Eina_Bool xmlrpc, Eina_Bool frontend, Eina_Bool scheduler, Eina_Bool poller, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name) || (!enabled) || (!xmlrpc) || (!frontend) || (!scheduler) || (!poller))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	l = eina_list_append(l, (void*)&enabled);
	l = eina_list_append(l, (void*)&xmlrpc);
	l = eina_list_append(l, (void*)&frontend);
	l = eina_list_append(l, (void*)&scheduler);
	l = eina_list_append(l, (void*)&poller);
	char *call;
	call = strdup("Zentific.modifyPlugin");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_isFrontendPluginEnabled(const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("Zentific.isFrontendPluginEnabled");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_getAllPlugins(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("Zentific.getAllPlugins");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Zentific_configPush(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Zentific.configPush");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJob(int id, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!id))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&id);
	char *call;
	call = strdup("Scheduler.getJob");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJobs(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("Scheduler.getJobs");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJobsByUID(int uid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&uid);
	char *call;
	call = strdup("Scheduler.getJobsByUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJobsByUUID(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Scheduler.getJobsByUUID");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJobStatus(int jobid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!jobid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&jobid);
	char *call;
	call = strdup("Scheduler.getJobStatus");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Scheduler_getJobsStatus(int *jobids, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!jobids))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, (void*)&*jobids);
	char *call;
	call = strdup("Scheduler.getJobsStatus");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_system_listMethods(zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon))
		return 0;
	Eina_List *l = NULL;
	char *call;
	call = strdup("system.listMethods");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_system_methodHelp(const char *methodname, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!methodname))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(methodname));
	char *call;
	call = strdup("system.methodHelp");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_system_methodSignature(const char *methodname, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!methodname))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(methodname));
	char *call;
	call = strdup("system.methodSignature");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Network_getBridges(const char *uuid, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	char *call;
	call = strdup("Network.getBridges");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}
int zrpc_Network_getBridge(const char *uuid, const char *name, zrpc_con *zcon, zrpc_network_cb cb, void *cbd)
{
	if ((!zcon) || (!uuid) || (!name))
		return 0;
	Eina_List *l = NULL;
	l = eina_list_append(l, strdup(uuid));
	l = eina_list_append(l, strdup(name));
	char *call;
	call = strdup("Network.getBridge");

	if (!zrpc_meta(call, l, zcon, cb, cbd))
		return 0;

	return 1;
}