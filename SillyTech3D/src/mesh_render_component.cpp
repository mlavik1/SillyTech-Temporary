#include "mesh_render_component.h"
#include "resource_manager.h"
#include "mesh_res.h"
#include "material_res.h"
#include "mesh.h"
#include "st_assert.h"
#include "mesh_render_manager.h"
#include "bounding_box_factory.h"

MeshRenderComponent::MeshRenderComponent()
{
	mIsActive = false;
	mMeshID = "";
	mBoundingBox = 0;
}

MeshRenderComponent::~MeshRenderComponent()
{

}



void MeshRenderComponent::OnBeginFrame()
{
	Component::OnBeginFrame();
}

void MeshRenderComponent::OnEndFrame()
{
	Component::OnEndFrame();
}

void MeshRenderComponent::OnFrame()
{
	Component::OnFrame();
}

void MeshRenderComponent::OnStart()
{
	Component::OnStart();

	

}

void MeshRenderComponent::OnStop()
{
	Component::OnStop();
}

void MeshRenderComponent::OnActivate()
{
	Component::OnActivate();

	MeshRes *meshRes = ResourceManager<MeshRes>::Instance()->GetResource(mMeshID.c_str());
	if (!meshRes)
		LOG_WARNING() << "RenderComponent could not find the MeshRes for: " << mMeshID;

	MaterialRes *materialRes = ResourceManager<MaterialRes>::Instance()->GetResource(mMaterialID.c_str());
	if (!materialRes)
		LOG_WARNING() << "RenderComponent could not find the MaterialRes for: " << mMaterialID;

	MeshRenderManager::Instance()->AttachMeshRenderComponent(this);

	CreateBoundingBox();

}

void MeshRenderComponent::OnDeactivate()
{
	Component::OnDeactivate();

	MeshRenderManager::Instance()->RemoveMeshRenderComponent(this);

}


void MeshRenderComponent::SetMeshID(const char* arg_id)
{
	mMeshID = arg_id;

}

std::string MeshRenderComponent::GetMeshID()
{
	return mMeshID;
}

void MeshRenderComponent::SetMaterialID(const char* arg_id)
{
	mMaterialID = arg_id;
}

std::string MeshRenderComponent::GetMaterialID()
{
	return mMaterialID;
}

Material *MeshRenderComponent::GetMaterial()
{
	MaterialRes *res = ResourceManager<MaterialRes>::Instance()->GetResource(mMaterialID.c_str());
	if (res)
		return res->GetMaterial();
	else
		return 0;
}

BoundingBox *MeshRenderComponent::GetBoundingBox()
{
	return mBoundingBox;
}

void MeshRenderComponent::CreateBoundingBox()
{
	if (mMeshID != "" && mParent)
	{
		MeshRes *res = ResourceManager<MeshRes>::Instance()->GetResource(mMeshID.c_str());
		if (res)
		{
			delete mBoundingBox;
			mBoundingBox = BoundingBoxFactory::CreateBoundingBox(mParent);
		}
			
	}
}