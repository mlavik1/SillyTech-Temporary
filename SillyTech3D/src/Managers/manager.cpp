#include "manager.h"



void Manager::OnFrame()
{
	if (!mActive)
		return;
		
}

void Manager::OnStart()
{
	if (!mActive)
		return;
}

void Manager::OnStop()
{
	if (!mActive)
		return;
}

void Manager::OnActivate()
{
	mActive = true;
}

void Manager::OnDeactivate()
{
	mActive = true;
}
