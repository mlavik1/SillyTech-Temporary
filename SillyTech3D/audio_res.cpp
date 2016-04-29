#include "audio_res.h"
#include "text_file_reader.h"
#include "lua_script_manager.h"

AudioRes::AudioRes(const char *arg_name, const char *arg_path) : Resource::Resource(arg_name, arg_path)
{

	Reload();
}

AudioRes::~AudioRes()
{
	alDeleteBuffers(1, &mBuffer);
}


void AudioRes::Reload()
{
	Resource::Reload();

	ALenum error;

	// TODO
	// Use resources instead

	/* Create an AL buffer from the given sound file. */
	mBuffer = alutCreateBufferFromFile(mResourcePath.c_str());
	if (mBuffer == AL_NONE)
	{
		error = alutGetError();
		LOG_ERROR() << "Error loading file: " << alutGetErrorString(error);
		//alutExit();
	}
	
}


ALuint AudioRes::GetBuffer()
{
	return mBuffer;
}