#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include "component.h"
#include "alut.h"
#include <string>

class AudioComponent : public Component
{
public:
	AudioComponent(const char* arg_filename);
	~AudioComponent();

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	void SetAudioFile(const char* arg_file);
	void Set3DSound(bool arg_enable);
	void SetMinDistance(float arg_distance);
	void SetMaxDistance(float arg_distance);

	void SetLooping(bool arg_looping);
	void BufferAudio();
	bool StartAudio();
	bool ContinueAudio();
	void Play();

	std::string GetAudioFile();

private:
	//ALuint mBuffer;
	ALuint mSource;
	ALint mStatus;
	std::string mFilename;
	bool m3DSound;
	bool mLooping;
	float mMinDistance;
	float mMaxDistance;

};

#endif