#include "networking_feature.h"
#include "replication_manager.h"
#include "lua_script_manager.h"
#include "st_assert.h"

__ImplementSingleton(NetworkingFeature)

NetworkingFeature::NetworkingFeature()
{
	mFeatureName = "NetworkingFeature";

	SDLNet_Init();

	mPort = 1334;

	__ConstructSingleton(NetworkingFeature)
}

NetworkingFeature::~NetworkingFeature()
{
	__DestructSingleton(NetworkingFeature)

	if (mServerConnection != nullptr)
	{
		mServerConnection->Close();
		delete(mServerConnection);
	}

	for (ClientConnection* conn : mClientConnections)
	{
		conn->Close();
		delete(conn);
	}

	SDLNet_Quit();

}

void NetworkingFeature::OnFrame()
{
	Feature::OnFrame();

	if (mServerConnection != nullptr && mIsServer)
	{
		mServerConnection->FetchNewMessages();


		for (auto& pair : mOutgoingClientMessages)
		{
			for (NetMessage &msg : pair.second)
			{
				for (int i = 0; i < msg.GetMessagePartCount(); i++)
				{
					std::string msgStr = msg.GetStringRepresentation(i);
					if (pair.first == -1)
						mServerConnection->SendMessageToAll(msgStr.c_str(), msgStr.length());
					else
						mServerConnection->SendMessage(pair.first, msgStr.c_str(), msgStr.length());
				}
			}
		}
	}
		
	else if (mClientConnections.size() > 0 /*&& !mIsServer*/)
	{
		for (ClientConnection* conn : mClientConnections)
		{
			conn->FetchNewMessages();
		}
	}
		
	mIncomingServerMessages.clear();
	mOutgoingClientMessages.clear();


	// We may manually add new incoming/outgoing messages after this
}

void NetworkingFeature::OnStart()
{
	Feature::OnStart();
}

void NetworkingFeature::OnStop()
{
	Feature::OnStop();
}

void NetworkingFeature::OnActivate()
{
	Feature::OnActivate();
}

void NetworkingFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}

void NetworkingFeature::SetServer()
{
	mIsServer = true;
	if (mServerConnection == nullptr)
		mServerConnection = new ServerConnection(50);

	mServerConnection->Connect(mPort);

	//mServerConnection->SetMessageCallback(&NetworkingFeature::handleIncomingMessage);
	
}

void NetworkingFeature::SetPort(int arg_port)
{
	mPort = arg_port;

	if (mServerConnection != nullptr && mServerConnection->IsConnected())
		mServerConnection->Connect(mPort);

}

void NetworkingFeature::ConnectToServer(const char* arg_host)
{
	ClientConnection* connection = nullptr;
	size_t connectionIndex = 0;

	if (mClientConnections.size() > 0)
	{
		for (size_t i = 0; i < mClientConnections.size(); i++)
		{
			ClientConnection* conn = mClientConnections[i];
			if (conn->GetHost() == std::string(arg_host))
			{
				connection = conn;
				connectionIndex = i;
			}
		}
	}

	if (connection == nullptr) // Create new connection, and connect
	{
		connectionIndex = mClientConnections.size();
		connection = new ClientConnection();
		connection->SetMessageCallback([&](const char* arg_message, int arg_bytes) -> void { handleIncomingServerMessage(connectionIndex, arg_message, arg_bytes); });
		bool connected = connection->Connect(arg_host, mPort);
		if (connected)
		{
			mClientConnections.push_back(connection);
			connection->SendMessage("Hei"); // TEMP! Send a proper request!
		}
		else
		{
			LOG_ERROR() << "Failed to connect to host:" << arg_host;
			
		}
			
	}
}

void NetworkingFeature::DisconnectFromServer(const char* arg_host)
{

}

void NetworkingFeature::handleIncomingServerMessage(int arg_Server, const char* arg_message, int arg_bytes)
{
	NetMessage incomingMessage(arg_message);
	
	if (incomingMessage.GetMessageType() == NetMessageType::Ignored)
	{
		LOG_WARNING() << "Received ignored message: " << arg_message;
		return;
	}


	if (incomingMessage.GetMessagePartCount() > 1 && (mRemainingMessageParts == 0 || mIncompleteMessage.GetMessageType() != incomingMessage.GetMessageType() || mIncompleteMessage.GetMessageLength() != incomingMessage.GetTotalLength()))
	{
		mRemainingMessageParts = incomingMessage.GetMessagePartCount() - 1;
		mIncompleteMessage = incomingMessage;
		mRemainingMessageParts--;
		return;
	}

	else if (mRemainingMessageParts > 0) // merge messages
	{
		__AssertComment(mIncompleteMessage.GetMessageType() == incomingMessage.GetMessageType() && mIncompleteMessage.GetMessageLength() == incomingMessage.GetTotalLength(), "NetMessage mismatch");
	
		mIncompleteMessage.AppendMessage(incomingMessage.GetMessage());
		mRemainingMessageParts--;

		if (mRemainingMessageParts > 0)
			return;
	}
	NetMessage& netMessage = (incomingMessage.GetMessagePartCount() > 1) ? mIncompleteMessage : incomingMessage;
	

	
	if (netMessage.GetMessageType() == NetMessageType::ObjectReplication)
	{
		ReplicationManager::Instance()->AddIncomingMessage(netMessage);
	}

	else if (netMessage.GetMessageType() == NetMessageType::LuaCall)
	{
		LuaScriptManager::Instance()->ExectureLine(netMessage.GetMessage().c_str());
	}
	
}

void NetworkingFeature::handleIncomingClientMessage(int arg_client, const char* arg_message, int arg_bytes)
{
	NetMessage netMessage(arg_message);

	LOG_INFO() << "Message from client " << arg_client << ": " << netMessage.GetMessage();

}


bool NetworkingFeature::IsServer()
{
	return mIsServer;
}

void NetworkingFeature::AddOutgoingMessage(NetMessage arg_message, int arg_socket)
{
	mOutgoingClientMessages[arg_socket].push_back(arg_message);
}