#ifndef LUASCRIPTCOMPONENT_H
#define LUASCRIPTCOMPONENT_H

#include "script_component.h"

struct lua_State;
class LuaScriptComponent : public ScriptComponent
{
public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	void SetScript(const char*arg_script_name);

public:
	LuaScriptComponent();
	~LuaScriptComponent();

	lua_State *mLuaState;


};


#endif