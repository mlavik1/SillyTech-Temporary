#ifndef LUASCRIPTMANAGER_H
#define LUASCRIPTMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <vector>
#include "lua_script_component.h"
#include "lua_glue.h"


class LuaScriptComponent;

class LuaScriptManager : public Manager
{
	__DeclareSingleton(LuaScriptManager)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	void AttachScriptComponent(LuaScriptComponent *arg_comp);
	void RemoveScriptComponent(LuaScriptComponent *arg_comp);

	void RunScriptOnce(const char *arg_file);
	void RunTerminalInput();
	void RecompileScripts();


private:
	LuaScriptManager();
	~LuaScriptManager();

	std::vector<LuaScriptComponent*> mScriptComponents;

	void callScripts(const char *arg_function);
	void compileScript(lua_State *luaState, LuaScriptComponent *comp);

};


#endif