#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <vector>

class CameraComponent;

class CameraManager : public Manager
{
	__DeclareSingleton(CameraManager)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	void AttachCameraComponent(CameraComponent *arg_camcomp);
	void DetachCameraComponent(CameraComponent *arg_camcomp);

	int					GetNumCameraComponents();
	CameraComponent*	GetCameraComponent(int cam_index = 0);
	CameraComponent*	GetMainCameraComponent();

private:
	CameraManager();
	~CameraManager();

	std::vector<CameraComponent *> mCameraComponents;
};

#endif