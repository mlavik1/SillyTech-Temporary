#include "material.h"

#include "resource_manager.h"
#include "shader_res.h"

Material::Material()
{
	SetShader(SHADER_TYPE_VERTEXSHADER, "Resources/Shaders/default_shader.vs");
	SetShader(SHADER_TYPE_FRAGMENTSHADER, "Resources/Shaders/default_shader.fs");
	SetShader(SHADER_TYPE_GEOMETRYSHADER, "Resources/Shaders/default_shader.gs");
}

Material::~Material()
{

}

Material::Material(const Material &other)
{
	this->mTextures = other.mTextures;
}

void Material::SetTexture(const char* arg_texture_type, const char* arg_texture)
{
	mTextures[arg_texture_type] = arg_texture;

}

std::string Material::GetTexture(const char* arg_texture_type)
{
	return mTextures[arg_texture_type];
}

void Material::SetShader(SHADER_TYPE arg_type, const char* arg_shader)
{
	mShaderProgram.SetShader(arg_type, arg_shader);
}

std::string Material::GetShader(SHADER_TYPE arg_type)
{
	return mShaderProgram.GetShader(arg_type);
}

void Material::CreateShaderProgram()
{
	mShaderProgram.CreatePogram();

}

glm::vec4 Material::GetColour()
{
	return mColour;
}

void Material::SetColour(glm::vec4 arg_colour)
{
	mColour = arg_colour;
}