#ifndef PHYSICSFEATURE_H
#define PHYSICSFEATURE_H

#include "feature.h"
#include "singleton.h"

class PhysicsFeature : public Feature
{
	__DeclareSingleton(PhysicsFeature)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;


private:
	PhysicsFeature();
	~PhysicsFeature();
};


#endif