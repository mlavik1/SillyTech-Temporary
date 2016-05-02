#ifndef TEXTURERES_H
#define TEXTURERES_H

#include "resource.h"
#include "texture.h"

class TextureRes : public Resource
{
public:
	TextureRes(const char *arg_name);
	~TextureRes();

private:
	Texture *mTexture;

public:
	void Reload() override;

	void SetTexture(Texture *arg_Texture);
	Texture *GetTexture();


};


#endif