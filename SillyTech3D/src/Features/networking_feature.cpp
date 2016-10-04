#include "networking_feature.h"
#include "replication_manager.h"
#include "lua_script_manager.h"

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
				if (pair.first == -1)
					mServerConnection->SendMessageToAll(msg.GetStringRepresentation().c_str(), 90/*msg.GetTotalLength()*/);
				else
					mServerConnection->SendMessage(pair.first, msg.GetStringRepresentation().c_str(), msg.GetTotalLength());
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
		connection->SetMessageCallback([&](const char* arg_message) -> void { handleIncomingServerMessage(connectionIndex, arg_message); });
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

void NetworkingFeature::handleIncomingServerMessage(int arg_Server, const char* arg_message)
{
	NetMessage netMessage(arg_message);

	if (netMessage.GetMessageType() == NetMessageType::Ignored)
	{
		LOG_WARNING() << "Received ignored message: " << arg_message;
	}

	else if (netMessage.GetMessageType() == NetMessageType::ObjectReplication)
	{
		ReplicationManager::Instance()->AddIncomingMessage(netMessage);
	}

	else if (netMessage.GetMessageType() == NetMessageType::LuaCall)
	{
		LuaScriptManager::Instance()->ExectureLine(netMessage.GetMessage().c_str());
	}
	
}

void NetworkingFeature::handleIncomingClientMessage(int arg_client, const char* arg_message)
{
	NetMessage netMessage(arg_message);

	LOG_INFO() << "Message from client " << arg_client << ": " << netMessage.GetStringRepresentation();

}


bool NetworkingFeature::IsServer()
{
	return mIsServer;
}

void NetworkingFeature::AddOutgoingMessage(NetMessage arg_message, int arg_socket)
{
	mOutgoingClientMessages[arg_socket].push_back(arg_message);
}