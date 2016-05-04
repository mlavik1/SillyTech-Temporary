#include <exception>


class ExceptionHandler
{
	public:
		static void initialiseHandlers();
		
	private:
		static void signalHandler(int sig);
		static void terminateHandler();
};


