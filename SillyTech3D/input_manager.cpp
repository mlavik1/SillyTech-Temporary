#include "input_manager.h"
#include <stdexcept>
#include "lua_script_manager.h"
#include "gui_manager.h"


__ImplementSingleton(InputManager)

InputManager::InputManager()
{
	__ConstructSingleton(InputManager)

		addDefaultKeycodes();
	mMousePosition = glm::vec2(0.0f,0.0f);
}


InputManager::~InputManager()
{
	__DestructSingleton(InputManager)
}


void InputManager::OnBeginFrame()
{
	Manager::OnBeginFrame();

	mKeyUpEvents.clear();
	mKeyDownEvents.clear();
	mMouseButtonMap = 0;

	mMouseWheel = glm::vec2(0.0f,0.0f);

	while (SDL_PollEvent(&mEvent))
	{
		GUIManager::Instance()->HandleInput(mEvent);


		if (mEvent.type == SDL_KEYDOWN)
			mKeyDownEvents[mEvent.key.keysym.sym] = true;
		else if (mEvent.type == SDL_KEYUP)
			mKeyUpEvents[mEvent.key.keysym.sym] = true;
		else if (mEvent.type == SDL_MOUSEMOTION)
		{
			mMousePosition = glm::vec2(mEvent.motion.x, mEvent.motion.y);
		}
		else if (mEvent.type == SDL_MOUSEWHEEL)
		{
			mMouseWheel += glm::vec2(mEvent.wheel.x, mEvent.wheel.y);
		}
		else if (mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			mMouseButtonMap |= (SDL_PRESSED << (mEvent.button.button-1));
		}
		else if (mEvent.type == SDL_MOUSEBUTTONUP)
		{
			mMouseButtonMap |= (SDL_PRESSED << (mEvent.button.button - 1)) << 16;
		}

		
	}

	

}

void InputManager::OnEndFrame()
{
	Manager::OnEndFrame();

}

void InputManager::OnFrame()
{
	Manager::OnFrame();

	// TEMP
	// ***** TODO *****
	// USE CALLBACK
	if (GetKey("q"))
		LuaScriptManager::Instance()->RunTerminalInput();
}

void InputManager::OnStart()
{
	Manager::OnStart();
}

void InputManager::OnStop()
{
	Manager::OnStop();

}

void InputManager::OnActivate()
{
	Manager::OnActivate();
		
}

void InputManager::OnDeactivate()
{
	Manager::OnDeactivate();
}





bool InputManager::GetKey(const char* arg_key)
{
	try {
		InputMapKeycode mapKeycode = mInputMap.at(arg_key);

		const Uint8 * keys = SDL_GetKeyboardState(NULL);

		return keys[SDL_GetScancodeFromKey(mapKeycode)];
	}
	catch (const std::out_of_range& oor) {
		LOG_ERROR() << "Out of Range error: " << oor.what() << ", " << "in input_manager::GetKey()";
	}
	return false;
}

bool InputManager::GetKeyDown(const char* arg_key)
{
	/*if (mEvent.type == SDL_KEYDOWN)
	{
		try {
			return mEvent.key.keysym.sym == mInputMap.at(arg_key);
		}
		catch (const std::out_of_range& oor) {
			LOG_ERROR() << "Out of Range error: " << oor.what() << ", " << "in input_manager::GetKeyDown()";
		}
	}*/
	try {
		InputMapKeycode keyCode = mInputMap.at(arg_key);
		return mKeyDownEvents.at(keyCode);
	}
	catch (const std::out_of_range& oor) {
		//LOG_ERROR() << "Out of Range error: " << oor.what() << ", " << "in input_manager::GetKeyDown()";
	}

	return false;
}

bool InputManager::GetKeyUp(const char* arg_key)
{
	/*if (mEvent.type == SDL_KEYUP)
	{
		try {
			return mEvent.key.keysym.sym == mInputMap.at(arg_key);
		}
		catch (const std::out_of_range& oor) {
			LOG_ERROR() << "Out of Range error: " << oor.what() << ", " << "in input_manager::GetKeyUp()";
		}
	}*/

	try {
		InputMapKeycode keyCode = mInputMap.at(arg_key);
		return mKeyUpEvents.at(keyCode);
	}
	catch (const std::out_of_range& oor) {
		//LOG_ERROR() << "Out of Range error: " << oor.what() << ", " << "in input_manager::GetKeyDown()";
	}

	return false;
}


void InputManager::AddInputMap(const char* arg_key, InputMapKeycode arg_value)
{
	mInputMap[arg_key] = arg_value;
}


glm::vec2 InputManager::GetMousePosition()
{
	return mMousePosition;
}

glm::vec2 InputManager::GetMouseWheel()
{
	return mMouseWheel;
}

bool InputManager::GetMouse(int arg_key)
{
	return 0;
}
bool InputManager::GetMouseDown(int arg_key)
{
	return mMouseButtonMap & (SDL_PRESSED << (arg_key - 1));
}
bool InputManager::GetMouseUp(int arg_key)
{
	return mMouseButtonMap & ((SDL_PRESSED << (arg_key - 1)) << 16);
}

SDL_Event InputManager::GetEvent()
{
	return mEvent;
}

void InputManager::addDefaultKeycodes()
{
	AddInputMap("up", SDLK_UP);
	AddInputMap("down", SDLK_DOWN);
	AddInputMap("right", SDLK_RIGHT);
	AddInputMap("left", SDLK_LEFT);

	AddInputMap("enter", SDLK_RETURN);
	AddInputMap("space", SDLK_SPACE);
	AddInputMap("backspace", SDLK_BACKSPACE);

	AddInputMap("lctrl", SDLK_LCTRL);
	AddInputMap("rctrl", SDLK_RCTRL);
	AddInputMap("lalt", SDLK_LALT);
	AddInputMap("lshift", SDLK_LSHIFT);
	AddInputMap("rshift", SDLK_RSHIFT);
	AddInputMap("ralt", SDLK_RALT);

	AddInputMap("q", SDLK_q);
	AddInputMap("w", SDLK_w);
	AddInputMap("e", SDLK_e);
	AddInputMap("r", SDLK_r);
	AddInputMap("t", SDLK_t);
	AddInputMap("y", SDLK_y);
	AddInputMap("u", SDLK_u);
	AddInputMap("i", SDLK_i);
	AddInputMap("o", SDLK_o);
	AddInputMap("p", SDLK_p);
	AddInputMap("a", SDLK_a);
	AddInputMap("s", SDLK_s);
	AddInputMap("d", SDLK_d);
	AddInputMap("f", SDLK_f);
	AddInputMap("g", SDLK_g);
	AddInputMap("h", SDLK_h);
	AddInputMap("j", SDLK_j);
	AddInputMap("k", SDLK_k);
	AddInputMap("l", SDLK_l);
	AddInputMap("z", SDLK_z);
	AddInputMap("x", SDLK_x);
	AddInputMap("c", SDLK_c);
	AddInputMap("v", SDLK_v);
	AddInputMap("b", SDLK_b);
	AddInputMap("n", SDLK_n);
	AddInputMap("m", SDLK_m);

	AddInputMap("1", SDLK_1);
	AddInputMap("2", SDLK_2);
	AddInputMap("3", SDLK_3);
	AddInputMap("4", SDLK_4);
	AddInputMap("5", SDLK_5);
	AddInputMap("6", SDLK_6);
	AddInputMap("7", SDLK_7);
	AddInputMap("8", SDLK_8);
	AddInputMap("9", SDLK_9);
	AddInputMap("0", SDLK_0);

}