#include "audio_component.h"
#include "actor.h"
#include "audio_manager.h"
#include "camera_manager.h"
#include "camera_component.h"
#include "audio_res.h"
#include "resource_manager.h"

AudioComponent::AudioComponent(const char *arg_filename) : Component()
{
	//mBuffer = 0;
	mSource = 0;
	//mStatus = -1;
	mFilename = arg_filename;
	mMinDistance = 50.0f;
	mMaxDistance = 50000.0f;
}

AudioComponent::~AudioComponent()
{
	alDeleteSources(1, &mSource);
	//alDeleteBuffers(1, &mBuffer);
}



void AudioComponent::OnBeginFrame()
{
	Component::OnBeginFrame();
}

void AudioComponent::OnEndFrame()
{
	Component::OnEndFrame();
}

void AudioComponent::OnFrame()
{
	Component::OnFrame();
}

void AudioComponent::OnStart()
{
	Component::OnStart();
}

void AudioComponent::OnStop()
{
	Component::OnStop();
}

void AudioComponent::OnActivate()
{
	Component::OnActivate();
	AudioManager::Instance()->AttachAudioComponent(this);

}

void AudioComponent::OnDeactivate()
{
	Component::OnDeactivate();
	AudioManager::Instance()->DetachAudioComponent(this);
}

void AudioComponent::SetAudioFile(const char* arg_file)
{
	mFilename = arg_file;
}
std::string AudioComponent::GetAudioFile()
{
	return mFilename;
}

void AudioComponent::BufferAudio()
{
	ALenum error;
	AudioRes *res = ResourceManager<AudioRes>::Instance()->GetResource(mFilename.c_str());
	if (!res)
		res = ResourceManager<AudioRes>::Instance()->AddResource(new AudioRes(mFilename.c_str(), mFilename.c_str()));

	// TODO
	// Use resources instead

	/* Generate a single source, attach the buffer to it and start playing. */
	alGenSources(1, &mSource);
}

bool AudioComponent::StartAudio()
{
	ALenum error;

	ALuint buffer = ResourceManager<AudioRes>::Instance()->GetResource(mFilename.c_str())->GetBuffer();

	
	
	alSourcei(mSource, AL_BUFFER, buffer);

	
	//alSourcei(mSource, AL_LOOPING, AL_FALSE);
	//for (int i = 0; i < 5; i++)
	//	alSourceQueueBuffers(mSource,1, &buffer);




	if (mStatus == AL_PLAYING)
	{
		//alSourceStop(mSource);
		alSourceRewind(mSource);
	}
	// else
	alSourcePlay(mSource);

	mStatus = AL_PLAYING;
		

	/* Why does this return an error?? */
	error = alGetError();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		LOG_ERROR() << "Error after alSourcePlay():" << alGetString(error);
		return false;
		//alutExit();
	}
	

	return true;
}

bool AudioComponent::ContinueAudio()
{
	//LOG_INFO() << mStatus;
	/****** TODO: Change, and move to UpdateAudio-method ******/
	/* Check every 0.1 seconds if the sound is still playing. */
	//do
	//{
	//	alutSleep(0.1f);
	//	alGetSourcei(mSource, AL_SOURCE_STATE, &mStatus);
	//} while (mStatus == AL_PLAYING);
	alGetSourcei(mSource, AL_SOURCE_STATE, &mStatus);


	if (mStatus == AL_PLAYING)
	{
		// 3D audio source?
		if (m3DSound)
		{
			/****** TODO: Do some of this ONCE, in AudioManager *****/
			glm::vec3 p = GetParent()->GetTransform().GetGlobalPosition();
			glm::vec3 v = GetParent()->GetVelocity();
			Actor *camAc = CameraManager::Instance()->GetMainCameraComponent()->GetParent();			
			glm::vec3 c = camAc->GetTransform().GetGlobalPosition();
			glm::vec3 f = camAc->GetTransform().Forward();
			glm::vec3 u = camAc->GetTransform().Up();
			glm::vec3 cv = camAc->GetVelocity();

			alSourcei(mSource, AL_REFERENCE_DISTANCE, mMinDistance);
			alSourcei(mSource, AL_MAX_DISTANCE, mMaxDistance);

			ALfloat listenerPos[] = { c.x,c.y,c.z };// optional
			ALfloat listenerVel[] = { cv.x,cv.y,cv.z };// optional
			ALfloat listenerOri[] = { f.x,f.y,f.z, u.x,u.y,u.z };// optional
			ALfloat source0Pos[] = { p.x,p.y,p.z };// optional
			ALfloat source0Vel[] = { v.x,v.y,v.z };// optional
			//ALfloat source0Vel[] = { 2.0, 0.0, 5.0 };// optional
			alListenerfv(AL_POSITION, listenerPos);// optional
			alListenerfv(AL_VELOCITY, listenerVel);// optional
			alListenerfv(AL_ORIENTATION, listenerOri);// optional

			alSourcef(mSource, AL_PITCH, 1.0f);// optional	
			alSourcef(mSource, AL_GAIN, 1.0f);// optional
			alSourcefv(mSource, AL_POSITION, source0Pos);// optional
			alSourcefv(mSource, AL_VELOCITY, source0Vel);// optional

														 //alSourcei(source, AL_LOOPING, AL_TRUE);// optional
		}
	}
	else
	{
		if (m3DSound)
		{
			//alSourceRewind(mSource);
			alSourcePlay(mSource);
			mStatus = AL_PLAYING;
			//StartAudio();
		}
		else
			return false;
	}

	return true;
}

void AudioComponent::Play()
{
	StartAudio();
}

void AudioComponent::Set3DSound(bool arg_enable)
{
	m3DSound = arg_enable;
}

void AudioComponent::SetMinDistance(float arg_distance)
{
	mMinDistance = arg_distance;
}

void AudioComponent::SetMaxDistance(float arg_distance)
{
	mMaxDistance = arg_distance;
}

void AudioComponent::SetLooping(bool arg_looping)
{
	mLooping = arg_looping;
}