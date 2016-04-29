#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <map>
#include <vector>
#include "debug.h"
#include "shader.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "shader_program.h"

#define TEXTURE_TYPE_DIFFUSE		"diffuse"
#define TEXTURE_TYPE_BUMPMAP		"bumpmap"

class Material
{
	friend class EditorGUI;
public:
	Material();
	~Material();
	Material(const Material &other);

private:
	std::map<std::string, std::string> mTextures;
	ShaderProgram mShaderProgram;
	glm::vec4 mColour;
	
public:
	void SetTexture(const char* arg_texture_type, const char* arg_texture);
	std::string GetTexture(const char* arg_texture_type);
	void SetShader(SHADER_TYPE arg_type, const char* arg_shader);
	std::string GetShader(SHADER_TYPE arg_type);
	void CreateShaderProgram();
	glm::vec4 GetColour();
	void SetColour(glm::vec4 arg_colour);

	inline ShaderProgram &GetShaderProgram()
	{
		return mShaderProgram;
	}
};


#endif
