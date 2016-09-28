#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <memory>

class AudioComponent;

class AudioManager : public Manager
{
	__DeclareSingleton(AudioManager)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	void AttachAudioComponent(AudioComponent *arg_audiosource);
	void DetachAudioComponent(AudioComponent *arg_audiosource);

private:
	AudioManager();
	~AudioManager();

private:
	std::vector<AudioComponent*> mAudioComponents;
};


#endif