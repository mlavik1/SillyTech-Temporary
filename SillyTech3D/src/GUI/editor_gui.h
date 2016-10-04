#ifndef EDITORGUI_H
#define EDITORGUI_H

#include "actor.h"
#include "AntTweakBar.h"
#include <glm.hpp>
#include "transform.h"
#include <string>

class EditorGUI
{
public:
	EditorGUI();
	~EditorGUI();

	void Initialise();
	void Update();
	
	void SetSelectedActor(Actor *arg_actor);
	void RefreshActorInspector();
	void RefreshSceneHierarchyBar();

private:
	static EditorGUI *editorGUI;

	Actor *mSelectedActor; // BURK DENNE til ?endre p?actor / components!
	TwBar *mEditorBar;
	TwBar *mActorInspectorBar;
	TwBar *mSceneHierarchyBar;
	TwBar *mScriptTerminalyBar;
	
	std::string mScript;

	float pos_x, pos_y, pos_z;
	float rotQuat[4];
	glm::quat *q;

	//glm::vec3 actorPos, actorScale;

	static void TW_CALL callbaclSceenWidthChanged(const void *value, void *clientData);
	static void TW_CALL callbaclSceenHeightChanged(const void *value, void *clientData);
	static void TW_CALL callbackGetScreenWidth(void *value, void *clientData);
	static void TW_CALL callbackGetScreenHeight(void *value, void *clientData);

	static void TW_CALL callbackRecompileShaders(void *clientData);
	static void TW_CALL callbackRecompileScripts(void *clientData);
	static void TW_CALL callbackPrintTimeLog(void *clientData);
	static void TW_CALL callbackSetPaused(void *clientData);

	static void TW_CALL callbackActorChanged(void *clientData);
	static void TW_CALL callbackSetFullscreen(void *clientData);
	static void TW_CALL callbackSetWireframe(void *clientData);
	static void TW_CALL callbackExecuteScript(void *clientData);

	static void TW_CALL callbackRemoveComponent(void *clientData);
	
public:
	static void RefreshSceneHierarchy();

	//static float getActorPosX() { editorGUI->actorPos = editorGUI->mSelectedActor->GetTransform().GetGlobalPosition(); return editorGUI->actorPos.x; }
	//static float getActorPosY() { editorGUI->actorPos = editorGUI->mSelectedActor->GetTransform().GetGlobalPosition(); return editorGUI->actorPos.y; }
	//static float getActorPosZ() { return editorGUI->mSelectedActor->GetTransform().GetGlobalPosition().z; }
};


#endif