#ifndef INPUTFEATURE_H
#define INPUTFEATURE_H

#include "feature.h"
#include "singleton.h"


class InputFeature : public Feature
{
	__DeclareSingleton(InputFeature)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

private:
	InputFeature();
	~InputFeature();

private:
	//std::map<std::string, int> keysPressed;
};


#endif