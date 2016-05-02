#ifndef SCRIPTFEATURE_H
#define SCRIPTFEATURE_H

#include "feature.h"
#include "singleton.h"

class ScriptFeature : public Feature
{
	__DeclareSingleton(ScriptFeature)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

private:
	ScriptFeature();
	~ScriptFeature();


};


#endif