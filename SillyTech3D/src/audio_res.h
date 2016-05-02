#ifndef AUDIORES_H
#define AUDIORES_H

#include "resource.h"
#include "alut.h"

class AudioRes : public Resource
{

public:
	AudioRes(const char *arg_name, const char *arg_path);
	~AudioRes();

private:
	ALuint mBuffer;

public:
	void Reload() override;

	ALuint GetBuffer();
};

#endif