#include "input_feature.h"

__ImplementSingleton(InputFeature)

InputFeature::InputFeature()
{
	mFeatureName = "InputFeature";

	__ConstructSingleton(InputFeature)
}

InputFeature::~InputFeature()
{
	__DestructSingleton(InputFeature)
}

void InputFeature::OnBeginFrame()
{
	Feature::OnBeginFrame();
}

void InputFeature::OnEndFrame()
{
	Feature::OnEndFrame();
}

void InputFeature::OnFrame()
{
	Feature::OnFrame();
}

void InputFeature::OnStart()
{
	Feature::OnStart();
}

void InputFeature::OnStop()
{
	Feature::OnStop();
}

void InputFeature::OnActivate()
{
	Feature::OnActivate();

	/************* TODO ************/
	// Make an InputCommandManager
	// Will use std::function  for event callbacks
	/*******************************/

}

void InputFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}