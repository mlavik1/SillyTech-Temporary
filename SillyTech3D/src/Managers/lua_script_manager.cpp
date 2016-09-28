#include "lua_script_manager.h"

#include "resource_manager.h"
#include "lua_script_res.h"

#include <string>

__ImplementSingleton(LuaScriptManager)

LuaScriptManager::LuaScriptManager()
{
	__ConstructSingleton(LuaScriptManager)
}


LuaScriptManager::~LuaScriptManager()
{
	__DestructSingleton(LuaScriptManager)
}

void LuaScriptManager::OnFrame()
{
	Manager::OnFrame();

	callScripts("Update");

}

void LuaScriptManager::OnStart()
{
	Manager::OnStart();

	RunScriptOnce("Resources/init.lua");

}

void LuaScriptManager::OnStop()
{
	Manager::OnStop();

}

void LuaScriptManager::OnActivate()
{
	Manager::OnActivate();
}

void LuaScriptManager::OnDeactivate()
{
	Manager::OnDeactivate();
}


void LuaScriptManager::AttachScriptComponent(LuaScriptComponent *arg_comp)
{
	mScriptComponents.push_back(arg_comp);
}

void LuaScriptManager::RemoveScriptComponent(LuaScriptComponent *arg_comp)
{
	for (size_t i = 0; i < mScriptComponents.size(); i ++)
		if(mScriptComponents[i] == arg_comp)
			mScriptComponents.erase(mScriptComponents.begin() + i);
}

void LuaScriptManager::callScripts(const char *arg_function)
{
	for (LuaScriptComponent *comp : mScriptComponents)
	{

		lua_State *luaState = comp->mLuaState;
		

		if (!luaState)
		{
			luaState = luaL_newstate();
			comp->mLuaState = luaState;
			luabind::open(luaState);
			luaL_openlibs(luaState);
			LuaGlue::BindAll(luaState, comp->GetParent());
			compileScript(luaState, comp);
			
		}
		if (comp->GetScriptName() == "")
			continue;

		luabind::open(luaState);

		
		//luaopen_math(luaState);


		try
		{
			luabind::call_function<void>(luaState, arg_function);
		}
		catch (luabind::error e)
		{
			LOG_ERROR() << "Failed to call Lua function.";
		}

		//lua_close(luaState);
	}
}

void LuaScriptManager::RunScriptOnce(const char *arg_file)
{
	lua_State *luaState = luaL_newstate();
	luabind::open(luaState);
	

	LuaGlue::BindAll(luaState, 0);

	
	if(luaL_dofile(luaState, arg_file))
		LOG_ERROR() << "Failed to run script(luaL_dofile): " << arg_file;

		//if (luaL_dostring(luaState, res->GetScript().c_str()))
		//	LOG_ERROR() << "Failed to run script(luaL_dostring): " << comp->GetScriptName();

	try
	{
		//luabind::call_function<void>(luaState, arg_function);
	}
	catch (luabind::error e)
	{
		LOG_ERROR() << "Failed to call Lua function.";
		LOG_EXCEPTION() << lua_tostring(luaState, -1);
	}

	lua_close(luaState);
}

void LuaScriptManager::RunTerminalInput()
{
	std::string terminalString;
	std::getline(std::cin, terminalString);

	lua_State *luaState = luaL_newstate();
	luabind::open(luaState);

	LuaGlue::BindAll(luaState, 0);

	
	if (luaL_dostring(luaState, terminalString.c_str()))
	{
		LOG_ERROR() << "Failed to run script(luaL_dostring): " << terminalString;
		LOG_EXCEPTION() << lua_tostring(luaState, -1);
	}
		

		//if (luaL_dostring(luaState, res->GetScript().c_str()))
		//	LOG_ERROR() << "Failed to run script(luaL_dostring): " << comp->GetScriptName();

	try
	{
		//luabind::call_function<void>(luaState, arg_function);
	}
	catch (luabind::error e)
	{
		LOG_ERROR() << "Failed to call Lua function.";
		LOG_EXCEPTION() << lua_tostring(luaState, -1);
	}

	lua_close(luaState);
}

void LuaScriptManager::RecompileScripts()
{
	for (LuaScriptComponent *comp : mScriptComponents)
	{
		LuaScriptRes *res = ResourceManager<LuaScriptRes>::Instance()->GetResource(comp->GetScriptName().c_str());
		if (res)
			res->Reload();
		else
			continue;
		lua_State *luaState = comp->mLuaState;
		compileScript(luaState, comp);
	}
}

void LuaScriptManager::compileScript(lua_State *luaState, LuaScriptComponent *comp)
{
	

	LuaScriptRes *res = ResourceManager<LuaScriptRes>::Instance()->GetResource(comp->GetScriptName().c_str());

	if (!res)
	{
		LOG_ERROR() << "Failed to load LuaScript resource: " << comp->GetScriptName();
		return;
	}

	if (luaL_dostring(luaState, res->GetScript().c_str()))
	{
		LOG_ERROR() << "Failed to run script(luaL_dostring): " << comp->GetScriptName();
		LOG_EXCEPTION() << lua_tostring(luaState, -1);
	}
}