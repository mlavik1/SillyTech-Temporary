#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include <map>
#include "shader.h"
#include <unordered_map>

class ShaderProgram
{
private:
	GLint getUniformLocation(const char *arg_name);
	GLint mShaderProgram;
	std::map<SHADER_TYPE, std::string> mShaders;
public:
	ShaderProgram();
	~ShaderProgram();

	void CreatePogram();
	void SetShader(SHADER_TYPE arg_type, const char* arg_shader);
	std::string GetShader(SHADER_TYPE arg_type);
	inline GLint GetShaderProgram()
	{
		return mShaderProgram;
	}

public:
	void SetUniform(const char *arg_name, const glm::vec3 & v);
	void SetUniform(const char *arg_name, const glm::vec4 & v);
	void SetUniform4fv(const char *arg_name, const GLfloat *m);
	void SetUniform(const char *arg_name, float val);
	void SetUniform(const char *arg_name, GLint val);

	void SetIsPostProcess(bool arg_pp);
	bool GetIsPostProcess();

private:
	std::unordered_map<std::string, GLint> mUniformLocations;
	void UseProgram();
	bool mIsPostProcess;

};

#endif