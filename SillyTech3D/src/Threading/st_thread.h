#include <thread>
#include <functional>

class ST_Thread
{
private:
	std::function<void()> mFunction;
	//void(*mFunction)();
	std::thread mThread;

public:
	void Execute();
	void WaitForThread();

	template <typename Functor>
	ST_Thread::ST_Thread(Functor arg_function)
	{
		mFunction = arg_function;
	}
	

};

