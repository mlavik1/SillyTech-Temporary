#include "resource.h"

Resource::Resource(const char *arg_name, const char * arg_path)
{
	mResourceName = std::string(arg_name);
	mResourcePath = std::string(arg_path);
}

Resource::~Resource()
{

}

void Resource::Reload()
{

}

std::string Resource::GetResourceName()
{
	return mResourceName;
}

std::string Resource::GetResourcePath()
{
	return mResourcePath;
}