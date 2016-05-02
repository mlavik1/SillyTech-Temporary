#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "component.h"
#include <string>

class ScriptComponent : public Component
{
public:

	virtual void OnBeginFrame() override;
	virtual void OnFrame() override;
	virtual void OnEndFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;

public:
	virtual void SetScript(const char*arg_script_name);

public:
	ScriptComponent();
	~ScriptComponent();

protected:
	std::string mScriptName;

public:
	std::string GetScriptName();
};


#endif