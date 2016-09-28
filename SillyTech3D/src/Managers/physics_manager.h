#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <PxPhysicsAPI.h>
#include <vector>
#include <unordered_map>

class PhysicsComponent;

class PhysicsManager : public Manager, public physx::PxSimulationEventCallback
{
	__DeclareSingleton(PhysicsManager)


public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

private:
	PhysicsManager();
	~PhysicsManager();

public:
	physx::PxPhysics *GetPhysics();
	void AttachPhysicsComponent(PhysicsComponent *arg_comp);
	void DetachPhysicsComponent(PhysicsComponent *arg_comp);

private:
	physx::PxPhysics	*mPhysics;
	physx::PxFoundation *mFoundation;
	physx::PxScene		*mScene;
	//std::vector<PhysicsComponent*> mPhysicsComponents;
	std::unordered_map<std::string, PhysicsComponent*> mPhysicsComponents;
	physx::PxDefaultErrorCallback mDefaultErrorCallback;
	physx::PxDefaultAllocator mDefaultAllocatorCallback;
	void onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs, physx::PxU32 nbPairs);
	void onConstraintBreak(physx::PxConstraintInfo *constraints, physx::PxU32 count){}
	void onWake(physx::PxActor **actors, physx::PxU32 count) {}
	void onSleep(physx::PxActor **actors, physx::PxU32 count) {}
	void onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
	{
		LOG_INFO() << "ON TRIGGER";
	}

	static physx::PxFilterFlags contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags &pairFlags, const void *constBlock, physx::PxU32 constantBlockSize)
	{
		pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT
			| physx::PxPairFlag::eTRIGGER_DEFAULT
			| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS
			| physx::PxPairFlag::eCCD_LINEAR; //Set flag to enable CCD (Continuous Collision Detection) 


		return physx::PxFilterFlag::eDEFAULT;
	}

	std::vector<PhysicsComponent*> mUninitialised;
};

#endif
