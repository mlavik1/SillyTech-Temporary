#include "manager.h"



void Manager::OnBeginFrame()
{
	if (!mActive)
		return;
}

void Manager::OnEndFrame()
{
	if (!mActive)
		return;
}

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
