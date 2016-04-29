#include "graphics_feature.h"
#include "resource_manager.h"
#include "shader_res.h"
#include "shader.h"
#include "material_res.h"
#include "AntTweakBar.h"

__ImplementSingleton(GraphicsFeature)

GraphicsFeature::GraphicsFeature()
{
	mFeatureName = "GraphicsFeature";
	mDisplay = new GLDisplay();
	mGraphicsSystem = new GLGraphicsSystem();	// TODO: #if USING_OPENGL

	__ConstructSingleton(GraphicsFeature)
}

GraphicsFeature::~GraphicsFeature()
{
	__DestructSingleton(GraphicsFeature)
}

void GraphicsFeature::OnBeginFrame()
{
	mDisplay->Reshape();
	mGraphicsSystem->PrepareRender();

	Feature::OnBeginFrame();
}

void GraphicsFeature::OnEndFrame()
{
	Feature::OnEndFrame();
	mDisplay->SwapBuffers();
}

void GraphicsFeature::OnFrame()
{

if(mPostProcessRendering)
	mGraphicsSystem->BindMainFrameBuffer();

	Feature::OnFrame();	// Mesh renderers called here
	
	if (mPostProcessRendering)
	{
		GetDisplay()->Reshape();
		mGraphicsSystem->RenderMainFrameBuffer();
	}
	// Draw tweak bars
	//TwDraw();
}

void GraphicsFeature::OnStart()
{
	
	if (mPostProcessRendering)
	{
		LOG_INFO() << "Post process rendering enabled";
	}

	if (mPostProcessRendering)
		mGraphicsSystem->InitMainFrameBuffer(mDisplay->GetScreenWidth(), mDisplay->GetScreenHeight());

	Feature::OnStart();
}

void GraphicsFeature::OnStop()
{
	Feature::OnStop();
}

void GraphicsFeature::OnActivate()
{
	mDisplay->InitWindow("SillyTech 3D", 250, 150, 800, 600);
	mDisplay->PositionConsoleWindow(0,0);
	mDisplay->ResizeConsoleWindow(500,550);
	mGraphicsSystem->Initialise();

	// TODO: Move this!    ShaderFactory!
	// add default sahders 
	Shader *vs = new Shader("Resources/Shaders/default_shader.vs", SHADER_TYPE_VERTEXSHADER);
	ShaderRes *vsRes = new ShaderRes(vs);
	ResourceManager<ShaderRes>::Instance()->AddResource(vsRes);
	Shader *gs = new Shader("Resources/Shaders/default_shader.gs", SHADER_TYPE_GEOMETRYSHADER);
	ShaderRes *gsRes = new ShaderRes(gs);
	ResourceManager<ShaderRes>::Instance()->AddResource(gsRes);
	Shader *fs = new Shader("Resources/Shaders/default_shader.fs", SHADER_TYPE_FRAGMENTSHADER);
	ShaderRes *fsRes = new ShaderRes(fs);
	ResourceManager<ShaderRes>::Instance()->AddResource(fsRes);

	Shader *vspost = new Shader("Resources/Shaders/default_postprocess.vs", SHADER_TYPE_VERTEXSHADER);
	ShaderRes *vsResPost = new ShaderRes(vspost);
	ResourceManager<ShaderRes>::Instance()->AddResource(vsResPost);
	Shader *fspost = new Shader("Resources/Shaders/default_postprocess.fs", SHADER_TYPE_FRAGMENTSHADER);
	ShaderRes *fsResPost = new ShaderRes(fspost);
	ResourceManager<ShaderRes>::Instance()->AddResource(fsResPost);

	Feature::OnActivate();
}

void GraphicsFeature::OnDeactivate()
{
	Feature::OnDeactivate();
}

Display *GraphicsFeature::GetDisplay()
{
	return mDisplay;
}

void GraphicsFeature::SetPostProcessRendering(bool arg_enabled)
{
	mPostProcessRendering = true;
}

GLGraphicsSystem *GraphicsFeature::GetGraphicsSystem()
{
	return mGraphicsSystem;
}