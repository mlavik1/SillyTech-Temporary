#include "replication_manager.h"
#include "Engine/game_engine.h"
#include "networking_feature.h"
#include <sstream>

__ImplementSingleton(ReplicationManager)

ReplicationManager::ReplicationManager()
{
	__ConstructSingleton(ReplicationManager)


		mReplicationIterator = mReplicatingObjects.begin();
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

		if (mReplicationIterator == mReplicatingObjects.end())
			mReplicationIterator = mReplicatingObjects.begin();
		//for (; mReplicationIterator != mReplicatingObjects.end(); mReplicationIterator++)
		if (mReplicationIterator != mReplicatingObjects.end())
		{
			IReplicable* repl = mReplicationIterator._Ptr->_Myval.second;

			std::ostringstream oss;
			repid_t repID = repl->GetReplicationID();
			for (size_t i = 0; i < sizeof(repid_t); i++)
				oss << reinterpret_cast<char *>(&repID)[i];
			oss << repl->GetReplicatedData().str();
			NetMessage netMessage(NetMessageType::ObjectReplication, 90/*NONONO!!!*/, oss.str().c_str());

			NetworkingFeature::Instance()->AddOutgoingMessage(netMessage);
		} mReplicationIterator ++ ; // temp - TODO: check if we need to replicate
	}

	for (NetMessage &netMessage : mIncomingMessageQueue) // TODO: Store NetMessage (not string) in list
	{
		std::string msgg = netMessage.GetMessage();
		const char* msg = msgg.c_str();
		repid_t repID = *(reinterpret_cast<repid_t*>((char*)msg));

		if (mReplicatingObjects.find(repID) != mReplicatingObjects.end())
		{
			int i = 0;
			mReplicatingObjects[repID]->SetReplicatedData(msg + sizeof(repid_t), i);
		}
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
	{
		repid_t repID = repid_none;
		std::unordered_map<repid_t, IReplicable*>::iterator iter = mReplicatingObjects.begin();
		for (; iter != mReplicatingObjects.end(); iter++)
		{
			repid_t curr = iter._Ptr->_Myval.first;
			if (curr > repID)
				repID = curr;
		}
		repID++;
		arg_object->SetReplicationID(repID);
		mReplicatingObjects.insert(std::pair<repid_t, IReplicable*>(repID, arg_object));
		return repID;
	}
	else
	{ // Remove:
		std::unordered_map<repid_t, IReplicable*>::iterator iter = mReplicatingObjects.begin();
		for (; iter != mReplicatingObjects.begin(); iter ++)
		{
			if (iter._Ptr->_Myval.second == arg_object)
			{
				mReplicatingObjects.erase(iter);
				break;
			}
		}
		return repid_none;
	}

}
