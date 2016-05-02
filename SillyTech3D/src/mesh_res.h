#ifndef MESHRES_H
#define MESHRES_H

#include "resource.h"
#include "mesh.h"

class MeshRes : public Resource
{
public:
	MeshRes(const char *arg_name);
	~MeshRes();

private:
	Mesh *mMesh;

public:
	void Reload() override;

	void SetMesh(Mesh *arg_mesh);
	Mesh *GetMesh();


};


#endif