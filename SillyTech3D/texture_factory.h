#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "texture.h"

class TextureFactory
{
public:
	static Texture* CreateFromFile(const char* arg_file);
};

#endif