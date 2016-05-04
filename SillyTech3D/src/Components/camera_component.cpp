#include "camera_component.h"
#include "actor.h"
#include "camera_manager.h"

CameraComponent::CameraComponent() : mViewport(0.0f,0.0f,1.0f,1.0f)
{
	Component::Component();

	SetCameraType(CameraType::PERSPECTIVE);
}

CameraComponent::~CameraComponent()
{
	Component::~Component();
}



void CameraComponent::OnBeginFrame()
{
	Component::OnBeginFrame();
}

void CameraComponent::OnEndFrame()
{
	Component::OnEndFrame();
}

void CameraComponent::OnFrame()
{
	Component::OnFrame();
}

void CameraComponent::OnStart()
{
	Component::OnStart();
}

void CameraComponent::OnStop()
{
	Component::OnStop();
}

void CameraComponent::OnActivate()
{
	Component::OnActivate();
	CameraManager::Instance()->AttachCameraComponent(this);

}

void CameraComponent::OnDeactivate()
{
	Component::OnDeactivate();
	CameraManager::Instance()->DetachCameraComponent(this);
}

glm::mat4x4 CameraComponent::GetViewMatrix()
{
	glm::vec3 pos = mParent->GetTransform().GetGlobalPosition();

	glm::mat4 Mc = glm::lookAt(pos, pos + mParent->GetTransform().Forward(), mParent->GetTransform().Up());

	glm::mat4 mv = mParent->GetTransform().GetGlobalModelMatrix();
	glm::vec3 u = glm::vec3(mv[1][0], mv[1][1], mv[1][2]);
	glm::vec3 f = glm::vec3(mv[2][0], mv[2][1], mv[2][2])*-1.0f;

	pos = glm::vec3(mv[3][0], mv[3][1], mv[3][2]);

	Mc = glm::lookAt(pos, pos + f, u);


	/*
	glm::mat4 mv = mParent->GetTransform().GetGlobalModelMatrix();
	glm::mat3 tmp(mv);
	tmp = tmp;
	Mc = glm::mat4(tmp);
	Mc[3][3] = 1.0f;

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), mParent->GetTransform().GetGlobalPosition());
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), mParent->GetTransform().GetGlobalScale());
	Mc = transMat * Mc * scaleMat;*/
	//if (mParent->GetParent())
	//	Mc =  mParent->GetTransform().GetGlobalRotation() * Mc;

	return Mc;
}

void CameraComponent::SetCameraType(CameraType arg_type)
{
	mCameraType = arg_type;
}

CameraComponent::CameraType CameraComponent::GetCameraType()
{
	return mCameraType;
}

void CameraComponent::SetViewport(Viewport arg_viewport)
{
	mViewport = arg_viewport;
}

Viewport &CameraComponent::GetViewport()
{
	return mViewport;
}