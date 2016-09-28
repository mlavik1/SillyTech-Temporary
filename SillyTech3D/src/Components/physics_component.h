#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"
#include <PxPhysicsAPI.h>

class Collider; //fwd-decl

class PhysicsComponent : public Component
{
public:
	virtual void OnFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;

public:
	PhysicsComponent();
	~PhysicsComponent();

public:
	void					SetCollider(Collider *arg_collider);
	physx::PxActor			*GetActor();
	void					SetMass(float arg_mass);
	float					GetMass();
	void					SetKinematic(bool arg_kinematic);

private:
	physx::PxRigidDynamic	*mActor;
	physx::PxMaterial		*mMaterial;
	Collider				*mCollider;
	


};


#endif