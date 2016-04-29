#ifndef ACTOR_H
#define ACTOR_H

#include "core_events.h"
#include "st_assert.h"
#include <memory>
#include "component.h"
#include <vector>
#include <string>
#include "transform.h"
#include "lua_garbage.h"
//#include "boost/enable_shared_from_this.hpp"

typedef std::shared_ptr<Component> component_ptr;

class Actor : ICoreEvents
{
public:
	Actor();
	~Actor();

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	void AttachComponent(Component *arg_component);
	void DetachComponent(Component *arg_component);
	
	void SetName(const char* arg_name);
	void SetTransform(Transform arg_trans);
	void SetParent(Actor *arg_parent);
	void AddChild(Actor *arg_child);
	void RemoveChild(Actor *arg_child);
	
	//void SetTransformDirty();
	Transform&					GetTransform();
	Actor*						GetParent();
	std::string					GetName();
	glm::vec3					GetVelocity();
	std::vector<Actor*>			GetChildren();


private:
	std::vector<Component*>		mComponents;
	std::vector<Actor*>			mChildren;
	Actor*						mParent;
	std::string					mName;
	Transform					mTransform;
	glm::vec3					mOldPosition;
	glm::vec3					mVelocity;


	
public:
	template <typename T>
	T *GetComponentByType(bool search_children = false)
	{
		//__AssertComment((std::is_base_of<Component, T>::value), "Type must be Component.");
		for (Component *comp : mComponents)
		{
			T* t = dynamic_cast<T*>(comp);
			if (t)
				return t;
		}
		if (search_children && mChildren.size() > 0)
		{
			for (Actor *child : mChildren)
			{
				T* ct = child->GetComponentByType<T>(search_children);
				if (ct)
					return ct;
			}
		}
		return 0;
	}
	
	/*** LUA uses this ***/
	template <typename T>
	std::vector<T*> &GetComponentsPtrByType(bool arg_inchildren = false)
	{
		std::vector<T*> *vec = new std::vector<T*>();
		LuaGarbage<T>::Instance()->SetPointerVector(vec); // temporarily store here, so Lua script can access the pointer

		addComponentsToVector<T>(*vec, arg_inchildren);
		return *vec;
	}

	template <typename T>
	std::vector<T*> GetComponentsByType(bool arg_inchildren = false)
	{
		std::vector<T*> vec;

		addComponentsToVector<T>(vec, arg_inchildren);

		return vec;
	}

private:
	template <typename T>
	void addComponentsToVector(std::vector<T*> &vec, bool arg_inchildren = false)
	{
		for (Component *comp : mComponents)
		{
			T* t = dynamic_cast<T*>(comp);
			if (t)
				vec.push_back(t);
		}
		if (arg_inchildren)
			for (Actor *child : mChildren)
				child->addComponentsToVector<T>(vec, arg_inchildren);
	}
};

#endif