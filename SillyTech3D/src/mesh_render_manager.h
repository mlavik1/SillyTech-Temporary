#ifndef MESHRENDERMANAGER_H
#define MESHRENDERMANAGER_H

#include "manager.h"
#include "singleton.h"
#include <vector>

#include "mesh_render_component.h"
#include "light_component.h"

//class MeshRenderComponent;

class MeshRenderManager : public Manager
{
	__DeclareSingleton(MeshRenderManager)

public:
	void OnBeginFrame() override;
	void OnFrame() override;
	void OnEndFrame() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnStart() override;
	void OnStop() override;

	void AttachMeshRenderComponent(MeshRenderComponent *arg_comp);
	void RemoveMeshRenderComponent(MeshRenderComponent *arg_comp);
	void AttachLightComponent(LightComponent *arg_comp);
	void RemoveLightComponent(LightComponent *arg_comp);

private:
	MeshRenderManager();
	~MeshRenderManager();
	
private:
	std::vector<MeshRenderComponent*> mMeshRenderComponents;
	std::vector<LightComponent*> mLightComponents;

	GLuint uniformBufferObject;

public:
	int mDrawCalls;
	int mDrawCallsSkipped;
};


#endif