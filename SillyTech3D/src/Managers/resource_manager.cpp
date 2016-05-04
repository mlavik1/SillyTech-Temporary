#ifndef __ResourceManager_CPP__
#define __ResourceManager_CPP__
#include "resource_manager.h"

#include <type_traits>

__ImplementTemplateSingleton(ResourceManager<T>)

template <typename T>
ResourceManager<T>::ResourceManager()
{
	__AssertComment((std::is_base_of<Resource, T>::value), "Cannot create Resource Manager. Type must be Resource.");

	__ConstructSingleton(ResourceManager<T>);
}

template <typename T>
ResourceManager<T>::~ResourceManager()
{
	__DestructSingleton(ResourceManager<T>);
}

template <typename T>
T *ResourceManager<T>::GetResource(const char *arg_name)
{
	T *t1 = mResources[arg_name];
	return t1;
}

template <typename T>
T *ResourceManager<T>::AddResource(T* arg_res)
{
	__AssertComment((std::is_base_of<Resource, T>::value), "Cannot add object to Resource Manager. Type must be Resource.");
	__AssertComment((arg_res != 0), "Resource cannot be NULL");

	mResources[((Resource*)arg_res)->GetResourceName()] = arg_res;
	return arg_res;
}


#endif