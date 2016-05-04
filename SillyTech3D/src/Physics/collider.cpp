#include "collider.h"

#include "physics_component.h"

Collider::Collider()
{
	mShape = 0;
	mPhysicsComponent = 0;
}


Collider::~Collider()
{

}

physx::PxShape *Collider::GetShape()
{
	return mShape;
}

physx::PxGeometry Collider::GetGeometry()
{
	// IN SUBLCASS: create and return a physx-geometry
	// Also do scaling, if neccessary

	return physx::PxBoxGeometry(0.5f,0.5f,0.5f);
}

void Collider::SetParent(PhysicsComponent *arg_comp)
{
	mPhysicsComponent = arg_comp;
}