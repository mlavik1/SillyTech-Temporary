#include "net_message.h"

#include <sstream>
#include "st_assert.h"

NetMessage::NetMessage()
	: mMessageType(NetMessageType::Ignored), mMessageLength(0), mMessage("")
{
}

NetMessage::NetMessage(const char* arg_message)
{
	msgprefix_t prefix = *(reinterpret_cast<msgprefix_t*>((char*)arg_message));
	if (prefix != NetMessagePrefix)
	{
		NetMessage();
		return;
	}
	mMessageType = (NetMessageType)*(reinterpret_cast<msgtype_t*>((char*)arg_message + sizeof(msgprefix_t)));
	mMessageLength = *(reinterpret_cast<msglen_t*>((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t)));
	mMessage = std::string((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t), mMessageLength);
}

NetMessage::NetMessage(NetMessageType arg_type, msglen_t arg_length, const char* arg_message)
{
	mMessageType = arg_type;
	mMessageLength = arg_length;
	mMessage = std::string(arg_message, mMessageLength);
}

NetMessage::NetMessage(NetMessageType arg_type, std::string arg_message)
{
	mMessageType = arg_type;
	mMessageLength = arg_message.size();
	mMessage = arg_message;
}

NetMessage::~NetMessage()
{
}


std::string NetMessage::GetStringRepresentation()
{
	/*
	std::ostringstream oss;
	oss << mMessageType;
	oss << mMessageLength;
	oss << mMessage;

	return oss.str();*/

	std::ostringstream ss;

	char * chararr = const_cast<char *>(reinterpret_cast<const char *>(&NetMessagePrefix));
	for (std::size_t i = 0; i != sizeof(msgprefix_t); ++i)
		ss << chararr[i];

	chararr = reinterpret_cast<char *>(&mMessageType);
	for (std::size_t i = 0; i != sizeof(msgtype_t); ++i)
		ss << chararr[i];

	chararr = reinterpret_cast<char *>(&mMessageLength);
	for (std::size_t i = 0; i != sizeof(msglen_t); ++i)
		ss << chararr[i];

	chararr = const_cast<char *>(mMessage.c_str());
	for (std::size_t i = 0; i != (size_t)mMessageLength; ++i)
		ss << chararr[i];

	//__AssertComment(ss.le)

	return ss.str();

}
