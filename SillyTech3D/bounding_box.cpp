#include "bounding_box.h"

#include "mesh.h"

BoundingBox::BoundingBox()
{
	mMeshData = 0;
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::SetMeshData(MeshData *arg_meshdata)
{
	mMeshData = arg_meshdata;
}

MeshData *BoundingBox::GetMeshData()
{
	return mMeshData;
}

void BoundingBox::SetBounds(float arg_x, float arg_y, float arg_z)
{
	mBounds = glm::vec3(arg_x, arg_y, arg_z);
}

glm::vec3 BoundingBox::GetBounds()
{
	return mBounds;
}