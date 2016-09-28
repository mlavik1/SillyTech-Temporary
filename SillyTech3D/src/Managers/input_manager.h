#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <SDL.h>
#include <map>
#include <string>
#include "glm.hpp"
#include <stdint.h>

#define KEYCODE_MOUSEBUTTON_LEFT	0x0001
#define KEYCODE_MOUSEBUTTON_MIDDLE	0x0002
#define KEYCODE_MOUSEBUTTON_RIGHT	0x0004

typedef SDL_Keycode InputMapKeycode;

class InputManager : public Manager
{
	__DeclareSingleton(InputManager)


public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	bool GetKey(const char* arg_key);
	bool GetKeyDown(const char* arg_key);
	bool GetKeyUp(const char* arg_key);

	bool GetMouse(int arg_key);
	bool GetMouseDown(int arg_key);
	bool GetMouseUp(int arg_key);

	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseWheel();

	void AddInputMap(const char* arg_key, InputMapKeycode arg_value);
	SDL_Event GetEvent();

private:
	InputManager();
	~InputManager();

	SDL_Event mEvent;
	std::map<InputMapKeycode, bool> mKeyDownEvents;
	std::map<InputMapKeycode, bool> mKeyUpEvents;
	uint32_t mMouseButtonMap;
	std::map<std::string, InputMapKeycode> mInputMap;

	void addDefaultKeycodes();
	glm::vec2 mMousePosition;
	glm::vec2 mMouseWheel;
	
};

#endif
