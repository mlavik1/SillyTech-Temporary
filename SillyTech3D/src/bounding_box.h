#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "mesh_data.h"
#include <glm.hpp>
//class Mesh;

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	void		SetMeshData(MeshData *arg_meshdata);
	void		SetBounds(float arg_x, float arg_y, float arg_z);

	MeshData*	GetMeshData();	
	glm::vec3	GetBounds();

private:
	MeshData*	mMeshData;
	glm::vec3	mBounds;
};

#endif