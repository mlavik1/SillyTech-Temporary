#include "mesh_res.h"
#include "debug.h"
#include "mesh.h"

MeshRes::MeshRes(const char *arg_name) : Resource::Resource(arg_name, "")
{
	
	//Reload();

}

MeshRes::~MeshRes()
{

}


void MeshRes::Reload()
{
	Resource::Reload();

	mMesh->BufferMeshData();
}

void MeshRes::SetMesh(Mesh *arg_mesh)
{
	mMesh = arg_mesh;
}

Mesh *MeshRes::GetMesh()
{
	return mMesh;
}

