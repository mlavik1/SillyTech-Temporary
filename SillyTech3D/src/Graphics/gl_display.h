#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include "display.h"
#include <SDL.h>
#include <GL/glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class GLDisplay : public Display
{
public:
	GLDisplay();
	~GLDisplay();

	void InitWindow(const char* arg_title, int x, int y, int widht, int height);
	void Reshape(int x, int y, int w, int h);
	void Reshape();
	void Reshape(Viewport &arg_viewport);
	void SwapBuffers();
	void PositionConsoleWindow(int arg_x, int arg_y);
	void ResizeConsoleWindow(int arg_w, int arg_h);
	int GetScreenWidth();
	int GetScreenHeight();
	void SetSize(int w, int h);
	void SetFullscreen(bool arg_fullscreen);
	bool IsFullscreen();

private:
	SDL_Window *mMainWindow;
	SDL_GLContext mMainGLContext;
	int win_width, win_height;
	int win_x, win_y;
};

#endif