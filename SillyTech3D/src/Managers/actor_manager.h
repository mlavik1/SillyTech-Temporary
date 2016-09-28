#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <memory>

#include "actor.h"

typedef std::shared_ptr<Actor> actor_ptr;

class ActorManager : public Manager
{
	__DeclareSingleton(ActorManager)

public: 
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	void AttachActor(Actor *arg_actor);
	std::vector<actor_ptr> GetActors();

private:
	ActorManager();
	~ActorManager();

private:
	std::vector<actor_ptr> mActors;
};


#endif