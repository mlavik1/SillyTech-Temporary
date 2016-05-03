#include "script_component.h"

#include "debug.h"

ScriptComponent::ScriptComponent()
{
	mIsActive = false;
}

ScriptComponent::~ScriptComponent()
{

}



void ScriptComponent::OnBeginFrame()
{
	Component::OnBeginFrame();
}

void ScriptComponent::OnEndFrame()
{
	Component::OnEndFrame();
}

void ScriptComponent::OnFrame()
{
	Component::OnFrame();
}

void ScriptComponent::OnStart()
{
	Component::OnStart();



}

void ScriptComponent::OnStop()
{
	Component::OnStop();
}

void ScriptComponent::OnActivate()
{
	Component::OnActivate();
}

void ScriptComponent::OnDeactivate()
{
	Component::OnDeactivate();

}

void ScriptComponent::SetScript(const char*arg_script_name)
{

	mScriptName = std::string(arg_script_name);
}

std::string ScriptComponent::GetScriptName()
{
	return mScriptName;
}
