#ifndef LUAGLUE_H
#define LUAGLUE_H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "luabind\luabind.hpp"
#include "luabind\operator.hpp"

#include <stdlib.h>
#include "actor.h"

class LuaGlue
{
public:
	static void BindAll(lua_State *luaState, Actor * arg_actor);

	static void LoadScript(lua_State *luaState, const char *arg_script, const char *arg_name);
	static void ExecuteScript(lua_State *luaState, const char *arg_name, const char *arg_function);

};

#endif