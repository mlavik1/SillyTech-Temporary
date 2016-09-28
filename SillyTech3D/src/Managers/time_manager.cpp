#include "time_manager.h"
#include "Engine/game_engine.h"

__ImplementSingleton(TimeManager)

TimeManager::TimeManager()
{
	__ConstructSingleton(TimeManager)

		mPaused = false;
}


TimeManager::~TimeManager()
{
	__DestructSingleton(TimeManager)
}

void TimeManager::OnFrame()
{
	Manager::OnFrame();
	if (mPaused)
		return;

	mPreviousTicks = mCurrentTicks;
	mCurrentTicks = SDL_GetTicks();
	mDeltaTicks = mCurrentTicks - mPreviousTicks;
	
}

void TimeManager::OnStart()
{
	Manager::OnStart();

	Uint32 mStartTicks = SDL_GetTicks();
	mPreviousTicks = mStartTicks;
	mCurrentTicks = mStartTicks;
	mDeltaTicks = 0;
}

void TimeManager::OnStop()
{
	Manager::OnStop();
}

void TimeManager::OnActivate()
{
	Manager::OnActivate();
}

void TimeManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

float TimeManager::GetTime()
{
	return (float)(mCurrentTicks - mStartTicks) / 1000.0f;
}

float TimeManager::GetDeltaTime()
{
	return (float)mDeltaTicks/1000.0f;
}

float TimeManager::GetFramesPerSecond()
{
	return 1000.0f / (float)mDeltaTicks;
}

void TimeManager::SetPaused(bool arg_paused)
{
	if (mPaused)
		mStartTicks += (SDL_GetTicks() - mPreviousTicks);
	mPreviousTicks = SDL_GetTicks();
	mPaused = arg_paused;
	mDeltaTicks = 0;
}

bool TimeManager::IsPaused()
{
	return mPaused;
}