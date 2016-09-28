#include "actor_manager.h"

__ImplementSingleton(ActorManager)

ActorManager::ActorManager()
{
	__ConstructSingleton(ActorManager)
}


ActorManager::~ActorManager()
{
	__DestructSingleton(ActorManager)
}


void ActorManager::AttachActor(Actor *arg_actor)
{
	mActors.push_back(actor_ptr(arg_actor));
	arg_actor->OnActivate();
}

void ActorManager::OnFrame()
{
	Manager::OnFrame();

	std::vector<actor_ptr>::iterator i;

	for (i = mActors.begin(); i != mActors.end(); i++)
		(*i)->OnFrame();
}

void ActorManager::OnStart()
{
	Manager::OnStart();

	std::vector<actor_ptr>::iterator i;

	for (i = mActors.begin(); i != mActors.end(); i++)
		(*i)->OnStart();
}

void ActorManager::OnStop()
{
	Manager::OnStop();

	std::vector<actor_ptr>::iterator i;

	for (i = mActors.begin(); i != mActors.end(); i++)
		(*i)->OnStop();
}

void ActorManager::OnActivate()
{
	Manager::OnActivate();
}

void ActorManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

std::vector<actor_ptr> ActorManager::GetActors()
{
	return mActors;
}