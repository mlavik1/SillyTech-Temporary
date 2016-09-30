#ifndef NETWORKINGFEATURE_H
#define NETWORKINGFEATURE_H

#include "feature.h"
#include "singleton.h"
#include <SDL_net.h>
#include <vector>
#include "server_connection.h"
#include "client_connection.h"
#include <unordered_map>
#include <string>

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
	
	std::unordered_map<int, std::vector<std::string>> mIncomingMessages;
	std::unordered_map<int, std::vector<std::string>> mOutgoingMessages;

	bool mIsServer;
	int mPort;
	std::string mHost;

	ClientConnection* mClientConnection = nullptr;
	ServerConnection* mServerConnection = nullptr;

	void handleIncomingMessage(const char* arg_message);

public:
	void SetServer();
	void SetClient();

	void SendMessages();
	void ProcessMessages();

	void SetPort(int arg_port);
	void ConnectToServer(const char* arg_host);

	bool IsServer();

	void AddOutgoingMessage(std::string arg_message, int arg_socket = -1);

};


#endif