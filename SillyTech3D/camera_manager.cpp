#include "camera_manager.h"

#include "camera_component.h"

__ImplementSingleton(CameraManager)

CameraManager::CameraManager()
{
	__ConstructSingleton(CameraManager)

}


CameraManager::~CameraManager()
{
	__DestructSingleton(CameraManager)
}



void CameraManager::OnBeginFrame()
{
	Manager::OnBeginFrame();

}

void CameraManager::OnEndFrame()
{
	Manager::OnEndFrame();

}

void CameraManager::OnFrame()
{
	Manager::OnFrame();
}

void CameraManager::OnStart()
{
	Manager::OnStart();
}

void CameraManager::OnStop()
{
	Manager::OnStop();

}

void CameraManager::OnActivate()
{
	Manager::OnActivate();

}

void CameraManager::OnDeactivate()
{
	Manager::OnDeactivate();
}

void CameraManager::AttachCameraComponent(CameraComponent *arg_camcomp)
{
	mCameraComponents.push_back(arg_camcomp);
}

void CameraManager::DetachCameraComponent(CameraComponent *arg_camcomp)
{
	for (int i = 0; i < mCameraComponents.size(); i++)
	{
		if (mCameraComponents.at(i) == arg_camcomp)
		{
			mCameraComponents.erase(mCameraComponents.begin() + i);
			return;
		}
	}
		

}

int CameraManager::GetNumCameraComponents()
{
	return mCameraComponents.size();
}

CameraComponent *CameraManager::GetCameraComponent(int cam_index)
{
	if (cam_index > mCameraComponents.size() - 1)
		return 0;
	else
		return mCameraComponents.at(cam_index);
}

CameraComponent *CameraManager::GetMainCameraComponent()
{
	/* TODO: Do something more clever   */
	// allow setting/ main camera???
	return mCameraComponents.at(0);
}