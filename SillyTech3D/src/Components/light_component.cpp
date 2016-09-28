#include "light_component.h"

#include "mesh_render_manager.h"


LightComponent::LightComponent() : Component()
{
	SetLightType(LightType::POINT_LIGHT);
}

LightComponent::~LightComponent()
{

}


void LightComponent::OnFrame()
{
	Component::OnFrame();
}

void LightComponent::OnStart()
{
	Component::OnStart();
}

void LightComponent::OnStop()
{
	Component::OnStop();
}

void LightComponent::OnActivate()
{
	Component::OnActivate();
	MeshRenderManager::Instance()->AttachLightComponent(this);
}

void LightComponent::OnDeactivate()
{
	Component::OnDeactivate();
	MeshRenderManager::Instance()->RemoveLightComponent(this);
}

void LightComponent::SetLightType(LightType arg_type)
{
	mLightType = arg_type;
}

LightComponent::LightType LightComponent::GetLightType()
{
	return mLightType;
}


void LightComponent::SetAmbientColour(glm::vec3 arg_colour)
{
	mAmbientColour = arg_colour;
}

void LightComponent::SetDiffuseColour(glm::vec3 arg_colour)
{
	mDiffuseColour = arg_colour;
}

void LightComponent::SetSpecularColour(glm::vec3 arg_colour)
{
	mSpecularColour = arg_colour;
}

glm::vec3 LightComponent::GetAmbientColour()
{
	return mAmbientColour;
}

glm::vec3 LightComponent::GetDiffuseColour()
{
	return mDiffuseColour;
}

glm::vec3 LightComponent::GetSpecularColour()
{
	return mSpecularColour;
}