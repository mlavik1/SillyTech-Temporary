#include "gui_manager.h"


__ImplementSingleton(GUIManager)

GUIManager::GUIManager()
{
	__ConstructSingleton(GUIManager);

	mEditorGUI = new EditorGUI();

}


GUIManager::~GUIManager()
{
	__DestructSingleton(GUIManager)
}



void GUIManager::OnBeginFrame()
{
	Manager::OnBeginFrame();

}

void GUIManager::OnEndFrame()
{
	Manager::OnEndFrame();

	mEditorGUI->Update();
	TwDraw();
}

void GUIManager::OnFrame()
{
	Manager::OnFrame();
}

void GUIManager::OnStart()
{
	Manager::OnStart();

	mEditorGUI->Initialise();
}

void GUIManager::OnStop()
{
	Manager::OnStop();

}

void GUIManager::OnActivate()
{
	Manager::OnActivate();

}

void GUIManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

void GUIManager::HandleInput(SDL_Event &arg_event)
{
	

	TwEventSDL(&arg_event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
}

