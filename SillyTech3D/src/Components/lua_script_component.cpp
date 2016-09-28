#include "lua_script_component.h"

#include "lua_script_manager.h"
#include "resource_manager.h"
#include "lua_script_res.h"

LuaScriptComponent::LuaScriptComponent() : ScriptComponent()
{
	this->mLuaState = 0;
}

LuaScriptComponent::~LuaScriptComponent()
{
}


void LuaScriptComponent::OnFrame()
{
	ScriptComponent::OnFrame();
}

void LuaScriptComponent::OnStart()
{
	ScriptComponent::OnStart();

}

void LuaScriptComponent::OnStop()
{
	ScriptComponent::OnStop();
}

void LuaScriptComponent::OnActivate()
{
	ScriptComponent::OnActivate();
	LuaScriptManager::Instance()->AttachScriptComponent(this);

	if (GetScriptName() == "")
		LOG_WARNING() << "LuaScriptComponent has no script";

}

void LuaScriptComponent::OnDeactivate()
{
	ScriptComponent::OnDeactivate();
	LuaScriptManager::Instance()->RemoveScriptComponent(this);
}

void LuaScriptComponent::SetScript(const char*arg_script_name)
{
	if(!ResourceManager<LuaScriptRes>::Instance()->GetResource(arg_script_name))
		ResourceManager<LuaScriptRes>::Instance()->AddResource(new LuaScriptRes(arg_script_name, arg_script_name));

	ScriptComponent::SetScript(arg_script_name);
}