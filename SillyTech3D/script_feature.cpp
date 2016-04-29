#include "script_feature.h"

__ImplementSingleton(ScriptFeature)

ScriptFeature::ScriptFeature()
{
	mFeatureName = "ScriptFeature";

	__ConstructSingleton(ScriptFeature)
}

ScriptFeature::~ScriptFeature()
{
	__DestructSingleton(ScriptFeature)
}

void ScriptFeature::OnBeginFrame()
{
	Feature::OnBeginFrame();
}

void ScriptFeature::OnEndFrame()
{
	Feature::OnEndFrame();
}

void ScriptFeature::OnFrame()
{
	Feature::OnFrame();
}

void ScriptFeature::OnStart()
{
	Feature::OnStart();
}

void ScriptFeature::OnStop()
{
	Feature::OnStop();
}

void ScriptFeature::OnActivate()
{
	Feature::OnActivate();
}

void ScriptFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}
