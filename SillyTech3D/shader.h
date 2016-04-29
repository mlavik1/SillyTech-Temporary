#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include "shader_reader.h"
#include <string>

#define SHADER_TYPE_VERTEXSHADER		1
#define SHADER_TYPE_FRAGMENTSHADER		2
#define SHADER_TYPE_GEOMETRYSHADER		3

typedef unsigned int SHADER_TYPE;

class Shader
{
public:
	Shader(const char* arg_filename, SHADER_TYPE arg_type);
	~Shader();

	bool Compile();

	inline SHADER_TYPE GetShaderType()
	{
		return mShaderType;
	}
	inline std::string GetFilename()
	{
		return mFilename;
	}
	inline GLuint GetShader()
	{
		return mShader;
	}

private:
	SHADER_TYPE mShaderType;
	GLuint mShader;
	std::string mFilename;
};

#endif