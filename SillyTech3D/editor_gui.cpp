#include "editor_gui.h"

#include "input_manager.h"
#include "graphics_feature.h"
#include "viewport.h"
#include "script_helper.h"
#include "mesh_render_manager.h"
#include "physics_component.h"
#include "component.h"
#include "actor_manager.h"
#include "lua_script_manager.h"
#include "camera_component.h"
#include "time_manager.h"
#include "light_component.h"


EditorGUI *EditorGUI::editorGUI = 0;

EditorGUI::EditorGUI()
{
	editorGUI = this;
}
EditorGUI::~EditorGUI()
{

}


void EditorGUI::Initialise()
{
	// Initialize AntTweakBar
	TwInit(TW_OPENGL, NULL);

	// Tell the window size to AntTweakBar
	TwWindowSize(GraphicsFeature::Instance()->GetDisplay()->GetScreenWidth(), GraphicsFeature::Instance()->GetDisplay()->GetScreenHeight());

	mEditorBar = TwNewBar("Editor/Engine");
	//TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with SDL and OpenGL.\nPress [Space] to toggle fullscreen.' "); // Message added to the help bar.
	
	TwAddVarRO(mEditorBar, "Draw calls: ", TW_TYPE_UINT32, &MeshRenderManager::Instance()->mDrawCalls, "");
	TwAddVarRO(mEditorBar, "Skipped: ", TW_TYPE_UINT32, &MeshRenderManager::Instance()->mDrawCallsSkipped, "");
	
	TwAddVarCB(mEditorBar, "Screen width", TW_TYPE_INT32, callbaclSceenWidthChanged, callbackGetScreenWidth, 0, "");
	TwAddVarCB(mEditorBar, "Screen height", TW_TYPE_INT32, callbaclSceenHeightChanged, callbackGetScreenHeight, 0, "");
	TwAddButton(mEditorBar, "Fullscreen", callbackSetFullscreen, NULL, "");

	TwAddButton(mEditorBar, "Recompile shaders", callbackRecompileShaders, NULL, " label='Recompile shaders' ");
	TwAddButton(mEditorBar, "Recompile scripts", callbackRecompileScripts, NULL, " label='Recompile scripts' ");
	TwAddButton(mEditorBar, "Print timelog", callbackPrintTimeLog, NULL, "");
	TwAddButton(mEditorBar, "Wireframe", callbackSetWireframe, NULL, "");
	TwAddButton(mEditorBar, "Pause", callbackSetPaused, NULL, "");

	

	//mScriptTerminalyBar = TwNewBar("Script Terminal");
	//TwAddVarRW(mScriptTerminalyBar, " Script: ", TW_TYPE_STDSTRING, &mScript, "");
	//TwAddButton(mScriptTerminalyBar, "Execute", callbackExecuteScript, NULL, "");

	RefreshSceneHierarchyBar();

}

void EditorGUI::Update()
{
	if (mSelectedActor)
	{
		glm::quat q = mSelectedActor->GetTransform().mRotationQuaternion;
		rotQuat[0] = q.x;
		rotQuat[1] = q.y;
		rotQuat[2] = q.z;
		rotQuat[3] = q.w;
	}
}


void EditorGUI::SetSelectedActor(Actor *arg_actor)
{
	mSelectedActor = arg_actor;

	RefreshActorInspector();
	//q = mSelectedActor->GetTransform().mRotationQuaternion;
}

void EditorGUI::RefreshSceneHierarchyBar()
{
	if(!mSceneHierarchyBar)
		mSceneHierarchyBar = TwNewBar("SceneHierarchy");
	//TwDefine(" SceneHierarchy position='200 40' "); // move bar to position (200, 40)

	for (actor_ptr actor : ActorManager::Instance()->GetActors())
	{
		if (!actor.get()->GetParent())
		{
			TwAddButton(mSceneHierarchyBar, actor.get()->GetName().c_str(), callbackActorChanged, actor.get(), "");
		}
	}

}

void EditorGUI::RefreshActorInspector()
{
	if (!mSelectedActor)
		return;
	if (!mActorInspectorBar)
		mActorInspectorBar = TwNewBar("ActorInspector");
	else
		TwRemoveAllVars(mActorInspectorBar);

	TwSetTopBar(mActorInspectorBar);
	
	//TwDefine("ActorInspector visible=true "); 
	TwAddButton(mActorInspectorBar, mSelectedActor->GetName().c_str(), NULL, NULL,"");

	TwAddVarRW(mActorInspectorBar, "Rotation", TW_TYPE_QUAT4F, &mSelectedActor->GetTransform().mRotationQuaternion, " group='Transform' ");
	TwAddVarRW(mActorInspectorBar, "PosX", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mPosition.x, " group='Transform' ");
	TwAddVarRW(mActorInspectorBar, "PosY", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mPosition.y, " group='Transform' ");
	TwAddVarRW(mActorInspectorBar, "PosZ", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mPosition.z, " group='Transform' ");

	TwAddVarRW(mActorInspectorBar, "ScaleX", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mScale.x, " group='Transform' ");
	TwAddVarRW(mActorInspectorBar, "ScaleY", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mScale.y, " group='Transform' ");
	TwAddVarRW(mActorInspectorBar, "ScaleZ", TW_TYPE_FLOAT, &mSelectedActor->GetTransform().mScale.z, " group='Transform' ");

	
	for (Actor *child : mSelectedActor->GetChildren())
	{
		const char* childName = child->GetName().c_str();
		TwAddButton(mActorInspectorBar, childName == "" ? "child" : childName, callbackActorChanged, child, " group='Children' ");
	}

	PhysicsComponent *physicsComponent = mSelectedActor->GetComponentByType<PhysicsComponent>();
	if (physicsComponent)
	{
		//TwAddSeparator(mActorInspectorBar, "Physics", " group='Physics' ");
		// ......
		TwAddButton(mActorInspectorBar, "Delete", callbackRemoveComponent, physicsComponent, " group='Physics' ");

	}

	CameraComponent *cameraComponent = mSelectedActor->GetComponentByType<CameraComponent>();
	if (cameraComponent)
	{
		//TwAddSeparator(mActorInspectorBar, "Camera", " group='Camera' ");
		// ......
		TwAddButton(mActorInspectorBar, "Delete", callbackRemoveComponent, cameraComponent, " group='Camera' ");

	}

	LightComponent *lightComponent = mSelectedActor->GetComponentByType<LightComponent>();
	if (lightComponent)
	{
		//TwAddSeparator(mActorInspectorBar, "Camera", " group='Camera' ");
		// ......
		TwAddButton(mActorInspectorBar, "Delete", callbackRemoveComponent, lightComponent, " group='Light' ");
		TwAddVarRW(mActorInspectorBar, "Diffuse colour", TW_TYPE_COLOR3F, &lightComponent->mDiffuseColour, " group='Light' colormode=rgb ");
		TwAddVarRW(mActorInspectorBar, "Specular colour", TW_TYPE_COLOR3F, &lightComponent->mSpecularColour, " group='Light' colormode=rgb ");
		TwAddVarRW(mActorInspectorBar, "Ambient colour", TW_TYPE_COLOR3F, &lightComponent->mAmbientColour, " group='Light' colormode=rgb ");
	}

	MeshRenderComponent *meshRenderComponent = mSelectedActor->GetComponentByType<MeshRenderComponent>();
	if (meshRenderComponent)
	{
		//TwAddSeparator(mActorInspectorBar, "Camera", " group='Camera' ");
		// ......
		TwAddButton(mActorInspectorBar, "Delete", callbackRemoveComponent, meshRenderComponent, " group='Mesh' ");

		TwAddVarRW(mActorInspectorBar, "Diffuse colour", TW_TYPE_COLOR3F, &meshRenderComponent->GetMaterial()->mColour, " group='Material' colormode=rgb ");
	}
}




/************* Callbacks *************/


void TW_CALL EditorGUI::callbaclSceenWidthChanged(const void *value, void *clientData)
{
	int aa = (const int)value;
	int aa1 = (const int)&value;
	GraphicsFeature::Instance()->GetDisplay()->SetSize(*(const int*)value, GraphicsFeature::Instance()->GetDisplay()->GetScreenHeight());
	//myVariable = *(const MyVariableType *)value;  // for instance
}

void TW_CALL EditorGUI::callbaclSceenHeightChanged(const void *value, void *clientData)
{
	GraphicsFeature::Instance()->GetDisplay()->SetSize(GraphicsFeature::Instance()->GetDisplay()->GetScreenWidth(), *(const int*)value);
	//myVariable = *(const MyVariableType *)value;  // for instance
}

void TW_CALL EditorGUI::callbackGetScreenWidth(void *value, void *clientData)
{
	*static_cast<int *>(value) = GraphicsFeature::Instance()->GetDisplay()->GetScreenWidth();
}

void TW_CALL EditorGUI::callbackGetScreenHeight(void *value, void *clientData)
{
	*static_cast<int *>(value) = GraphicsFeature::Instance()->GetDisplay()->GetScreenHeight();
}

void TW_CALL EditorGUI::callbackRecompileShaders(void *clientData)
{
	ScriptHelper::RecompileShaders();
}

void TW_CALL EditorGUI::callbackRecompileScripts(void *clientData)
{
	ScriptHelper::RecompileScripts();
}

void TW_CALL EditorGUI::callbackPrintTimeLog(void *clientData)
{
	ScriptHelper::PrintTimeLog();
}

void TW_CALL EditorGUI::callbackActorChanged(void *clientData)
{
	editorGUI->SetSelectedActor((Actor*)clientData);
}

void TW_CALL EditorGUI::callbackSetFullscreen(void *clientData)
{
	GraphicsFeature::Instance()->GetDisplay()->SetFullscreen(!GraphicsFeature::Instance()->GetDisplay()->IsFullscreen());
}



void TW_CALL EditorGUI::callbackSetWireframe(void *clientData)
{
	for (actor_ptr actor : ActorManager::Instance()->GetActors())
	{
		MeshRenderComponent *renderComp = actor.get()->GetComponentByType<MeshRenderComponent>(true);
		if (renderComp)
		{
			Material *mat = renderComp->GetMaterial();
			mat->GetShaderProgram().SetUniform("wireframe", 1);
		}
	}
}

void TW_CALL EditorGUI::callbackExecuteScript(void *clientData)
{
	LuaScriptManager::Instance()->RunScriptOnce(editorGUI->mScript.c_str());
}


void TW_CALL EditorGUI::callbackRemoveComponent(void *clientData)
{
	editorGUI->mSelectedActor->DetachComponent((Component*)clientData);
	editorGUI->RefreshActorInspector();
}

void TW_CALL EditorGUI::callbackSetPaused(void *clientData)
{
	TimeManager::Instance()->SetPaused(!TimeManager::Instance()->IsPaused());
}