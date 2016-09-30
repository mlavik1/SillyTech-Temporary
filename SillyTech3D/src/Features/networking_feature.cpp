#include "networking_feature.h"
#include "replication_manager.h"

__ImplementSingleton(NetworkingFeature)

NetworkingFeature::NetworkingFeature()
{
	mFeatureName = "NetworkingFeature";

	SDLNet_Init();

	mPort = 1234;

	__ConstructSingleton(NetworkingFeature)
}

NetworkingFeature::~NetworkingFeature()
{
	__DestructSingleton(NetworkingFeature)
}

void NetworkingFeature::OnFrame()
{
	Feature::OnFrame();

	if (mServerConnection != nullptr && mIsServer)
	{
		mServerConnection->FetchNewMessages();


		for (auto& pair : mOutgoingMessages)
		{
			for (std::string msg : pair.second)
			{
				if (pair.first == -1)
					mServerConnection->SendMessageToAll(msg.c_str(), msg.size());
				else
					mServerConnection->SendMessage(pair.first, msg.c_str(), msg.size());
			}
		}
	}
		
	else if (mClientConnection != nullptr && !mIsServer)
	{
		mClientConnection->FetchNewMessages();
	}
		

	mIncomingMessages.clear();
	mOutgoingMessages.clear();


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

void NetworkingFeature::SetClient()
{
	mIsServer = false;
	if (mClientConnection == nullptr)
		mClientConnection = new ClientConnection();

	mClientConnection->SetMessageCallback([&](const char* arg_message) -> void { handleIncomingMessage(arg_message); });
}

void NetworkingFeature::SetPort(int arg_port)
{
	mPort = arg_port;

	if (mServerConnection != nullptr && mServerConnection->IsConnected())
		mServerConnection->Connect(mPort);

	if (mClientConnection != nullptr && mClientConnection->IsConnected())
		mClientConnection->Connect(mHost.c_str(), mPort);
}

void NetworkingFeature::ConnectToServer(const char* arg_host)
{
	if (mClientConnection != nullptr)
	{
		mHost = arg_host;
		bool connected = mClientConnection->Connect(mHost.c_str(), mPort);
		if (connected)
			mClientConnection->SendMessage("Hei"); // TEMP! Send a proper request!
		else
			LOG_ERROR() << "Failed to connect to host:" << arg_host;
	}
}

void NetworkingFeature::SendMessages()
{
	
}

void NetworkingFeature::ProcessMessages()
{
}

void NetworkingFeature::handleIncomingMessage(const char* arg_message)
{
	//mIncomingMessages[arg_socket].push_back(arg_message);

	//if (!mIsServer)
	//	ReplicationManager::Instance()->AddIncomingMessage(arg_message); // !!! Can't just cast it to string! Resulting string is then empty
	if (!mIsServer)
		ReplicationManager::Instance()->ReplicationTest(arg_message);
}

bool NetworkingFeature::IsServer()
{
	return mIsServer;
}

void NetworkingFeature::AddOutgoingMessage(std::string arg_message, int arg_socket)
{
	mOutgoingMessages[arg_socket].push_back(arg_message);
}