#include "texture_factory.h"

#include "resource_manager.h"
#include "texture_res.h"

Texture* TextureFactory::CreateFromFile(const char* arg_file)
{
	Texture *texture;

	TextureRes *res = ResourceManager<TextureRes>::Instance()->GetResource(arg_file);
	if (res)
		return res->GetTexture();	// texture already imported
	else
	{
		res = new TextureRes(arg_file);
		ResourceManager<TextureRes>::Instance()->AddResource(res);
		texture = new Texture();
	}
		

	texture->SetFilename(arg_file);
	texture->BufferTexture();
	res->SetTexture(texture);
	// code here

	return texture;
}