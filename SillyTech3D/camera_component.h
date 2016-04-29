#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "component.h"
#include "glm.hpp"
#include "viewport.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	typedef enum { ORTHOGRAPHIC = 1, PERSPECTIVE = 2 } CameraType;

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:	
	void	SetCameraType(CameraType arg_type);	
	void	SetViewport(Viewport arg_viewport);

	Viewport&					GetViewport();
	glm::mat4x4					GetViewMatrix();
	CameraComponent::CameraType GetCameraType();

private:
	CameraComponent::CameraType mCameraType;
	Viewport					mViewport;
};

#endif