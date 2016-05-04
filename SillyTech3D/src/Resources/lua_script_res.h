#ifndef LUASCRIPTRES_H
#define LUASCRIPTRES_H

#include "resource.h"

class LuaScriptRes : public Resource
{

public:
	LuaScriptRes(const char *arg_name, const char * arg_path);
	~LuaScriptRes();

private:
	std::string mScript;

public:
	void Reload() override;

	std::string GetScript();
};

#endif