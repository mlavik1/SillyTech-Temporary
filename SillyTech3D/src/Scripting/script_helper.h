#ifndef SCRIPTHELPER_H
#define SCRIPTHELPER_H

#include "debug.h"
#include "luabind/luabind.hpp"
#include "lua_script_component.h"
#include "camera_component.h"
#include "light_component.h"
#include "shader_program.h"
#include "audio_component.h"
#include "physics_component.h"
#include "game_server.h"


class Actor;

class ScriptHelper
{
public:
	
	static void PrintText(const char* arg_text);

	static void LogInfo(const char* arg_text);
	static void LogWarning(const char* arg_text);
	static void LogError(const char* arg_text);

	static Actor *GetActorByName(const char * arg_name);

	static Actor *GetActor();

	static void SetCurrentActor(Actor *arg_actor);

	static Actor *CreateActorFromModel(const char* arg_name, const char *arg_model);

	static void CreateReplicatedActor(const char* arg_name);
	static void CreateReplicatedActorFromModel(const char* arg_name, const char *arg_model);
	static void ServerCall(int arg_serverid, const char* arg_call);
	static void MulticastCall(const char* arg_call);

	static LuaScriptComponent *NewLuaScriptComponent();
	static LightComponent *NewLightComponent();
	static CameraComponent *NewCameraComponent();
	static PhysicsComponent *NewPhysicsComponent();
	static Actor *NewActor();
	static Actor *CreateActor(const char* arg_name);
	static AudioComponent *NewAudioComponent(const char* arg_file);

	static void RecompileShaders();
	static void RecompileScripts();
	static void PrintTimeLog();

	static ShaderProgram *GetPostProcessProgram();

private:
	static Actor *mCurrentActor;

};

#endif