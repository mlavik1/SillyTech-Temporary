#include "networking_feature.h"

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
		mServerConnection->FetchNewMessages();
	else if (mClientConnection != nullptr && !mIsServer)
		mClientConnection->FetchNewMessages();
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
}

void NetworkingFeature::SetClient()
{
	mIsServer = false;
	if (mClientConnection == nullptr)
		mClientConnection = new ClientConnection();
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
	if (mClientConnection == nullptr)
	{
		mHost = arg_host;
		mClientConnection->Connect(mHost.c_str(), mPort);
	}
}