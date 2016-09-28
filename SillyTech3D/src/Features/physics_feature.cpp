#include "physics_feature.h"

__ImplementSingleton(PhysicsFeature)

PhysicsFeature::PhysicsFeature()
{
	mFeatureName = "PhysicsFeature";

	__ConstructSingleton(PhysicsFeature)
}

PhysicsFeature::~PhysicsFeature()
{
	__DestructSingleton(PhysicsFeature)
}

void PhysicsFeature::OnFrame()
{
	Feature::OnFrame();
}

void PhysicsFeature::OnStart()
{
	Feature::OnStart();
}

void PhysicsFeature::OnStop()
{
	Feature::OnStop();
}

void PhysicsFeature::OnActivate()
{
	Feature::OnActivate();
}

void PhysicsFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}