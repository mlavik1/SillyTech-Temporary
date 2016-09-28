#include "physics_manager.h"

#include "physics_component.h"
#include "time_manager.h"
#include <sstream>
#include "st_assert.h"

__ImplementSingleton(PhysicsManager)

PhysicsManager::PhysicsManager()
{
	__ConstructSingleton(PhysicsManager)
		mPhysics = 0;
	mFoundation = 0;
	mScene = 0;
}


PhysicsManager::~PhysicsManager()
{
	__DestructSingleton(PhysicsManager)
}


void PhysicsManager::OnFrame()
{
	Manager::OnFrame();

	/***   NEIII   Gjer dette ein annan plass ----test **/
	for (PhysicsComponent *pc : mUninitialised)
		pc->OnStart();
	mUninitialised.clear();

	if (mScene)
	{
		physx::PxReal timestep = TimeManager::Instance()->GetDeltaTime();
		if (timestep > 0.0f && timestep < 2.0f) // TODO: Remove this, and instead make sure the TimeManager does not jump at first frame
		{
			mScene->simulate(timestep);
			mScene->fetchResults(true);
		}
		
		
		//physx::PxVec3 pos = gBox->getGlobalPose().p;
		//LOG_INFO() << pos.x << ", " << pos.y << ", " << pos.z;
	}
	else
		LOG_ERROR() << "PhysX scene is NULL";

	std::unordered_map<std::string, PhysicsComponent*>::iterator i;

	for (i = mPhysicsComponents.begin(); i != mPhysicsComponents.end(); i++)
	{
		if(i->second)
			i->second->OnFrame();
	}
		

}

void PhysicsManager::OnStart()
{
	Manager::OnStart();

	std::unordered_map<std::string, PhysicsComponent*>::iterator i;


	for (i = mPhysicsComponents.begin(); i != mPhysicsComponents.end(); i++)
	{
		if (i->second)
			i->second->OnStart();
	}

	
}

void PhysicsManager::OnStop()
{
	Manager::OnStop();

	std::unordered_map<std::string, PhysicsComponent*>::iterator i;

	for (i = mPhysicsComponents.begin(); i != mPhysicsComponents.end(); i++)
	{
		if (i->second)
			i->second->OnStop();
	}

}

void PhysicsManager::OnActivate()
{
	Manager::OnActivate();


	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
	mPhysics = 0;
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale());
	if (!mPhysics)
		LOG_ERROR() << "Error creating PhysX device";
	else
		LOG_INFO() << "Initialised PhysX, version: " << PX_PHYSICS_VERSION_MAJOR << "." << PX_PHYSICS_VERSION_MINOR;

	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
	//sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = contactReportFilterShader;
	//sceneDesc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	sceneDesc.simulationEventCallback = this;
	sceneDesc.flags |= physx::PxSceneFlag::eENABLE_CCD;
	
	mScene = mPhysics->createScene(sceneDesc);

	mScene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0);	//Global visualization scale which gets multiplied with the individual scales
	mScene->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);	//Enable visualization of actor's shape
	mScene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 1.0f);	//Enable visualization of actor's axis





	
	/*
																							
	using namespace physx;

	PxMaterial* material = mPhysics->createMaterial(10000.5f, 0.5f, 10000.5f);

	PxTransform planePos = PxTransform(PxVec3(0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));	//Position and orientation(transform) for plane actor  
	PxRigidStatic* plane = mPhysics->createRigidStatic(planePos);								//Creating rigid static actor	
	plane->createShape(PxPlaneGeometry(), *material);						//Defining geometry for plane actor
	mScene->addActor(*plane);												//Adding plane actor to PhysX scene


	
	{
		//Creating a dynamic sphere (It will fall on to trigger shape which will invoke 'onTrigger()' function)
		PxTransform			spherePos(PxVec3(-10.0f, 10.0f, 0.0f));
		PxSphereGeometry	sphereGeometry(2);
		PxRigidDynamic*		sphere = PxCreateDynamic(*mPhysics, spherePos, sphereGeometry, *material, 1.0f);
		mScene->addActor(*sphere);

		//Creating a trigger shape(trigger shape can't collide against any abject, 
		//thus it is made static otherwise it will fall under the effect of gravity) 
		PxTransform		boxPos(PxVec3(-10.0f, 2.10f, 0.0f));
		PxShape*		boxShape = mPhysics->createShape(PxBoxGeometry(PxVec3(3.0f, 2.0f, 3.0f)), *material);

		boxShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);	//flagged to disable shape collision
		boxShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);		//flagged as trigger shape

		PxRigidStatic*	gBox = PxCreateStatic(*mPhysics, boxPos, *boxShape);
		mScene->addActor(*gBox);
	}



	{
		//Creating a rigid dynamic sphere (It will fall on to the other rigid dynamic body which will invoke 'onContact()' function)																			 
		PxTransform			spherePos(PxVec3(10.0f, 10.0f, 0.0f));
		PxSphereGeometry	sphereGeometry(2);
		PxRigidDynamic*		sphere = PxCreateDynamic(*mPhysics, spherePos, sphereGeometry, *material, 1.0f);

		sphere->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true); //Set flag to enable CCD (Continuous Collision Detection) for the actor

		mScene->addActor(*sphere);

		//Creating a rigid dynamic box resting on static plane 																 
		PxTransform		boxPos(PxVec3(10.0f, 2.0f, 0.0f));
		PxBoxGeometry	boxGeometry(PxVec3(3.0f, 2.0f, 3.0f));
		PxRigidDynamic* box2 = PxCreateDynamic(*mPhysics, boxPos, boxGeometry, *material, 1.0f);
		mScene->addActor(*box2);
	}


	*/







	
}

void PhysicsManager::OnDeactivate()
{
	Manager::OnDeactivate();
}


physx::PxPhysics *PhysicsManager::GetPhysics()
{
	return mPhysics;
}

void PhysicsManager::AttachPhysicsComponent(PhysicsComponent *arg_comp)
{
	mPhysicsComponents[arg_comp->GetMemoryHash()] = arg_comp;

	mScene->addActor(*arg_comp->GetActor());
	mUninitialised.push_back(arg_comp);
}

void PhysicsManager::DetachPhysicsComponent(PhysicsComponent *arg_comp)
{
	mPhysicsComponents.erase(arg_comp->GetMemoryHash());

	mScene->removeActor(*arg_comp->GetActor());
}

void PhysicsManager::onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs, physx::PxU32 nbPairs)
{
	LOG_INFO() << "CONTACT!!!!!!!!!!";
}