#include <Windows.h>
#include <SDL.h>
#include <GL\glew.h>
#undef main // prevent LNK2019

#include "game_engine.h"
#include "debug.h"
#include "st_assert.h"
#include "actor_manager.h"
#include "actor_factory.h"
#include "lua_script_res.h"
#include "camera_component.h"
#include "graphics_feature.h"
#include "physics_component.h"
#include "physics_manager.h"
#include "script_helper.h"
#include <AntTweakBar.h>
#include <PxPhysicsAPI.h>
#include "shader_reader.h"

//#define _MSC_VER 1700
#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#else
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#endif

#define DEBUG_MODE

using namespace std;

int main(int argc, char **argv)
{
	/*
	int ver = _MSC_VER;
	physx::PxDefaultErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;
	physx::PxFoundation *gFoundation = 0;

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	physx::PxPhysics * gPhysics = 0;
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale());
	if (!gPhysics)
		LOG_ERROR() << "Error creating PhysX device";
	else
		LOG_INFO() << "Initialised PhysX, version: " << PX_PHYSICS_VERSION_MAJOR << "." << PX_PHYSICS_VERSION_MINOR;



	physx::PxScene * gScene = 0;
	physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 9.9f);
	sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	physx::PxMaterial *mMaterial = gPhysics->createMaterial(0.5,0.5,0.5);
	physx::PxTransform planePos = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f), physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0.0f, 0.0f, 1.0f)));
	physx::PxRigidActor *plane = gPhysics->createRigidStatic(planePos);
	physx::PxPlaneGeometry geo = physx::PxPlaneGeometry();
	physx::PxShape *shape = plane->createShape(geo, *mMaterial);
	gScene->addActor(*plane);

	physx::PxRigidDynamic *gBox;
	physx::PxTransform boxPos(physx::PxVec3(0.0f,10.0f,0.0f));
	physx::PxBoxGeometry boxGeometry(physx::PxVec3(0.5f,0.5f,0.5f));
	gBox = physx::PxCreateDynamic(*gPhysics, boxPos, boxGeometry, *mMaterial, 1.0f);
	gScene->addActor(*gBox);
	//((physx::PxRigidDynamic*)gBox)->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC,true);
	
	for (int i = 0; i <= 300; i++)
	{
		if (gScene)
		{
			physx::PxReal myTimestep = 1.0f / 60.0f;
			gScene->simulate(myTimestep);
			gScene->fetchResults(true);

			physx::PxVec3 pos = gBox->getGlobalPose().p;
			LOG_INFO() << pos.x << ", " << pos.y << ", " << pos.z;
		}
	}
	*/
	




	Debug::SetFileLogMode(DEBUG_MODE_ERROR);
	Debug::SetTerminalLogMode(DEBUG_MODE_ALL);

	LOG_INFO() << "starting from Main.cpp";
	
	__Assert(1 == 1);

	//std::string testShader = ShaderReader::GetShader("DefaultShader.vs");
	//LOG_INFO() << testShader;

	GameEngine *gs;
	gs = GameEngine::Create();
	gs->Initialise();



	/*

	// Initialize AntTweakBar
	TwInit(TW_OPENGL, NULL);

	// Tell the window size to AntTweakBar
	TwWindowSize(800, 300);

	TwBar *bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with SDL and OpenGL.\nPress [Space] to toggle fullscreen.' "); // Message added to the help bar.
	int width, height;
	// Add 'width' and 'height' to 'bar': they are read-only (RO) variables of type TW_TYPE_INT32.
	TwAddVarRO(bar, "Width", TW_TYPE_INT32, &width,
		" label='Wnd width' help='Width of the graphics window (in pixels)' ");

	TwAddVarRO(bar, "Height", TW_TYPE_INT32, &height,
		" label='Wnd height' help='Height of the graphics window (in pixels)' ");

		*/




	//Actor *ac = new Actor();
	//ac->AttachComponent(new PhysicsComponent());
	//ActorManager::Instance()->AttachActor(ac);
	//LOG_INFO() << "VAFLA";
	//ScriptHelper::GetActorByName("Tidus")->AttachComponent(new PhysicsComponent());

	GraphicsFeature::Instance()->SetPostProcessRendering(true);

	gs->Start();


	LOG_INFO() << "exiting Main.cpp";


	return 0;
}