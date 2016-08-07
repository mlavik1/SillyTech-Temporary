#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "mesh_data.h"
#include <string>
#include "bounding_box.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	GLuint mVBO;
	GLuint mNBO;
	GLuint mTBO;
	GLuint mIBO;

public:
	void			BufferMeshData();
	void			UnBufferMeshData();
	BoundingBox*	GetBoundingBox();

private:
	int				mRefCount;
	MeshData*		mMeshData;
	BoundingBox*	mBoundingBox;	// bounding box (of this mesh only) used for space subdivision, etc..

public:
	void IncRefCount();
	void DecRefCount();

	void setMeshData(MeshData *arg_meshData);
	inline MeshData *GetMeshData()
	{
		return  mMeshData;
	}

};

#endif