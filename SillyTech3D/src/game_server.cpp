#include "game_server.h"

__ImplementSingleton(GameServer)

GameServer::GameServer()
{
	__ConstructSingleton(GameServer)
		if (_instance != 0)
			LOG_INFO() << "Created GameServer";
}

GameServer::~GameServer()
{
	__DestructSingleton(GameServer)
}

void GameServer::Start()
{
	//__LogTime("");

	mFeatures["PhysicsFeature"]->OnStart();		//__LogTime("OnStart:PhysicsFeature");
	mFeatures["InputFeature"]->OnStart();		//__LogTime("OnStart:InputFeature");
	mFeatures["GameFeature"]->OnStart();		//__LogTime("OnStart:GameFeature");
	mFeatures["AudioFeature"]->OnStart();		//__LogTime("OnStart:AudioFeature");
	mFeatures["ScriptFeature"]->OnStart();		//__LogTime("OnStart:ScriptFeature");
	mFeatures["GraphicsFeature"]->OnStart();	//__LogTime("OnStart:GraphicsFeature");

	
}

void GameServer::Update()
{
	//std::cout << "update" << std::endl;
	
	// OnBeginFrame
	{	__LogTime("");
		mFeatures["PhysicsFeature"]->OnBeginFrame();		__LogTime("OnBeginFrame:PhysicsFeature");
		mFeatures["InputFeature"]->OnBeginFrame();			__LogTime("OnBeginFrame:InputFeature");
		mFeatures["GameFeature"]->OnBeginFrame();			__LogTime("OnBeginFrame:GameFeature");
		mFeatures["AudioFeature"]->OnBeginFrame();			__LogTime("OnBeginFrame:AudioFeature");
		mFeatures["ScriptFeature"]->OnBeginFrame();			__LogTime("OnBeginFrame:ScriptFeature");
		mFeatures["GraphicsFeature"]->OnBeginFrame();		__LogTime("OnBeginFrame:GraphicsFeature");
	}

	// OnFrame
	{__LogTime("");
		mFeatures["PhysicsFeature"]->OnFrame();				__LogTime("OnFrame:PhysicsFeature");
		mFeatures["InputFeature"]->OnFrame();				__LogTime("OnFrame:InputFeature");
		mFeatures["GameFeature"]->OnFrame();				__LogTime("OnFrame:GameFeature");
		mFeatures["AudioFeature"]->OnFrame();				__LogTime("OnFrame:AudioFeature");
		mFeatures["ScriptFeature"]->OnFrame();				__LogTime("OnFrame:ScriptFeature");
		mFeatures["GraphicsFeature"]->OnFrame();			__LogTime("OnFrame:GraphicsFeature");
	}

	// OnEndFrame
	{
		mFeatures["PhysicsFeature"]->OnEndFrame();
		mFeatures["InputFeature"]->OnEndFrame();
		mFeatures["GameFeature"]->OnEndFrame();
		mFeatures["AudioFeature"]->OnEndFrame();
		mFeatures["ScriptFeature"]->OnEndFrame();
		mFeatures["GraphicsFeature"]->OnEndFrame();
	}

}

void GameServer::AttachFeature(Feature *arg_feature)
{
	__Assert(arg_feature != 0);
	__Assert(mFeatures[arg_feature->GetFeatureName()] == 0);

	arg_feature->OnActivate();
	mFeatures[arg_feature->GetFeatureName()] = arg_feature;
}

void GameServer::DetachFeature(Feature *arg_feature)
{
	__Assert(arg_feature != 0);
	__Assert(mFeatures[arg_feature->GetFeatureName()] != 0);

	arg_feature->OnDeactivate();
	mFeatures[arg_feature->GetFeatureName()] = 0;
}

void GameServer::PrintTimeLog()
{
	mTimer.PrintTimeLog();
}