#ifndef UNSAFE_SINGLETON_H_
#define UNSAFE_SINGLETON_H_

#include "st_assert.h"

#define __DeclareUnsafeSingleton(type) \
public: \
	static type *Instance() \
		{ \
			if(_instance) \
				return _instance; \
			return Create(); \
		}; \
	static type *Create(); \
private: \
	static type *_instance;

#define __ImplementUnsafeSingleton(type) \
	type *type::_instance = 0; \
	type *type::Create() \
		{ \
			type *newObject = new type(); \
			return newObject; \
		}

#define __ImplementUnsafeTemplateSingleton(type) \
	template <typename T> \
	type *type::_instance = 0; \
	template <typename T> \
	type *type::Create() \
		{ \
			type *newObject = new type(); \
			return newObject; \
		}

#define __ConstructUnsafeSingleton(type) \
    __Assert(_instance == 0); _instance = this;

#define __DestructUnsafeSingleton(type) \
	__Assert(_instance); _instance = 0;

#endif