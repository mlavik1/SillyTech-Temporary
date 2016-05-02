#ifndef MANAGER_H
#define MANAGER_H

//#include "feature_fwd_decl.h"
#include "core_events.h"
#include <vector>

class Manager : public ICoreEvents
{
public:
	virtual void OnBeginFrame() override;
	virtual void OnFrame() override;
	virtual void OnEndFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;

	inline void SetACtive(bool arg_active)
	{
		mActive = arg_active;
	}
	
private:
	bool mActive;

};

#endif
