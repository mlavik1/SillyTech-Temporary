#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "singleton.h"
#include <map>
#include <string>
#include "resource.h"
#include <type_traits>
#include "st_assert.h"

template <class T>
class ResourceManager
{
__DeclareSingleton(ResourceManager<T>)

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, T*> mResources;


public:
	T *GetResource(const char *arg_name);
	T *AddResource(T* arg_res);
	inline std::map<std::string, T*> GetResources()
	{
		return mResources;
	}
};

#include "resource_manager.cpp"

#endif
