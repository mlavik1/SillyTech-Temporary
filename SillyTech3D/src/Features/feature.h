#ifndef FEATURE_H
#define FEATURE_H

#include "core_events.h"
#include "singleton.h"

#include <string>
#include <vector>

#include "manager.h"

class Feature : public ICoreEvents
{

public:
	virtual void OnFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;

public:
	std::string GetFeatureName();
	void AttachManager(Manager *arg_manager);

protected:
	std::string mFeatureName;	// REMEMBER TO ADD
	std::vector<Manager*> mManagers;
};


#endif