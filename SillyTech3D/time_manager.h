#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <SDL.h>


class TimeManager : public Manager
{
	__DeclareSingleton(TimeManager)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	float GetTime();
	float GetDeltaTime();
	float GetFramesPerSecond();
	void SetPaused(bool arg_paused);
	bool IsPaused();

private:
	TimeManager();
	~TimeManager();

	bool mPaused;

	Uint32 mStartTicks;
	Uint32 mPreviousTicks;
	Uint32 mCurrentTicks;
	Uint32 mDeltaTicks;



};


#endif