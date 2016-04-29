#ifndef TEXTFILEREADER_H
#define TEXTFILEREADER_H

#include <string>
#include <fstream>
#include "debug.h"

class TextFileReader
{
public:
	static std::string ReadString(const char* arg_file_path)
	{
		std::string strReturn = "";

		std::ifstream ifs(arg_file_path);
		if (ifs.is_open())
		{
			std::stringstream buffer;
			buffer << ifs.rdbuf();
			strReturn = buffer.str();
		}
		else
		{
			LOG_ERROR() << "(text_file_reader::ReadString) File not found: " << arg_file_path;
		}

		return strReturn;
	}
};


#endif