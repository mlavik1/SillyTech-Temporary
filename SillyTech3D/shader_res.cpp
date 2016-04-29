#include "shader_res.h"
#include "debug.h"
#include "st_assert.h"

ShaderRes::ShaderRes(Shader *arg_shader) : Resource::Resource(arg_shader->GetFilename().c_str(), arg_shader->GetFilename().c_str())
{
	__AssertComment((arg_shader != 0), "Cannot create ShaderRes if Shader is NULL");

	mShader = arg_shader;
	Reload();

}

ShaderRes::~ShaderRes()
{

}


void ShaderRes::Reload()
{
	Resource::Reload();

	mShader->Compile();
}

Shader *ShaderRes::GetShader()
{
	return mShader;
}

