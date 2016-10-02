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
#include "net_message.h"

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
	
	std::vector<NetMessage>				mIncomingClientMessages; // Messages from clients
	std::unordered_map<int, std::vector<NetMessage>> mIncomingServerMessages; // Messages from server
	std::unordered_map<int, std::vector<NetMessage>> mOutgoingClientMessages; // Messages to clients

	bool mIsServer = false;
	int mPort;

	std::vector<ClientConnection*> mClientConnections; // May connect to multiple servers
	ServerConnection* mServerConnection = nullptr;

	void handleIncomingServerMessage(int arg_Server, const char* arg_message);
	void handleIncomingClientMessage(int arg_client, const char* arg_message);

public:
	void SetServer();

	void SetPort(int arg_port);
	void ConnectToServer(const char* arg_host);
	void DisconnectFromServer(const char* arg_host);

	bool IsServer();

	void AddOutgoingMessage(NetMessage arg_message, int arg_socket = -1);

};


#endif