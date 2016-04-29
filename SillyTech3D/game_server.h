#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "singleton.h"
#include "debug.h"
#include <map>
#include <string>
#include "feature_fwd_decl.h"
#include "game_feature.h"
#include "timer.h"

#define __LogTime(ID) (mTimer.LogTime(ID))

class GameServer
{
	__DeclareSingleton(GameServer)

public:
	void Start();
	void Update();
	
	void AttachFeature(Feature *arg_feature);
	void DetachFeature(Feature *arg_feature);
	void PrintTimeLog();

private:
	GameServer();
	~GameServer();

	
	std::map<std::string, Feature*> mFeatures;
	Timer mTimer; // DO NOT CHANGE: used by __LogTime()-macro
};

#endif