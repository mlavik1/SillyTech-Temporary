#ifndef NETWORKINGFEATURE_H
#define NETWORKINGFEATURE_H

#include "feature.h"
#include "singleton.h"
#include <SDL_net.h>
#include <vector>
#include "server_connection.h"
#include "client_connection.h"

class NetworkingFeature : public Feature
{
	__DeclareSingleton(NetworkingFeature)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;


private:
	NetworkingFeature();
	~NetworkingFeature();
	
	std::vector<std::string> mIncomingMessages;

	bool mIsServer;
	int mPort;
	std::string mHost;

	ClientConnection* mClientConnection = nullptr;
	ServerConnection* mServerConnection = nullptr;

public:
	void SetServer();
	void SetClient();

	void SetPort(int arg_port);
	void ConnectToServer(const char* arg_host);

};


#endif