#include "mesh.h"
#include "bounding_box_factory.h"
#include "debug.h"

Mesh::Mesh() : mVBO(0), mNBO(0), mTBO(0), mIBO(0), mMeshData(0)
{
	mRefCount = 0;
}

Mesh::~Mesh()
{

}

void Mesh::BufferMeshData()
{
	// TODO: Buffer VBO, NBO, TBO; IBO   (through GraphicsSystem/GraphicsFeature)

	if (!mMeshData)
		LOG_ERROR() << "Trying to buffer Mesh that has no MeshData";
	if (mMeshData->mVertices.empty())
		LOG_ERROR() << "Mesh has no vertices. Cnanot buffer";
	if (mMeshData->mNormals.empty())
		LOG_ERROR() << "Mesh has no normals. Cnanot buffer";
	if (mMeshData->mIndices.empty())
		LOG_ERROR() << "Mesh has no indices. Cnanot buffer";
	//if (mMeshData->mTexCoords.empty())
	//	LOG_ERROR() << "Mesh has no texcoords. Cnanot buffer";
	
	// vertices
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mMeshData->mVertices.size() * sizeof(glm::vec3), &mMeshData->mVertices.front(), GL_STATIC_DRAW);

	// normals
	glGenBuffers(1, &mNBO);
	glBindBuffer(GL_ARRAY_BUFFER, mNBO);
	glBufferData(GL_ARRAY_BUFFER, mMeshData->mNormals.size() * sizeof(glm::vec3), &mMeshData->mNormals.front(), GL_STATIC_DRAW);

	// texture coords
	if (!mMeshData->mTexCoords.empty())
	{		
		glGenBuffers(1, &mTBO);
		glBindBuffer(GL_ARRAY_BUFFER, mTBO);
		glBufferData(GL_ARRAY_BUFFER, mMeshData->mTexCoords.size() * sizeof(glm::vec2), &mMeshData->mTexCoords.front(), GL_STATIC_DRAW);

	}
	
	// indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMeshData->mIndices.size() * sizeof(unsigned int), &mMeshData->mIndices.front(), GL_STATIC_DRAW);
	
}

void Mesh::UnBufferMeshData()
{

}
/*
std::string Mesh::GetBoundingBox()
{
	return mBoundingBoxId;
}

void Mesh::CreateBoundingBox()
{
	
}
*/
void Mesh::IncRefCount()
{
	mRefCount++;

	if (mRefCount == 1)
		BufferMeshData();

}
void Mesh::DecRefCount()
{
	if (mRefCount > 0)
		mRefCount--;
	else
		LOG_WARNING() << "Trying to reduce Mesh's refcount belows zero";

	if (mRefCount == 0)
		UnBufferMeshData();

}

void Mesh::setMeshData(MeshData *arg_meshData)
{
	mMeshData = arg_meshData;
	mBoundingBox = BoundingBoxFactory::CreateBoundingBox(mMeshData);
}

BoundingBox *Mesh::GetBoundingBox()
{
	return mBoundingBox;
}