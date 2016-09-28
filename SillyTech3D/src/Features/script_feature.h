#ifndef SCRIPTFEATURE_H
#define SCRIPTFEATURE_H

#include "feature.h"
#include "singleton.h"

class ScriptFeature : public Feature
{
	__DeclareSingleton(ScriptFeature)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

private:
	ScriptFeature();
	~ScriptFeature();


};


#endif