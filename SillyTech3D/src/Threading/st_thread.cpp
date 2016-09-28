#include "st_thread.h"



void ST_Thread::Execute()
{
	auto lambda = [=](void)  -> void
	{
		mFunction();
	};

	mThread = std::thread(lambda);
	
}

void ST_Thread::WaitForThread()
{
	mThread.join();
}
