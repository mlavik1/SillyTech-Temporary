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

	mFeatures["NetworkingFeature"]->OnStart();	//__LogTime("OnStart:NetworkingFeature");
	mFeatures["PhysicsFeature"]->OnStart();		//__LogTime("OnStart:PhysicsFeature");
	mFeatures["InputFeature"]->OnStart();		//__LogTime("OnStart:InputFeature");
	mFeatures["GameFeature"]->OnStart();		//__LogTime("OnStart:GameFeature");
	mFeatures["AudioFeature"]->OnStart();		//__LogTime("OnStart:AudioFeature");
	mFeatures["ScriptFeature"]->OnStart();		//__LogTime("OnStart:ScriptFeature");
	mFeatures["GraphicsFeature"]->OnStart();	//__LogTime("OnStart:GraphicsFeature");

	mGraphicsThread = new ST_Thread([&]() -> void{ mFeatures["GraphicsFeature"]->OnFrame(); });
	mInputThead = new ST_Thread([&]() -> void { mFeatures["InputFeature"]->OnFrame(); });
	mAudioThread = new ST_Thread([&]() -> void { mFeatures["AudioFeature"]->OnFrame(); });
}

void GameServer::Update()
{

	//mAudioThread->Execute();
	//mAudioThread->WaitForThread();

	// OnFrame
	{__LogTime("");
		mFeatures["NetworkingFeature"]->OnFrame();			__LogTime("OnFrame:NetworkingFeature");
		mFeatures["GraphicsFeature"]->OnFrame();			__LogTime("OnFrame:GraphicsFeature");
		mFeatures["PhysicsFeature"]->OnFrame();				__LogTime("OnFrame:PhysicsFeature");
		mFeatures["InputFeature"]->OnFrame();				__LogTime("OnFrame:InputFeature");
		mFeatures["AudioFeature"]->OnFrame();				__LogTime("OnFrame:AudioFeature");
		mFeatures["GameFeature"]->OnFrame();				__LogTime("OnFrame:GameFeature");
		mFeatures["ScriptFeature"]->OnFrame();				__LogTime("OnFrame:ScriptFeature");
		
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