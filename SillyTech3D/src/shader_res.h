#ifndef SHADERRES_H
#define SHADERRES_H

#include "resource.h"
#include "shader.h"

class ShaderRes : public Resource
{
public:
	ShaderRes(Shader *arg_shader);
	~ShaderRes();

private:
	Shader *mShader;

public:
	void Reload() override;

	Shader *GetShader();
};

#endif