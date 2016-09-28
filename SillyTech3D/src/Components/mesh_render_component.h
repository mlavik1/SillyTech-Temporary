#ifndef MESHRENDERCOMPONENT_H
#define MESHRENDERCOMPONENT_H

#include "component.h"
#include <string>
#include "material.h"
#include "mesh_data.h"
#include "bounding_box.h"

class MeshRenderComponent : public Component
{
public:
	virtual void OnFrame() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnStart() override;
	virtual void OnStop() override;

	void				SetMeshID(const char* arg_id);
	std::string			GetMeshID();
	void				SetMaterialID(const char* arg_id);
	std::string			GetMaterialID();
	Material*			GetMaterial();
	BoundingBox*		GetBoundingBox();
	void				CreateBoundingBox();

public:
	MeshRenderComponent();
	~MeshRenderComponent();

private:
	std::string		mMeshID;
	std::string		mMaterialID;
	BoundingBox*	mBoundingBox; // bounding box of this mesh and all children (also see Mesh::mBoundingBox)

};


#endif