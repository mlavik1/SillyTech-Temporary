#include "texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include "GL/glew.h"
#include "debug.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::BufferTexture()
{
	// TODO: do this through GLimp class !

	SDL_Surface *surface = IMG_Load(mFilename.c_str());
	if (surface == NULL)
	{
		LOG_ERROR() << "SDL could not load texture: " << mFilename;
		return;
	}
	glGenTextures(1, &mTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, mTextureBuffer);
	if (surface->format->BitsPerPixel == 32)
	{	// 32 bit
		if(surface->format->Bshift < surface->format->Gshift) // BGRA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
		else // RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else // 24 bit
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}
	SDL_FreeSurface(surface);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}