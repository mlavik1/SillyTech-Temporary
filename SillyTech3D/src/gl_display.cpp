#include "gl_display.h"
#include "debug.h"
#ifdef _WIN32
#include <Windows.h>
#endif

GLDisplay::GLDisplay()
{

}

GLDisplay::~GLDisplay()
{

}

void GLDisplay::InitWindow(const char* arg_title, int x, int y, int width, int height)
{
	win_width = width;
	win_height = height;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		LOG_ERROR() << "Failed to initialise SDL";
	else
	{
		SDL_version linkedver; SDL_version compiledver;
		SDL_GetVersion(&linkedver);
		SDL_VERSION(&compiledver);
		LOG_INFO() << "SDL compiled version: " << (int)compiledver.major << "." << (int)compiledver.minor << ", pathch: " << (int)compiledver.patch;
		LOG_INFO() << "SDL linked version: " << (int)linkedver.major << "." << (int)linkedver.minor << ", pathch: " << (int)linkedver.patch;
	}

	mMainWindow = SDL_CreateWindow(arg_title, x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	mMainGLContext = SDL_GL_CreateContext(mMainWindow);

	LOG_INFO() << "Using OpenGL, version " << glGetString(GL_VERSION);
	
	GLenum res = glewInit();
	if (res != GLEW_OK)
		LOG_ERROR() << "Failed to initialise glew";
	else
		LOG_INFO() << "Using glew, version " << glewGetString(GLEW_VERSION);
		
	Reshape(0, 0, width, height);
}

void GLDisplay::PositionConsoleWindow(int arg_x, int arg_y)
{
#ifdef _WIN32
	HWND window = GetConsoleWindow();
	SetWindowPos(window, 0, arg_x, arg_y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
#else
	LOG_WARNING() << "Unhandles OS. Cannot position console window";
#endif
}

void GLDisplay::ResizeConsoleWindow(int arg_w, int arg_h)
{
#ifdef _WIN32
	HWND window = GetConsoleWindow();
	RECT r;
	GetWindowRect(window, &r);
	MoveWindow(window, r.left, r.top, arg_w, arg_h, TRUE);
#else
	LOG_WARNING() << "Unhandles OS. Cannot position console window";
#endif
}

void GLDisplay::SwapBuffers()
{
	SDL_GL_SwapWindow(mMainWindow);
}

void GLDisplay::Reshape()
{
	Reshape(0,0, win_width, win_height);
}

void GLDisplay::Reshape(Viewport &arg_viewport)
{
	Reshape(win_width * arg_viewport.x, win_height* arg_viewport.y, win_width * arg_viewport.w, win_height* arg_viewport.h);
}

void GLDisplay::Reshape(int x, int y, int w, int h)
{

	if (h == 0)
		h = 1;
	float wf = (float)w;
	float hf = (float)h;

	float ratio = wf / hf;
	float nearZ = 1.0f;
	float farZ = 121212.0f;
	float fov = 50.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(x, y, wf, hf);
	//if (m_pCurrentCamera == 0 || m_pCurrentCamera->GetType() == Camera::CameraType::PERSPECTIVE)
		gluPerspective(fov, ratio, nearZ, farZ);
	//else
	//	glOrtho(-4 * ratio, 4 * ratio, -4, 4, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);

}

int GLDisplay::GetScreenWidth()
{
	return win_width;
}
int GLDisplay::GetScreenHeight()
{
	return win_height;
}


void GLDisplay::SetSize(int w, int h)
{
	win_width = w;
	win_height = h;
	SDL_SetWindowSize(mMainWindow, w, h);
	Reshape();
}

void GLDisplay::SetFullscreen(bool arg_fullscreen)
{
	if (arg_fullscreen)
		SDL_SetWindowFullscreen(mMainWindow, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(mMainWindow, ~SDL_WINDOW_FULLSCREEN);
	Reshape();
}

bool GLDisplay::IsFullscreen()
{
	return (SDL_GetWindowFlags(mMainWindow) & SDL_WINDOW_FULLSCREEN);
}