#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "component.h"
#include "glm.hpp"

class LightComponent : public Component
{
	friend class EditorGUI;
public:
	LightComponent();
	~LightComponent();

	typedef enum { POINT_LIGHT = 1, DIRECTIONAL_LIGHT = 2, SPOT_LIGHT = 3, AREA_LIGHT = 4 } LightType;

public:
	void OnFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

public:
	void SetLightType(LightType arg_type);
	LightComponent::LightType GetLightType();

	void SetAmbientColour(glm::vec3 arg_colour);
	void SetDiffuseColour(glm::vec3 arg_colour);
	void SetSpecularColour(glm::vec3 arg_colour);
	glm::vec3 GetAmbientColour();
	glm::vec3 GetDiffuseColour();
	glm::vec3 GetSpecularColour();

private:
	LightComponent::LightType mLightType;

	glm::vec3 mAmbientColour;
	glm::vec3 mDiffuseColour;
	glm::vec3 mSpecularColour;
};

#endif