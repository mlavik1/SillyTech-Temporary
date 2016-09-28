#include "replication_manager.h"
#include "Engine/game_engine.h"

__ImplementSingleton(ReplicationManager)

ReplicationManager::ReplicationManager()
{
	__ConstructSingleton(ReplicationManager)

}


ReplicationManager::~ReplicationManager()
{
	__DestructSingleton(ReplicationManager)
}

void ReplicationManager::OnFrame()
{
	Manager::OnFrame();
}

void ReplicationManager::OnStart()
{
	Manager::OnStart();
}

void ReplicationManager::OnStop()
{
	Manager::OnStop();
}


void ReplicationManager::OnActivate()
{
	Manager::OnActivate();
}

void ReplicationManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

void ReplicationManager::AddIncomingMessage(std::string arg_message)
{
	mIncomingMessageQueue.push_back(arg_message);
}

void ReplicationManager::AddOutgoingMessage(std::string arg_message)
{
	mOutgoingMessageQueue.push_back(arg_message);
}

void ReplicationManager::SetReplicate(IReplicable *arg_object, bool arg_replicate)
{
	if (arg_replicate)
		mReplicatingObjects.push_back(arg_object);
	else
	{ // Remove:
		std::vector<IReplicable*>::iterator iter = mReplicatingObjects.begin();
		for (; iter != mReplicatingObjects.begin(); iter ++)
		{
			if (*iter._Ptr == arg_object)
			{
				mReplicatingObjects.erase(iter);
				break;
			}
		}
	}
}
