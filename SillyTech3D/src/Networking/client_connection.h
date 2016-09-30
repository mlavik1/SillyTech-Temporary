#pragma once

#include "tcp_connectionk.h"
#include <functional>

class ClientConnection : public TcpConnection
{
private:
	TCPsocket mServerSocket;

	std::function<void(const char*)> mMessageCallback;
	//void(*mMessageCallback)(const char*);
	void(*mServerDisconnectedCallback)();

public:
	ClientConnection();
	~ClientConnection();
	virtual void FetchNewMessages() override;
	void SendMessage(const char *arg_message);
	void SendMessage(const char *arg_message, int arg_length);
	bool Connect(const char *arg_host, int port);



// Callback modifiers
	template<typename Functor>
	inline void SetMessageCallback(Functor arg_func)
	{
		mMessageCallback = arg_func;
	}

	inline void SetServerDisconnectedCallback(void(*arg_func)())
	{
		mServerDisconnectedCallback = arg_func;
	}
};