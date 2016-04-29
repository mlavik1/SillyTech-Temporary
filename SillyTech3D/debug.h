#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#define DEBUG_MODE_NONE				0x0000
#define DEBUG_MODE_INFO				0x0001
#define DEBUG_MODE_WARNING			0x0002
#define DEBUG_MODE_EXCEPTION		0x0004
#define DEBUG_MODE_ERROR			0x0008
#define DEBUG_MODE_ALL				0x000F

typedef unsigned int DEBUG_MODE;
typedef unsigned int OUTPUT_MODE;

class Debug
{
public:
	Debug(DEBUG_MODE mode = DEBUG_MODE_INFO)
	{
		outputMode = mode;

		if (!(outputMode & (fileLogMode | terminalLogMode)))
			return;

		std::string prefix;

		DEBUG_MODE bitmask = outputMode;
		DEBUG_MODE bit = DEBUG_MODE_ERROR;
		while (bitmask)
		{
			switch (bitmask & bit)
			{
			case DEBUG_MODE_INFO:
				prefix = "";
				break;
			case DEBUG_MODE_WARNING:
				prefix = "Warning: ";
				break;
			case DEBUG_MODE_ERROR:
				prefix = "ERROR: ";
				break;
			case DEBUG_MODE_EXCEPTION:
				prefix = "Exception: ";
				break;
			}
			bitmask &= ~bit;
			bit >>= 1;
		}

		_buffer << prefix;
	}

	template <typename T>
	Debug & operator<<(T const &value)
	{
		if (outputMode & terminalLogMode)
			_buffer << value;
		return *this;
	}

	~Debug()
	{
		_buffer << std::endl;
		std::cout << _buffer.str();

		
		if (fileLogMode & outputMode)
		{
			std::ofstream myFile;
			if (firstTime)
			{
				firstTime = false;
				myFile = std::ofstream("DebugLog.txt", std::ios::trunc);
			}
			else
				myFile = std::ofstream("DebugLog.txt", std::ios::app);

			myFile << _buffer.str();
			myFile.close();
		}
		
	}


	static void SetTerminalLogMode(DEBUG_MODE mode)
	{
		terminalLogMode = mode;
	}

	static void SetFileLogMode(DEBUG_MODE mode)
	{
		fileLogMode = mode;
	}

private:
	std::ostringstream _buffer;
	static DEBUG_MODE terminalLogMode;
	static DEBUG_MODE fileLogMode;
	static DEBUG_MODE outputMode;
	static bool firstTime;
};

#define LOG(level) \
	Debug(level)
#define LOG_INFO() \
	Debug(DEBUG_MODE_INFO)
#define LOG_WARNING() \
	Debug(DEBUG_MODE_WARNING)
#define LOG_ERROR() \
	Debug(DEBUG_MODE_ERROR)
#define LOG_EXCEPTION() \
	Debug(DEBUG_MODE_EXCEPTION)


#endif