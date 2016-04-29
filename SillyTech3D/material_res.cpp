#include "material_res.h"
#include "debug.h"

MaterialRes::MaterialRes(const char *arg_name, Material *arg_mat)
	: Resource::Resource(arg_name, "")
{
	mMaterial = arg_mat;

	Reload();

}

MaterialRes::~MaterialRes()
{

}


void MaterialRes::Reload()
{
	Resource::Reload();
	mMaterial->CreateShaderProgram();

}


Material *MaterialRes::GetMaterial()
{
	return mMaterial;
}

