#include "shader_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "debug.h"

std::string ShaderReader::GetShader(const char* arg_filename)
{
	ShaderReader sr;
	return sr.getShader(arg_filename);
}



ShaderReader::ShaderReader()
{

}

ShaderReader::~ShaderReader()
{

}


std::string ShaderReader::getShader(const char* arg_filename)
{
	
	parseFile(arg_filename);

	std::stringstream ss("");

	ss << "#version 330 core" << "\n";

	for (std::string str : mDefinitionList)
		ss << str << "\n";
	
	for (std::string attr : mAttributeList)
		ss << attr + "\n";

	for (std::string unif : mUniformList)
		ss << unif << "\n";

	ss << mFunctions.str() << "\n";

	ss << mMainMetod.str() << "\n";


	
	// TODO: Create final shader



	return ss.str();
}

void ShaderReader::parseFile(const char* arg_filename)
{
	std::stringstream path(""); path << SHADER_PATH << "/" << arg_filename;
	std::ifstream input(path.str());
	if (!input)
		LOG_ERROR() << "Could not find file: " << path.str();
	std::string currRegion = "";

	std::string line;
	while (std::getline(input, line))
	{
		// ALWAYS parse definitions
		std::size_t index = line.find("#define");
		if (index != std::string::npos)
		{
			std::stringstream ss("");
			for (size_t i = line.length(); line[i] != ' '; i--)
				ss << line[i];
			mDefinitionList.push_back(ss.str());
		}


		std::string reg = getRegion(line);
		if (reg == "END")
			currRegion = "";
		else if (reg != "")
		{
			if (currRegion != "")
				LOG_WARNING() << "Found new region before the previous has been ended: " << reg;

			currRegion = reg;
		}

		if (currRegion == "" || reg != "")
			continue;

		if (currRegion == "INCLUDES")
		{
			std::size_t lIndex = line.find("<");
			std::size_t rIndex = line.find(">");
			if (lIndex != std::string::npos && rIndex != std::string::npos)
				{
				std::string newDef = line.substr(lIndex+1, rIndex - lIndex-1).c_str();
				for (std::string def : mDefinitionList)
				{
					if (def == newDef)
					{
						LOG_ERROR() << "Found circular dependency in: " << arg_filename;
						continue;
					}
				}
				parseFile(newDef.c_str());
			}

		}
		else if (currRegion == "STRUCTURES")
		{
			if (line != "")
				mStructures << "\n" << line.c_str();
		}
		else if (currRegion == "ATTRIBUTES")
		{
			// TODO: Check for duplicates
			if (line != "")
				mAttributeList.push_back(line);
		}

		else if (currRegion == "UNIFORMS")
		{
			if (line != "")
				mUniformList.push_back(line);
		}
		else if (currRegion == "FUNCTIONS")
		{
			mFunctions << "\n" << line.c_str();
		}
		else if (currRegion == "MAIN")
		{
			mMainMetod << "\n" << line.c_str();
		}
	}
}

std::string ShaderReader::getRegion(std::string arg_line)
{
	std::size_t index = arg_line.find("#region begin");
	if (index != std::string::npos)
	{
		std::size_t lIndex = arg_line.find("<");
		std::size_t rIndex = arg_line.find(">");
		if (lIndex == std::string::npos || rIndex == std::string::npos)
		{
			LOG_ERROR() << "Illegar region: " << arg_line;
			return "";
		}
		else
		{
			return arg_line.substr(lIndex+1, rIndex - lIndex-1);
		}

	}

	index = arg_line.find("#region end");
	if (index != std::string::npos)
		return "END";

	return "";
}
