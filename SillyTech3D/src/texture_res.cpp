#include "texture_res.h"
#include "debug.h"

TextureRes::TextureRes(const char *arg_name) : Resource::Resource(arg_name, "")
{
	Reload();

}

TextureRes::~TextureRes()
{

}


void TextureRes::Reload()
{
	Resource::Reload();

}

void TextureRes::SetTexture(Texture *arg_Texture)
{
	mTexture = arg_Texture;
}

Texture *TextureRes::GetTexture()
{
	return mTexture;
}

