#ifndef GAMEFEATURE_H
#define GAMEFEATURE_H

#include "feature.h"
#include "singleton.h"

class GameFeature : public Feature
{
	__DeclareSingleton(GameFeature)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;
	

private:
	GameFeature();
	~GameFeature();
};


#endif