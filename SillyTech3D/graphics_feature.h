#ifndef GRAPHICSFEATURE_H
#define GRAPHICSFEATURE_H

#include "feature.h"
#include "singleton.h"
#include "gl_display.h"
#include "graphics_system.h"
#include "gl_graphics_system.h"
#include "shader_program.h"

class CameraComponent;

class GraphicsFeature : public Feature
{
	__DeclareSingleton(GraphicsFeature)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	Display *GetDisplay();

	void SetPostProcessRendering(bool arg_enabled);

	GLGraphicsSystem *GetGraphicsSystem();


private:
	GraphicsFeature();
	~GraphicsFeature();
	Display *mDisplay;
	GLGraphicsSystem *mGraphicsSystem;

	bool mPostProcessRendering;
};

#endif