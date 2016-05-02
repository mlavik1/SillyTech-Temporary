#include "game_feature.h"

__ImplementSingleton(GameFeature)

GameFeature::GameFeature()
{
	mFeatureName = "GameFeature";

	__ConstructSingleton(GameFeature)
}

GameFeature::~GameFeature()
{
	__DestructSingleton(GameFeature)
}

void GameFeature::OnBeginFrame()
{
	Feature::OnBeginFrame();
}

void GameFeature::OnEndFrame()
{
	Feature::OnEndFrame();
}

void GameFeature::OnFrame()
{
	Feature::OnFrame();
}

void GameFeature::OnStart()
{
	Feature::OnStart();
}

void GameFeature::OnStop()
{
	Feature::OnStop();
}

void GameFeature::OnActivate()
{
	Feature::OnActivate();
}

void GameFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}