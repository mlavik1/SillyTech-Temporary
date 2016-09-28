#include "tcp_connectionk.h"

TcpConnection::TcpConnection()
{
	mConnected = false;
}

TcpConnection::~TcpConnection()
{
	SDLNet_FreeSocketSet(mSocketSet);

}

void TcpConnection::setHost(const char *arg_host)
{
	mHost = arg_host;
}

bool TcpConnection::getHostIPAddress(IPaddress &out, int port)
{
	const char *host = NULL;
	if (mHost != "")
		host = mHost.c_str();

	if (SDLNet_ResolveHost(&out, host, port))
	{
		return false;
	}
	else
		return true;
}

void TcpConnection::SetConnected(bool arg_connected)
{
	mConnected = arg_connected;
}


void TcpConnection::sendMessage(TCPsocket &socket, const char *arg_message)
{
	sendMessage(socket, arg_message, strlen(arg_message) + 1);
}

void TcpConnection::sendMessage(TCPsocket &socket, const char *arg_message, int length)
{
	SDLNet_TCP_Send(socket, arg_message, length);
}

bool TcpConnection::IsConnected()
{
	return mConnected;
}