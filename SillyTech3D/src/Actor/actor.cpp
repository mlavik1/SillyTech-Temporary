#include "actor.h"
#include "time_manager.h"

Actor::Actor() : mTransform(this)
{
	REPLICATION_CONSTRUCTOR()

	mIsActive = false;
	mName = "";
	mParent = 0;
	
}

Actor::~Actor()
{
	__Assert(mComponents.empty());
}

void Actor::OnFrame()
{
	glm::vec3 newPos = mTransform.GetGlobalPosition();
	mVelocity = (newPos - mOldPosition) * TimeManager::Instance()->GetDeltaTime();
	mOldPosition = newPos;
}

void Actor::OnStart()
{
	__Assert(mIsActive);

	//std::vector<component_ptr>::iterator i;
	//for (i = mComponents.begin(); i != mComponents.end(); i++)
	//	(*i)->OnStart();
	for (Component* comp : mComponents)
		comp->OnStart();
}

void Actor::OnStop()
{

}

void Actor::OnActivate()
{
	mIsActive = true;
}

void Actor::OnDeactivate()
{
	mIsActive = false;
}

void Actor::AttachComponent(Component *arg_component)
{
	//mComponents.push_back(component_ptr(arg_component));
	mComponents.push_back(arg_component);
	arg_component->SetParent(this);
	arg_component->OnActivate();
}

void Actor::DetachComponent(Component *arg_component)
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents.at(i) == arg_component)
		{
			mComponents.erase(mComponents.begin() + i);
			break;
		}
	}
	//arg_component->SetParent(this);
	arg_component->OnDeactivate();
	delete arg_component;
}

void Actor::AddChild(Actor *arg_child)
{
	if (arg_child)
	{
		mChildren.push_back(arg_child);
		arg_child->SetParent(this);
	}
	
}

void Actor::RemoveChild(Actor *arg_child)
{
	
}

void Actor::SetParent(Actor *arg_parent)
{
	mParent = arg_parent;
}


std::string Actor::GetName()
{
	return mName;
}

void Actor::SetName(const char* arg_name)
{
	mName = arg_name;
}

Transform &Actor::GetTransform()
{
	return mTransform;
}


void Actor::SetTransform(Transform arg_trans)
{
	mTransform = arg_trans;
}

Actor *Actor::GetParent()
{
	return mParent;
}

/*void Actor::SetTransformDirty()
{
	mTransform.SetDirty();
	if(!mChildren.empty())
		for (Actor *child : mChildren)
			child->SetTransformDirty();
}*/

glm::vec3 Actor::GetVelocity()
{
	return mVelocity;
}

std::vector<Actor*> Actor::GetChildren()
{
	return mChildren;
}