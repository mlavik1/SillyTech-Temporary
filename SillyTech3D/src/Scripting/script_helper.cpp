#include "script_helper.h"
#include "actor_manager.h"
#include "actor.h"
#include <memory>
#include "actor_factory.h"
#include "shader_res.h"
#include "material_res.h"
#include "resource_manager.h"
#include "graphics_feature.h"
#include "lua_script_manager.h"
#include "physics_component.h"
#include "networking_feature.h"
#include "replication_manager.h"
#include <sstream>
#include "editor_gui.h"


Actor *ScriptHelper::mCurrentActor = 0;

void ScriptHelper::PrintText(const char* arg_text)
{
	LOG_INFO() << "Lua script: " << arg_text;
};

void ScriptHelper::LogInfo(const char* arg_text)
{
	LOG_INFO() << arg_text;
}

void ScriptHelper::LogWarning(const char* arg_text)
{
	LOG_WARNING() << arg_text;
}

void ScriptHelper::LogError(const char* arg_text)
{
	LOG_ERROR() << arg_text;
}

Actor *ScriptHelper::GetActorByName(const char * arg_name)
{
	std::vector<actor_ptr>::iterator i;
	std::vector<actor_ptr> tmpActors = ActorManager::Instance()->GetActors();

	for (i = tmpActors.begin(); i != tmpActors.end(); i++)
	{
		if (!strcmp((*i)->GetName().c_str(), arg_name))
		{
			return (*i).get();
		}
	}
	return 0;
}

Actor *ScriptHelper::GetActor()
{
	return mCurrentActor;
}


void ScriptHelper::SetCurrentActor(Actor *arg_actor)
{
	mCurrentActor = arg_actor;
}

Actor *ScriptHelper::CreateActorFromModel(const char* arg_name, const char *arg_model)
{
	Actor *actor = ActorFactory::CreateFromModel(arg_model);
	actor->SetName(arg_name);
	ActorManager::Instance()->AttachActor(actor);

	EditorGUI::RefreshSceneHierarchy();

	return actor;
}

void ScriptHelper::CreateReplicatedActor(const char * arg_name)
{
	if (NetworkingFeature::Instance()->IsServer())
	{
		Actor* actor = CreateActor(arg_name);
		repid_t repID = ReplicationManager::Instance()->SetReplicate(actor, true);
		std::ostringstream oss;
		oss << "MulticastCall(\"CreateActor('" << arg_name << "'):SetReplicate(" << repID <<")\")";
		MulticastCall(oss.str().c_str());
		//LuaScriptManager::Instance()->ExectureLine(oss.str().c_str());
		EditorGUI::RefreshSceneHierarchy();
	}
	else
	{
		std::string strCall = std::string("ServerCall(\"CreateReplicatedActor('") + std::string(arg_name) + std::string("')\")");
		LuaScriptManager::Instance()->ExectureLine(strCall.c_str());
	}
}

void ScriptHelper::CreateReplicatedActorFromModel(const char * arg_name, const char * arg_model)
{
	if (NetworkingFeature::Instance()->IsServer())
	{
		Actor* actor = ActorFactory::CreateFromModel(arg_model);
		actor->SetName(arg_name);
		repid_t repID = ReplicationManager::Instance()->SetReplicate(actor, true);
		std::ostringstream oss;
		oss << "MulticastCall(\"CreateActorFromModel('" << arg_name << "', '" << arg_model << "'):SetReplicate(" << repID << ")\")";
		MulticastCall(oss.str().c_str());
		//LuaScriptManager::Instance()->ExectureLine(oss.str().c_str());
		EditorGUI::RefreshSceneHierarchy();
	}
	else
	{
		std::string strCall = std::string("ServerCall(\"CreateReplicatedActorFromModel('") + std::string(arg_name) + std::string("', '") + std::string(arg_model) + std::string("')\")");
		LuaScriptManager::Instance()->ExectureLine(strCall.c_str());
	}
}

void ScriptHelper::ServerCall(const char* arg_call)
{
	if (NetworkingFeature::Instance()->IsServer())
	{
		LuaScriptManager::Instance()->ExectureLine(arg_call);
	}
	else
	{
		// TODO: send message to server
	}
}

void ScriptHelper::MulticastCall(const char* arg_call)
{
	if (NetworkingFeature::Instance()->IsServer())
	{
		//LuaScriptManager::Instance()->ExectureLine(arg_call);
		NetMessage netMessage(NetMessageType::LuaCall, strlen(arg_call) + 1, arg_call);
		NetworkingFeature::Instance()->AddOutgoingMessage(netMessage);
	}
	else
	{
		LuaScriptManager::Instance()->ExectureLine(arg_call);
	}
}

LuaScriptComponent *ScriptHelper::NewLuaScriptComponent()
{
	LuaScriptComponent *sc = new LuaScriptComponent();
	return sc;
}

LightComponent *ScriptHelper::NewLightComponent()
{
	LightComponent *lc = new LightComponent();
	return lc;
}

CameraComponent *ScriptHelper::NewCameraComponent()
{
	CameraComponent *cc = new CameraComponent();
	return cc;
}

PhysicsComponent *ScriptHelper::NewPhysicsComponent()
{
	PhysicsComponent *pc = new PhysicsComponent();
	return pc;
}

Actor *ScriptHelper::NewActor()
{
	Actor *actor = new Actor();
	ActorManager::Instance()->AttachActor(actor);
	return actor;
}

Actor *ScriptHelper::CreateActor(const char* arg_name)
{
	Actor *actor = new Actor();
	actor->SetName(arg_name);
	ActorManager::Instance()->AttachActor(actor);

	EditorGUI::RefreshSceneHierarchy();

	return actor;
}

AudioComponent *ScriptHelper::NewAudioComponent(const char* arg_file)
{
	AudioComponent *ac = new AudioComponent(arg_file);
	return ac;
}

void ScriptHelper::RecompileShaders()
{
	std::map<std::string, ShaderRes*> shaders = ResourceManager<ShaderRes>::Instance()->GetResources();
	for (auto pair : shaders)
	{
		ShaderRes *res = pair.second;
		if (res)
			res->Reload();
	}

	std::map<std::string, MaterialRes*> materials = ResourceManager<MaterialRes>::Instance()->GetResources();
	for (auto pair : materials)
	{
		pair.second->GetMaterial()->CreateShaderProgram();
	}
}

void ScriptHelper::RecompileScripts()
{
	LuaScriptManager::Instance()->RecompileScripts();
}

ShaderProgram *ScriptHelper::GetPostProcessProgram()
{
	return GraphicsFeature::Instance()->GetGraphicsSystem()->GetPostProcessProgram();
}

void ScriptHelper::PrintTimeLog()
{
	GameServer::Instance()->PrintTimeLog();
}

