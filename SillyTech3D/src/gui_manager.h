#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "manager.h"
#include "singleton.h"
#include "editor_gui.h"
#include "SDL.h"

class GUIComponent;

class GUIManager : public Manager
{
	__DeclareSingleton(GUIManager)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	void HandleInput(SDL_Event &arg_event);

private:
	GUIManager();
	~GUIManager();

private:
	EditorGUI *mEditorGUI;

};

#endif