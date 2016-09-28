#include "audio_feature.h"

__ImplementSingleton(AudioFeature)

AudioFeature::AudioFeature()
{
	mFeatureName = "AudioFeature";

	__ConstructSingleton(AudioFeature)
}

AudioFeature::~AudioFeature()
{
	__DestructSingleton(AudioFeature)
}

void AudioFeature::OnFrame()
{
	Feature::OnFrame();
}

void AudioFeature::OnStart()
{
	Feature::OnStart();
}

void AudioFeature::OnStop()
{
	Feature::OnStop();
}

void AudioFeature::OnActivate()
{
	Feature::OnActivate();
}

void AudioFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}