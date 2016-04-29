/*
* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* !!!!!!!!! Garbage manager for Lua !!!!!!!!!
* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* --- Use this when you want to pass std:vectors
*    of pointers to Lua.
* --- Memory must be allocated on heap, so
*   if you store it here it will automatically
*   be deleted.
*/

#ifndef LUAGARBAGE_H
#define LUAGARBAGE_H

#include <map>
#include <vector>
#include <type_traits>
#include <typeindex>

template <typename T>
class LuaGarbage
{
public:
	static LuaGarbage<T> *Instance()
	{
		if (LuaGarbage<T>::_instance == 0) {
			LuaGarbage<T>::_instance = new LuaGarbage<T>();
		}
		return LuaGarbage<T>::_instance;
	}
private:
	static LuaGarbage<T> *_instance;

private:
	std::map<std::type_index, std::vector<T*>*> mPointerVectors;
	inline explicit LuaGarbage()
	{
		LuaGarbage::_instance = static_cast<LuaGarbage<T>*>(this);
	}
	inline ~LuaGarbage() {
		LuaGarbage::_instance = 0;
	}

public:
	void SetPointerVector(std::vector<T*> *arg_vec)
	{
		std::vector<T*> *vec = mPointerVectors[typeid(T)];
		if (vec)
			delete(vec);
		vec = arg_vec;
	}


};

template <typename T>
LuaGarbage<T> *LuaGarbage<T>::_instance = 0;
/*template <typename T> \
type *type::Create() \
{ \
type *newObject = new type(); \
return newObject; \
}*/

#endif
