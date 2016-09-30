#include "replication_manager.h"
#include "Engine/game_engine.h"
#include "replication.h"
#include "networking_feature.h"
#include <sstream>

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

	// TODO: Use prefix in messages, defining the Message Type (make NetworkMessageType enum)

	if (NetworkingFeature::Instance()->IsServer())
	{
		for (IReplicable* repl : mReplicatingObjects)
		{
			// TODO: Use ID
			NetworkingFeature::Instance()->AddOutgoingMessage(repl->GetReplicatedData().str());
		}
	}

	for (std::string msg : mIncomingMessageQueue)
	{
		int i = 0;
		if (mReplicatingObjects.size() > 0)
			mReplicatingObjects[0]->SetReplicatedData(msg.c_str(), i);
	}

	mIncomingMessageQueue.clear();
	mOutgoingMessageQueue.clear();

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


void ReplicationManager::ReplicationTest(const char* arg_message)
{
	int i = 0;
	if (mReplicatingObjects.size() > 0)
		mReplicatingObjects[0]->SetReplicatedData(arg_message, i);
}