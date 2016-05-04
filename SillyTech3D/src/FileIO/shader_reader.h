#ifndef SHADERREADER_H
#define SHADERREADER_H

#include <string>
#include <sstream>
#include <map>
#include <vector>

class ShaderReader
{
public:
	static std::string GetShader(const char* arg_filename);

private:
	ShaderReader();
	~ShaderReader();
	
	void parseFile(const char* arg_filename);

	std::string				getShader(const char* arg_filename);
	std::string				getRegion(std::string arg_line);
	const char* SHADER_PATH = "Resources/STShaders";

private:
	std::map<std::string, std::string>	mHeaderMap;
	std::vector<std::string>			mDefinitionList;
	std::vector<std::string>			mAttributeList;
	std::vector<std::string>			mUniformList;
	std::stringstream					mStructures;
	std::stringstream					mFunctions;
	std::stringstream					mMainMetod;
};

#endif