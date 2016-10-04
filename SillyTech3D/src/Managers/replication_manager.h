#ifndef ReplicationManager_H
#define ReplicationManager_H

#include "manager.h"
#include "singleton.h"
#include <vector>
#include "net_message.h"
#include "replication_types.h"
#include "timer.h"
#include <unordered_map>


class IReplicable; // fwd. decl.


class ReplicationManager : public Manager
{
	__DeclareSingleton(ReplicationManager)

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

private:
	ReplicationManager();
	~ReplicationManager();

	const float ReplicationDelay = 50.0f; // TEMP: Don't do this. But make sure clients are not spammed with messages
										// If too many messages are sent, clients will for some reason receive garbage messages??

	std::unordered_map<repid_t, IReplicable*> mReplicatingObjects;
	//std::vector<IReplicable*> mReplicatingObjects;

	std::vector<NetMessage> mIncomingMessageQueue;

	Timer mServerReplicationTimer;
	std::unordered_map<repid_t, IReplicable*>::iterator mReplicationIterator;


public:
	void AddIncomingMessage(NetMessage arg_message);

	repid_t SetReplicate(IReplicable *arg_object, bool arg_replicate);

};


#endif
