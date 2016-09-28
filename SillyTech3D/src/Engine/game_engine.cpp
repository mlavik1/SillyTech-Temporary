#include "game_engine.h"

#include "game_feature.h"
#include "script_feature.h"
#include "actor_manager.h"
#include "manager.h"
#include "lua_script_res.h"
#include "actor_factory.h"
#include "mesh_res.h"
#include "input_feature.h"
#include "st_assert.h"
#include "material_res.h"
#include "texture_res.h"
#include "graphics_feature.h"
#include "mesh_render_manager.h"
#include "shader_res.h"
#include "input_feature.h"
#include "input_manager.h"
#include "camera_manager.h"
#include "time_manager.h"
#include "audio_feature.h"
#include "audio_manager.h"
#include "audio_res.h"
#include "physics_feature.h"
#include "physics_manager.h"
#include "gui_manager.h"
#include "networking_feature.h"
#include "replication_manager.h"

__ImplementSingleton(GameEngine)

GameEngine::GameEngine()
{
	__ConstructSingleton(GameEngine)

	running = false;
	paused = false;
	initialised = false;

		if (_instance != 0)
			LOG_INFO() << "Created GameEngine";
}
GameEngine::~GameEngine()
{
	__DestructSingleton(GameEngine);

	
}

void GameEngine::Initialise()
{
	gameServer = GameServer::Create();

	createFeatures();

	initialised = true;
}

void GameEngine::Start()
{
	__AssertComment(initialised == true, "Called GameEngine::Start() before GameEngine::Initialise()");

	running = true;

	gameServer->Start();

	while (running)
	{
		gameServer->Update();

		float delay = (1000 / 70) - (SDL_GetTicks() - time_ms);

		if(delay < 1000)
			SDL_Delay(delay);
		time_ms = SDL_GetTicks();
	}

}

void GameEngine::createFeatures()
{
	__AssertComment(gameServer != 0, "GameEngine::createFeatures() cannotexecute if gameServer is NULL");

	ResourceManager<MeshRes>::Create();
	ResourceManager<LuaScriptRes>::Create();
	ResourceManager<MaterialRes>::Create();
	ResourceManager<TextureRes>::Create();
	ResourceManager<ShaderRes>::Create();
	ResourceManager<AudioRes>::Create();


	ScriptFeature *scriptFeature = ScriptFeature::Create();
	LuaScriptManager *luaMan = LuaScriptManager::Create();
	scriptFeature->AttachManager(luaMan);
	gameServer->AttachFeature(scriptFeature);

	AudioFeature *audioFeature = AudioFeature::Create();
	AudioManager *audioManager = AudioManager::Create();
	audioFeature->AttachManager(audioManager);
	gameServer->AttachFeature(audioFeature);

	GameFeature *gameFeature = GameFeature::Create();
	ActorManager *actorManager = ActorManager::Create();
	TimeManager *timeManager = TimeManager::Create();
	
	gameFeature->AttachManager(timeManager);
	gameFeature->AttachManager(actorManager);
	gameServer->AttachFeature(gameFeature);	

	GraphicsFeature *graphicsFeature = GraphicsFeature::Create();
	MeshRenderManager *meshRenderManager = MeshRenderManager::Create();
	CameraManager *cameraManager = CameraManager::Create();
	GUIManager *guiManager = GUIManager::Create();
	gameServer->AttachFeature(graphicsFeature);
	graphicsFeature->AttachManager(meshRenderManager);	
	graphicsFeature->AttachManager(guiManager);
	graphicsFeature->AttachManager(cameraManager);

	InputFeature *inputFeature = InputFeature::Create();
	InputManager *inputManager = InputManager::Create();
	inputFeature->AttachManager(inputManager);
	gameServer->AttachFeature(inputFeature);

	PhysicsFeature *physicsFeature = PhysicsFeature::Create();
	PhysicsManager *physicsManager = PhysicsManager::Create();
	physicsFeature->AttachManager(physicsManager);
	gameServer->AttachFeature(physicsFeature);
	
	NetworkingFeature *networkingFeature = NetworkingFeature::Create();
	ReplicationManager *ReplicationManager = ReplicationManager::Create();
	networkingFeature->AttachManager(ReplicationManager);
	gameServer->AttachFeature(networkingFeature);
	

}

