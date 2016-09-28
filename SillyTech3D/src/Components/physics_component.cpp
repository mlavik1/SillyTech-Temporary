#include "physics_component.h"

#include "debug.h"
#include "collider.h"
#include "st_assert.h"
#include "physics_manager.h"
#include "actor.h"
#include <glm.hpp>
#include "mesh_render_component.h"

PhysicsComponent::PhysicsComponent() : Component()
{
	
}

PhysicsComponent::~PhysicsComponent()
{

}


void PhysicsComponent::OnFrame()
{
	Component::OnFrame();
	
	physx::PxVec3 pose = mActor->getGlobalPose().p;
	GetParent()->GetTransform().SetGlobalPosition(glm::vec3(pose.x, pose.y, pose.z));

	//LOG_INFO() << pos.x << ", " << pos.y << ", " << pos.z;
}

void PhysicsComponent::OnStart()
{
	Component::OnStart();

	MeshRenderComponent *meshComp = mParent->GetComponentByType<MeshRenderComponent>(true);
	if (meshComp)
	{
		// TODO: use modelview?  OR SCALE LATER!!
		glm::vec3 bounds = meshComp->GetBoundingBox()->GetBounds()*GetParent()->GetTransform().GetGlobalScale();
		physx::PxBoxGeometry geo = physx::PxBoxGeometry(bounds.x, bounds.y, bounds.z);
		physx::PxShape *shape = mActor->createShape(geo, *mMaterial);
		//shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
		//shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	}
}

void PhysicsComponent::OnStop()
{
	Component::OnStop();
}

void PhysicsComponent::OnActivate()
{
	Component::OnActivate();

	mMaterial = PhysicsManager::Instance()->GetPhysics()->createMaterial(0.5, 0.5, 0.5);
	physx::PxTransform pos(physx::PxVec3(0.0f, 10.0f, 0.0f));
	physx::PxBoxGeometry geo(physx::PxVec3(0.5f, 0.5f, 0.5f));
	MeshRenderComponent *meshComp = mParent->GetComponentByType<MeshRenderComponent>(true);
	if (meshComp)
	{
		// TODO: use modelview?  OR SCALE LATER!!
		glm::vec3 bounds = meshComp->GetBoundingBox()->GetBounds()*GetParent()->GetTransform().GetGlobalScale();
		geo = physx::PxBoxGeometry(bounds.x, bounds.y, bounds.z);
		int a = 1;
	}

	//mActor = physx::PxCreateDynamic(*PhysicsManager::Instance()->GetPhysics(), pos, geo, *mMaterial, 100.0f);
	mActor = PhysicsManager::Instance()->GetPhysics()->createRigidDynamic(pos);
	//physx::PxShape *shape = mActor->createShape(geo, *mMaterial);
	//shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	//shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	//shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	
	glm::vec3 pose = GetParent()->GetTransform().GetGlobalPosition();
	physx::PxTransform trans(physx::PxVec3(pose.x, pose.y, pose.z));
	mActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);
	mActor->setGlobalPose(trans);

	PhysicsManager::Instance()->AttachPhysicsComponent(this);
}

void PhysicsComponent::OnDeactivate()
{
	Component::OnDeactivate();

	PhysicsManager::Instance()->DetachPhysicsComponent(this);
}




void PhysicsComponent::SetCollider(Collider *arg_collider)
{
	__AssertComment(mCollider != 0, "Trying to attach a collider that is null.");

	mCollider = arg_collider;
	mCollider->SetParent(this);
}

physx::PxActor *PhysicsComponent::GetActor()
{
	return mActor;
}

void PhysicsComponent::SetMass(float arg_mass)
{
	mActor->setMass(arg_mass);
}

float PhysicsComponent::GetMass()
{
	return mActor->getMass();
}

void PhysicsComponent::SetKinematic(bool arg_kinematic)
{
	//mActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, arg_kinematic);
	mActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, arg_kinematic); // TEMP!!!!!!!

}