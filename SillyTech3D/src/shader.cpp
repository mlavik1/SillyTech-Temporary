#include "shader.h"
#include <fstream>

#include "debug.h"

Shader::Shader(const char* arg_filename, SHADER_TYPE arg_type)
{
	mFilename = arg_filename;
	mShaderType = arg_type;
}

Shader::~Shader()
{

}

bool Shader::Compile()
{
	GLuint glShaderType;
	if (mShaderType == SHADER_TYPE_VERTEXSHADER)
		glShaderType = GL_VERTEX_SHADER;
	else if (mShaderType == SHADER_TYPE_FRAGMENTSHADER)
		glShaderType = GL_FRAGMENT_SHADER;
	else if (mShaderType == SHADER_TYPE_GEOMETRYSHADER)
		glShaderType = GL_GEOMETRY_SHADER;
	else
		LOG_ERROR() << "Undefined shader type: " << mShaderType;

	if (mShader)
	{
		//glUseProgram(0);
		glDeleteShader(mShader);
	}
		
	GLuint newShader;
	newShader = glCreateShader(glShaderType);

	std::ifstream inFile;				//uses <fstream>
	inFile.open(mFilename);		//open the input file
	if (!inFile.is_open())
	{
		LOG_ERROR() << "ERROR: Could not open " << mFilename;
		return false;
	}
		
	std::stringstream strStream;			// uses <sstream>
	// ***** TODO: Use ShaderReader *****
											//if(mFilename == "Resources/Shaders/default_shader.vs")
	//	strStream << ShaderReader::GetShader("DefaultShader.vs");
	//else
		strStream << inFile.rdbuf();	//read the file
	std::string shaderText = strStream.str();	//str holds the content of the file
	const char* text = shaderText.c_str();
	const GLint length = strlen(text);

	glShaderSource(newShader, 1, &text, &length);

	glCompileShader(newShader);
	GLint success;
	glGetShaderiv(newShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(newShader, sizeof(infoLog), NULL, infoLog);
		LOG_ERROR() << "Error compling shader: " << std::string(infoLog);
		std::ofstream out("ShaderError.txt");
		out << shaderText << "\n\n**********\n" << std::string(infoLog);
		out.close();
		return false;
	}
	else
	{
		mShader = newShader;
		LOG_INFO() << "Successfully compiled shader: " << mFilename;
		return true;
	}
		

	//glAttachShader(arg_shaderProgram, shader);
}