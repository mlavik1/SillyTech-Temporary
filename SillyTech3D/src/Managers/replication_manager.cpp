#include "replication_manager.h"
#include "Engine/game_engine.h"
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

	if (!mServerReplicationTimer.HasStarted())
		mServerReplicationTimer.Start();

	if (NetworkingFeature::Instance()->IsServer() && mServerReplicationTimer.GetTime() > ReplicationDelay)
	{
		mServerReplicationTimer.GetTimeAndRestart();

		for (IReplicable* repl : mReplicatingObjects)
		{
			// TODO: Use ID !!!!!!!
			NetMessage netMessage(NetMessageType::ObjectReplication, 90/*NONONO!!!*/, repl->GetReplicatedData().str().c_str());

			NetworkingFeature::Instance()->AddOutgoingMessage(netMessage);

			// TODO: Use ID
			//NetworkingFeature::Instance()->AddOutgoingMessage(repl->GetReplicatedData().str());
		}
	}

	for (NetMessage &netMessage : mIncomingMessageQueue) // TODO: Store NetMessage (not string) in list
	{
		int i = 0;
		if (mReplicatingObjects.size() > 0)
			mReplicatingObjects[0]->SetReplicatedData(netMessage.GetMessage().c_str(), i);
	}

	mIncomingMessageQueue.clear();

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

void ReplicationManager::AddIncomingMessage(NetMessage arg_message)
{
	mIncomingMessageQueue.push_back(arg_message);
}

repid_t ReplicationManager::SetReplicate(IReplicable *arg_object, bool arg_replicate)
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

	return repid_none; // TODO: Generate unique ID, and add to map!

}
