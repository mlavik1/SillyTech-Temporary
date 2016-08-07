#ifndef COMPONENT_H
#define COMPONENT_H

#include "core_events.h"
#include <string>

class Actor;

class Component : public ICoreEvents
{

public:
	virtual void OnBeginFrame() override;
	virtual void OnFrame() override;
	virtual void OnEndFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;


	void			SetParent(Actor *arg_parent);


	Actor*			GetParent();
	std::string		GetMemoryHash();

protected:
	Actor* mParent;	
	
public:
	Component();
	virtual ~Component();
};

#endif