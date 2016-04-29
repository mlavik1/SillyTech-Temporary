#include "timer.h"
#include "debug.h"

Timer::Timer()
{

}
Timer::~Timer()
{

}

void Timer::Start()
{
	mStartTicks = SDL_GetTicks();
}

int Timer::GetTime()
{
	return SDL_GetTicks() - mStartTicks;
}

int Timer::GetTimeAndRestart()
{
	int ticks = SDL_GetTicks() - mStartTicks;
	mStartTicks = SDL_GetTicks();
	return ticks;
}

void Timer::LogTime(const char *arg_id)
{
	mTimeMap[arg_id] = GetTimeAndRestart();
}

int Timer::GetTimeLog(const char *arg_id)
{
	return mTimeMap[arg_id];
}

void Timer::PrintTimeLog()
{
	std::unordered_map<std::string, int>::iterator it = mTimeMap.begin();
	while (it != mTimeMap.end())
	{
		LOG_INFO() << it->first << " : " << it->second;
		it++;
	}
}