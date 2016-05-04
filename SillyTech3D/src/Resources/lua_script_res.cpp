#include "lua_script_res.h"
#include "text_file_reader.h"
#include "lua_script_manager.h"

LuaScriptRes::LuaScriptRes(const char *arg_name, const char * arg_path) : Resource::Resource(arg_name, arg_path)
{
	
	Reload();

}

LuaScriptRes::~LuaScriptRes()
{

}


void LuaScriptRes::Reload()
{
	Resource::Reload();

	mScript = TextFileReader::ReadString(mResourcePath.c_str());
}


std::string LuaScriptRes::GetScript()
{
	return mScript;
}