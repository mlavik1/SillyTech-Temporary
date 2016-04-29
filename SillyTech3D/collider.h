#ifndef COLLIDER_H
#define COLLIDER_H

#include <PxPhysicsAPI.h>

class PhysicsComponent;

class Collider
{
public:
	Collider();
	~Collider();

public:
	void						SetParent(PhysicsComponent *arg_comp);
	physx::PxShape*				GetShape();
	virtual physx::PxGeometry	GetGeometry();

private:
	physx::PxShape*		mShape;
	PhysicsComponent*	mPhysicsComponent;
};

#endif