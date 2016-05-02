#include "Audio_manager.h"

#include <openal/alut.h>
#include "audio_component.h"

__ImplementSingleton(AudioManager)

AudioManager::AudioManager()
{
	__ConstructSingleton(AudioManager)
}


AudioManager::~AudioManager()
{
	alcMakeContextCurrent(NULL);

	__DestructSingleton(AudioManager)
}

void AudioManager::OnBeginFrame()
{
	Manager::OnBeginFrame();

	for (AudioComponent *comp : mAudioComponents)
	{
		comp->ContinueAudio();
	}
}

void AudioManager::OnEndFrame()
{
	Manager::OnEndFrame();
}

void AudioManager::OnFrame()
{
	Manager::OnFrame();
}

void AudioManager::OnStart()
{
	Manager::OnStart();

}

void AudioManager::OnStop()
{
	Manager::OnStop();

	if (!alutExit())
	{
		ALenum error = alutGetError();
		LOG_ERROR() << alutGetErrorString(error);
	}
}

void AudioManager::OnActivate()
{
	Manager::OnActivate();

	// Initialise alut
	if (!alutInit(NULL, NULL))
	{
		ALenum error = alutGetError();
		LOG_ERROR() << alutGetErrorString(error);
	}
	else
	{
		LOG_INFO() << "Successfully initialised alut version " << alutGetMajorVersion() << "." << alutGetMinorVersion();
	}
}

void AudioManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

void AudioManager::AttachAudioComponent(AudioComponent *arg_audiosource)
{
	arg_audiosource->BufferAudio();
	mAudioComponents.push_back(arg_audiosource);
}
void AudioManager::DetachAudioComponent(AudioComponent *arg_audiosource)
{
	std::vector<AudioComponent*>::iterator pos = std::find(mAudioComponents.begin(), mAudioComponents.end(), arg_audiosource);
	if (pos != mAudioComponents.end()) // == myVector.end() means the element was not found
		mAudioComponents.erase(pos);
}