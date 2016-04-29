#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <unordered_map>

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	int GetTime();
	int GetTimeAndRestart();
	void LogTime(const char *arg_id);
	int GetTimeLog(const char *arg_id);
	void PrintTimeLog();

private:
	unsigned int mStartTicks;
	std::unordered_map<std::string, int> mTimeMap;
};

#endif