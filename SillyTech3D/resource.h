#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource
{

public:
	virtual void Reload();

protected:
	std::string mResourceName;
	std::string mResourcePath;

public:
	Resource(const char *arg_name, const char * arg_path);
	~Resource();

	std::string GetResourceName();
	std::string GetResourcePath();
};


#endif