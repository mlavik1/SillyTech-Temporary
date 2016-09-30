#include "lua_glue.h"
#include <luabind/iterator_policy.hpp>
#include "actor.h"
#include "transform.h"
#include "script_helper.h"
#include "input_manager.h"
#include "lua_script_component.h"
#include "viewport.h"
#include "camera_component.h"
#include "mesh_render_component.h"
#include "time_manager.h"
#include "light_component.h"
#include "material.h"
#include "mesh_render_component.h"
#include "shader_program.h"
#include "glm.hpp"
#include "audio_component.h"
#include "physics_component.h"
#include "game_server.h"
#include "networking_feature.h"
#include "replication.h"

void LuaGlue::BindAll(lua_State *luaState, Actor * arg_actor)
{

	ScriptHelper::SetCurrentActor(arg_actor);

	// helper functions:
	luabind::module(luaState)[
		luabind::def("PrintText", &ScriptHelper::PrintText),
		luabind::def("GetActorByName", &ScriptHelper::GetActorByName),
		luabind::def("CreateActorFromModel", &ScriptHelper::CreateActorFromModel),
		luabind::def("GetActor", &ScriptHelper::GetActor),
		luabind::def("RecompileShaders", &ScriptHelper::RecompileShaders),
		luabind::def("RecompileScripts", &ScriptHelper::RecompileScripts),
		luabind::def("NewLuaScriptComponent", &ScriptHelper::NewLuaScriptComponent),
		luabind::def("NewLightComponent", &ScriptHelper::NewLightComponent),
		luabind::def("NewCameraComponent", &ScriptHelper::NewCameraComponent),
		luabind::def("NewPhysicsComponent", &ScriptHelper::NewPhysicsComponent),
		luabind::def("NewAudioComponent", &ScriptHelper::NewAudioComponent),
		luabind::def("NewActor", &ScriptHelper::NewActor),
		luabind::def("GetPostProcessProgram", &ScriptHelper::GetPostProcessProgram),
		luabind::def("PrintTimeLog", &ScriptHelper::PrintTimeLog)
	];

	// glm::vec3 & vec2
	luabind::module(luaState)[
		luabind::class_<glm::vec3>("vec3")
			.def(luabind::constructor<float, float, float>())
			.def(luabind::self * float())
			.def(luabind::self + glm::vec3())
			.def(luabind::self- glm::vec3())
			.def(luabind::self * glm::vec3())
			.def_readwrite("x", &glm::vec3::x)
			.def_readwrite("y", &glm::vec3::y)
			.def_readwrite("z", &glm::vec3::z),
		luabind::class_<glm::vec2>("vec2")
			.def(luabind::constructor<float, float>())
			.def(luabind::self * float())
			.def(luabind::self + glm::vec2())
			.def(luabind::self * glm::vec2())
			.def_readwrite("x", &glm::vec2::x)
			.def_readwrite("y", &glm::vec2::y)
	];
	
	// Transform:
	luabind::module(luaState)[
		luabind::class_<Transform>("Transform")
			.def("SetPosition", &Transform::SetPosition)
			.def("GetPosition", &Transform::GetPosition)
			.def("SetScale", &Transform::SetScale)
			.def("GetScale", &Transform::GetScale)
			.def("Forward", &Transform::Forward)
			.def("Right", &Transform::Right)
			.def("Up", &Transform::Up)
			.def("PrintPosition", &Transform::PrintPosition)
			.def("Rotate", &Transform::Rotate)
			.def("SetRotation", &Transform::SetRotation)
	];
	
	// IReplicable:
	luabind::module(luaState)[
		luabind::class_<IReplicable>("IReplicable")
			.def("SetIsReplicated", &IReplicable::SetIsReplicated)
			.def("SetReplicationID", &IReplicable::SetReplicationID)
	];

	// Actor:
	luabind::module(luaState)[
		luabind::class_<Actor, IReplicable>("Actor")
			.def(luabind::constructor<>())
			.def("GetName", &Actor::GetName)
			.def("SetName", &Actor::SetName)
			.def("GetTransform", &Actor::GetTransform)
			.def("SetTransform", &Actor::SetTransform)
			.def("AttachComponent", &Actor::AttachComponent)
			.def("DetachComponent", &Actor::DetachComponent)
			.def("AddChild", &Actor::AddChild)
			.def("GetLuaScriptComponent", &Actor::GetComponentByType<LuaScriptComponent>)
			.def("GetCameraComponent", &Actor::GetComponentByType<CameraComponent>)
			.def("GetAudioComponent", &Actor::GetComponentByType<AudioComponent>)
			.def("GetMeshRenderComponent", &Actor::GetComponentByType<MeshRenderComponent>)
			.def("GetMeshRenderComponents", &Actor::GetComponentsPtrByType<MeshRenderComponent>, luabind::return_stl_iterator)
	];
	
	// NetworkingFeature:
	luabind::module(luaState)[
		luabind::def("Networking", &NetworkingFeature::Instance),
			luabind::class_<NetworkingFeature>("NetworkingFeature")
			.def("SetServer", &NetworkingFeature::SetServer)
			.def("SetClient", &NetworkingFeature::SetClient)
			.def("ConnectToServer", &NetworkingFeature::ConnectToServer)
	];

	// InputManager:
	luabind::module(luaState)[
		luabind::def("Input", &InputManager::Instance),
		luabind::class_<InputManager>("InputManager")			
			.def("GetKey", &InputManager::GetKey)
			.def("GetKeyDown", &InputManager::GetKeyDown)
			.def("GetKeyUp", &InputManager::GetKeyUp)
			.def("GetMouse", &InputManager::GetMouse)
			.def("GetMouseDown", &InputManager::GetMouseDown)
			.def("GetMouseUp", &InputManager::GetMouseUp)
			.def("GetMousePosition", &InputManager::GetMousePosition)
			.def("GetMouseWheel", &InputManager::GetMouseWheel)
	];

	// TimeManager:
	luabind::module(luaState)[
		luabind::def("Time", &TimeManager::Instance),
			luabind::class_<TimeManager>("TimeManager")
			.def("GetTime", &TimeManager::GetTime)
			.def("GetDeltaTime", &TimeManager::GetDeltaTime)
			.def("GetFramesPerSecond", &TimeManager::GetFramesPerSecond)
	];
	
	// Shader:
	luabind::module(luaState)[
		luabind::class_<ShaderProgram>("ShaderProgram")
			.def("SetInt", (void(ShaderProgram::*)(const char*,GLint)) &ShaderProgram::SetUniform)

	];
	// Material:
	luabind::module(luaState)[
		luabind::class_<Material>("Material")
		.def("GetShaderProgram", &Material::GetShaderProgram)
	];
	
	// Component:
	luabind::module(luaState)[
		luabind::class_<Component>("Component")
	];
	// ScriptComponent:
	luabind::module(luaState)[
		luabind::class_<ScriptComponent, Component>("ScriptComponent")
	];

	// LuaScriptComponent:
	luabind::module(luaState)[
		luabind::class_<LuaScriptComponent, ScriptComponent>("LuaScriptComponent")
		.def("SetScript", &LuaScriptComponent::SetScript)
	];

	// PhysicsCOmponent:
	luabind::module(luaState)[
		luabind::class_<PhysicsComponent, Component>("PhysicsComponent")
			.def("SetKinematic", &PhysicsComponent::SetKinematic)
	];

	// MeshRenderComponent:
	luabind::module(luaState)[
		luabind::class_<MeshRenderComponent, Component>("MeshRenderComponent")
			.def("GetMaterial", &MeshRenderComponent::GetMaterial)
	];

	// AudioComponent:
	luabind::module(luaState)[
		luabind::class_<AudioComponent, Component>("AudioComponent")
			.def("Play", &AudioComponent::Play)
			.def("Set3DSound", &AudioComponent::Set3DSound)
			.def("SetLooping", &AudioComponent::SetLooping)
			.def("SetMinDistance", &AudioComponent::SetMinDistance)
			.def("SetMaxDistance", &AudioComponent::SetMaxDistance)
	];

	// LightComponent:
	luabind::module(luaState)[
		luabind::class_<LightComponent, Component>("LightComponent")
			//.def(luabind::constructor<>())
			.def("SetAmbientColour", &LightComponent::SetAmbientColour)
			.def("SetDiffuseColour", &LightComponent::SetDiffuseColour)
			.def("SetSpecularColour", &LightComponent::SetSpecularColour)
			.def("GetAmbientColour", &LightComponent::GetAmbientColour)
			.def("GetDiffuseColour", &LightComponent::GetDiffuseColour)
			.def("GetSpecularColour", &LightComponent::GetSpecularColour)
	];

	// Viewport:
	luabind::module(luaState)[
		luabind::class_<Viewport>("Viewport")
			.def(luabind::constructor<float, float, float, float>())
	];
	// CameraComponent:
	luabind::module(luaState)[
		luabind::class_<CameraComponent, Component>("CameraComponent")
			.def(luabind::constructor<>())
			.def("SetViewport", &CameraComponent::SetViewport)
	];
}



void LuaGlue::LoadScript(lua_State *luaState, const char *arg_script, const char *arg_name)
{
	/* load the lua script into memory */
	luaL_loadstring(luaState, arg_script);
	
	/* create a new function environment and store it in the registry */
	lua_createtable(luaState, 0, 1);
	lua_getglobal(luaState, "print");
	lua_setfield(luaState, -2, "print");
	lua_pushvalue(luaState, -1);
	lua_setfield(luaState, LUA_REGISTRYINDEX, arg_name);
	
	//lua_getglobal(L, "my_environment"); /* push environment onto stack */
	//lua_setupvalue(L, -2, 1);           /* pop environment and assign to upvalue#1 */

	
	/* set the environment for the loaded script and execute it */
	//lua_setfenv(luaState, -2);
	lua_setupvalue(luaState, -2, 1);
	lua_call(luaState, 0, 0);

}

void LuaGlue::ExecuteScript(lua_State *luaState, const char *arg_name, const char *arg_function)
{
	/* retrieve the environment from the resgistry */
	lua_getfield(luaState, LUA_REGISTRYINDEX, arg_name);

	/* get the desired function from the environment */
	lua_getfield(luaState, -1, arg_function);

	return lua_call(luaState, 0, 0);
}
