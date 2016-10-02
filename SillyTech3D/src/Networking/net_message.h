#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <string>
#include <types.h>
#include "net_message_type.h"

typedef uint16_t msgprefix_t;
typedef uint8_t msgtype_t;
typedef uint16_t msglen_t;

class NetMessage
{
private:
	NetMessageType		mMessageType;
	msglen_t			mMessageLength;
	std::string			mMessage;

	const msgprefix_t NetMessagePrefix = 52134;

public:
	NetMessage();
	NetMessage(const char* arg_message);
	NetMessage(NetMessageType arg_type, msglen_t arg_length, const char* arg_message);
	NetMessage(NetMessageType arg_type, std::string arg_message);
	~NetMessage();

	inline NetMessageType	GetMessageType()		{ return mMessageType; }
	inline msglen_t			GetMessageLength()		{ return mMessageLength; }
	inline std::string		GetMessage()			{ return mMessage; }
	inline size_t			GetTotalLength()		{ return GetMessageLength() + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t); }

	std::string GetStringRepresentation();

};


#endif // #ifndef NETMESSAGE_H