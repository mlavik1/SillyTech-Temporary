#ifndef DISPLAY_H
#define DISPLAY_H

#include "viewport.h"

class Display
{
public:
	virtual void InitWindow(const char* arg_title, int x, int y, int widht, int height) {}
	virtual void Reshape(int x, int y, int w, int h) {}
	virtual void Reshape() {}
	virtual void Reshape(Viewport &arg_viewport) {}
	virtual void SwapBuffers() {}
	virtual void PositionConsoleWindow(int arg_x, int arg_y) {}
	virtual void ResizeConsoleWindow(int arg_w, int arg_h) {}
	virtual int GetScreenWidth() { return 600; }
	virtual int GetScreenHeight() { return 400; }
	virtual void SetSize(int w, int h){}
	virtual void SetFullscreen(bool arg_fullscreen){}
	virtual bool IsFullscreen() { return false; }

};

#endif