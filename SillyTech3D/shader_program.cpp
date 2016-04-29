#include "shader_program.h"
#include "debug.h"
#include "resource_manager.h"
#include "shader_res.h"

ShaderProgram::ShaderProgram()
{
	mShaderProgram = -1;
}
ShaderProgram::~ShaderProgram()
{

}

GLint ShaderProgram::getUniformLocation(const char *arg_name)
{
	GLint loc = -1;
	auto it = mUniformLocations.find(arg_name);
	if (it == mUniformLocations.end())
	{
		loc = glGetUniformLocation(mShaderProgram, arg_name);
		mUniformLocations[arg_name] = loc;

		if (loc == -1)
			LOG_WARNING() << "Failed to get " << arg_name << " uniform from program";
	}		
	else
		loc = it->second;

	return loc;
}
	

void ShaderProgram::SetUniform(const char *arg_name, const glm::vec3 & v)
{
	UseProgram();

	GLint loc = getUniformLocation(arg_name);
	if (loc != -1)
		glUniform3fv(loc, 1, glm::value_ptr(v));
}
void ShaderProgram::SetUniform(const char *arg_name, const glm::vec4 & v)
{
	UseProgram();

	GLint loc = getUniformLocation(arg_name);
	if (loc != -1)
		glUniform4fv(loc, 1, glm::value_ptr(v));
}
void ShaderProgram::SetUniform4fv(const char *arg_name, const GLfloat *m)
{
	UseProgram();

	GLint loc = getUniformLocation(arg_name);
	if(loc != -1)
		glUniformMatrix4fv(loc, 1, GL_FALSE, m);
}
void ShaderProgram::SetUniform(const char *arg_name, float val)
{
	UseProgram();

	GLint loc = getUniformLocation(arg_name);
	if (loc != -1)
		glUniform1f(loc, val);
}
void ShaderProgram::SetUniform(const char *arg_name, GLint val)
{
	UseProgram();

	GLint loc = getUniformLocation(arg_name);

	if (loc != -1)
		glUniform1i(loc, val);
}

void ShaderProgram::CreatePogram()
{
	// TODO: move to GLGraphicsImp
	if (mShaderProgram != -1)
	{
		glUseProgram(0);
		glDeleteProgram(mShaderProgram);
	}	

	mShaderProgram = glCreateProgram();

	ShaderRes *res = ResourceManager<ShaderRes>::Instance()->GetResource(mShaders[SHADER_TYPE_VERTEXSHADER].c_str());
	if (!res)
	{
		LOG_ERROR() << "Cannot create shader program. ShaderRes not found: " << mShaders[SHADER_TYPE_VERTEXSHADER].c_str();
		return;
	}
		
	glAttachShader(mShaderProgram, res->GetShader()->GetShader());

	res = ResourceManager<ShaderRes>::Instance()->GetResource(mShaders[SHADER_TYPE_GEOMETRYSHADER].c_str());
	if (!res)
	{
		if (mShaders[SHADER_TYPE_GEOMETRYSHADER] != "")
		{
			LOG_ERROR() << "Cannot create shader program. ShaderRes not found: " << mShaders[SHADER_TYPE_GEOMETRYSHADER].c_str();
			return;
		}		
	}
	else
		glAttachShader(mShaderProgram, res->GetShader()->GetShader());

	res = ResourceManager<ShaderRes>::Instance()->GetResource(mShaders[SHADER_TYPE_FRAGMENTSHADER].c_str());
	if (!res)
	{
		LOG_ERROR() << "Cannot create shader program. ShaderRes not found: " << mShaders[SHADER_TYPE_FRAGMENTSHADER].c_str();
		return;
	}
	glAttachShader(mShaderProgram, res->GetShader()->GetShader());


	glLinkProgram(mShaderProgram);
	GLint success;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar error[1024];
		glGetProgramInfoLog(mShaderProgram, sizeof(error), NULL, error);
		LOG_ERROR() << "Error linking shader program: " << std::string(error);
	}

	glValidateProgram(mShaderProgram);
	glGetProgramiv(mShaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		GLchar error[1024];
		glGetProgramInfoLog(mShaderProgram, sizeof(error), NULL, error);
		LOG_ERROR() << "Error validating shader program: " << std::string(error);
	}

	//LOG_INFO() << "Created shader program";

}

void ShaderProgram::SetShader(SHADER_TYPE arg_type, const char* arg_shader)
{
	mShaders[arg_type] = arg_shader;
}

std::string ShaderProgram::GetShader(SHADER_TYPE arg_type)
{
	return mShaders[arg_type];
}

void ShaderProgram::UseProgram()
{
	GLint currProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
	if (currProgram != mShaderProgram)
		glUseProgram(mShaderProgram);
}


void ShaderProgram::SetIsPostProcess(bool arg_pp)
{
	mIsPostProcess = arg_pp;
}
bool ShaderProgram::GetIsPostProcess()
{
	return mIsPostProcess;
}