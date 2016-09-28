#include "component.h"
#include "actor.h"

Component::Component()
{
	mIsActive = false;
}

Component::~Component()
{

}

void Component::SetParent(Actor *arg_parent)
{
	mParent = arg_parent;
}


void Component::OnFrame()
{

}

void Component::OnStart()
{
	__Assert(mIsActive);
}

void Component::OnStop()
{

}

void Component::OnActivate()
{
	__Assert(mParent != 0);
	mIsActive = true;
}

void Component::OnDeactivate()
{

}

Actor *Component::GetParent()
{
	return mParent;
}

std::string Component::GetMemoryHash()
{
	std::stringstream ss;
	ss << this;
	return ss.str();
}