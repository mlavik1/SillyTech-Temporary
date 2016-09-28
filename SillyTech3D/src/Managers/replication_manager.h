#ifndef ReplicationManager_H
#define ReplicationManager_H

#include "manager.h"
#include "singleton.h"
#include <vector>
#include "replication.h"


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

	std::vector<IReplicable*> mReplicatingObjects;

	std::vector<std::string> mIncomingMessageQueue;
	std::vector<std::string> mOutgoingMessageQueue;

public:
	void AddIncomingMessage(std::string arg_message);
	void AddOutgoingMessage(std::string arg_message);

	void SetReplicate(IReplicable *arg_object, bool arg_replicate);

};


#endif
