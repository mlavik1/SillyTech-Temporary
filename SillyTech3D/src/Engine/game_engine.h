#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "singleton.h"
#include "debug.h"
#include "game_server.h"
#include <SDL.h>
#include "feature_fwd_decl.h"
#include "st_assert.h"

#include "lua_script_component.h"
#include "lua_script_manager.h"
#include "resource_manager.h"


class GameEngine
{
	__DeclareSingleton(GameEngine)

public:
	void Start();
	void Initialise();

private:
	GameEngine();
	~GameEngine();

private:
	void createFeatures();

private:
	GameServer *gameServer;
	bool running;
	bool paused;
	bool initialised;
	Uint32 time_ms;
	
};

#endif
