#ifndef AUDIOFEATURE_H
#define AUDIOFEATURE_H

#include "feature.h"
#include "singleton.h"

class AudioFeature : public Feature
{
	__DeclareSingleton(AudioFeature)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;


private:
	AudioFeature();
	~AudioFeature();
};


#endif