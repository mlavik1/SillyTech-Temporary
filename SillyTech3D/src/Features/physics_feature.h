#ifndef PHYSICSFEATURE_H
#define PHYSICSFEATURE_H

#include "feature.h"
#include "singleton.h"

class PhysicsFeature : public Feature
{
	__DeclareSingleton(PhysicsFeature)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;


private:
	PhysicsFeature();
	~PhysicsFeature();
};


#endif