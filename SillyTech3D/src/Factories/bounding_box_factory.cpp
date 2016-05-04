#include "bounding_box_factory.h"
#include "mesh_render_component.h"
#include "mesh_res.h"
#include "mesh_data.h"
#include "mesh.h"
#include "actor.h"
#include "st_assert.h"
#include "glm.hpp"


BoundingBox *BoundingBoxFactory::CreateBoundingBox(Actor *arg_actor)
{
	std::vector<MeshRenderComponent*> comps = arg_actor->GetComponentsByType<MeshRenderComponent>(true);

	if (!arg_actor)
	{
		LOG_ERROR() << "Cannot create bounding box NULL actor";
		return 0;
	}

	if (comps.size() < 1)
	{
		LOG_ERROR() << "Cannot create bounding box from actor that has no MeshRenderComponents";
		return 0;
	}

	glm::vec3 min(9999.0f);
	glm::vec3 max(-9999.0f);


	for (MeshRenderComponent *comp : comps)
	{
		if (comp->GetMeshID() == "")
		{
			LOG_ERROR() << "MeshRenderComponent has no Mesh! Cannot create bounding box";
			return 0;
		}
		MeshRes *res = ResourceManager<MeshRes>::Instance()->GetResource(comp->GetMeshID().c_str());
		if (!res)
		{
			LOG_ERROR() << "MeshRes is NULL! Cannot create bounding box";
			return 0;
		}
		Mesh *mesh = res->GetMesh();				//__AssertComment(mesh != 0, "Mesh cannot be NULL");
		MeshData *meshdata = mesh->GetMeshData();	//__AssertComment(meshdata != 0, "MeshData cannot be NULL");

		for (int i : meshdata->mIndices)
		{
			glm::vec3 v = meshdata->mVertices[i];
			if (v.x < min.x)
				min.x = v.x;
			else if (v.x > max.x)
				max.x = v.x;

			if (v.y < min.y)
				min.y = v.y;
			else if (v.y > max.y)
				max.y = v.y;

			if (v.z < min.z)
				min.z = v.z;
			else if (v.z > max.z)
				max.z = v.z;
		}
	}

	MeshData *meshData = new MeshData();
	meshData->mVertices.push_back(min);
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, min.z));
	meshData->mVertices.push_back(glm::vec3(max.x, max.y, min.z));
	meshData->mVertices.push_back(glm::vec3(min.x, max.y, min.z));
	meshData->mVertices.push_back(glm::vec3(min.x, min.y, max.z));
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, max.z));
	meshData->mVertices.push_back(max);
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, min.z));
	meshData->mIndices.push_back(0);
	meshData->mIndices.push_back(1);
	meshData->mIndices.push_back(2);
	meshData->mIndices.push_back(3);
	meshData->mIndices.push_back(4);
	meshData->mIndices.push_back(5);
	meshData->mIndices.push_back(6);
	meshData->mIndices.push_back(7);

	/*
	Mesh *mesh = new Mesh();
	mesh->setMeshData(meshData);
	MeshRes *res = new MeshRes((const char*)mesh);
	res->SetMesh(mesh);
	ResourceManager<MeshRes>::Instance()->AddResource(res);
	mesh->BufferMeshData();
	*/

	//return res->GetResourceName();
	BoundingBox *bb = new BoundingBox();
	bb->SetMeshData(meshData);
	bb->SetBounds((max.x - min.x) / 2.0f, (max.y - min.y) / 2.0f, (max.z - min.z) / 2.0f);
	return bb;
}

BoundingBox *BoundingBoxFactory::CreateBoundingBox(MeshData *arg_meshdata)
{

	if (!arg_meshdata)
	{
		LOG_ERROR() << "MeshData is NULL! Cannot create bounding box.";
		return 0;
	}

	glm::vec3 min;
	glm::vec3 max;

	for (glm::vec3 v : arg_meshdata->mVertices)
	{
		if (v.x < min.x)
			min.x = v.x;
		else if (v.x > max.x)
			max.x = v.x;

		if (v.y < min.y)
			min.y = v.y;
		else if (v.y > max.y)
			max.y = v.y;

		if (v.z < min.z)
			min.z = v.z;
		else if (v.z > max.z)
			max.z = v.z;
	}

	MeshData *meshData = new MeshData();
	meshData->mVertices.push_back(min);
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, min.z));
	meshData->mVertices.push_back(glm::vec3(max.x, max.y, min.z));
	meshData->mVertices.push_back(glm::vec3(min.x, max.y, min.z));
	meshData->mVertices.push_back(glm::vec3(min.x, min.y, max.z));
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, max.z));
	meshData->mVertices.push_back(max);
	meshData->mVertices.push_back(glm::vec3(max.x, min.y, min.z));
	meshData->mIndices.push_back(0);
	meshData->mIndices.push_back(1);
	meshData->mIndices.push_back(2);
	meshData->mIndices.push_back(3);
	meshData->mIndices.push_back(4);
	meshData->mIndices.push_back(5);
	meshData->mIndices.push_back(6);
	meshData->mIndices.push_back(7);

	BoundingBox *bb = new BoundingBox();
	bb->SetMeshData(meshData);
	bb->SetBounds((max.x-min.x)/2.0f, (max.y - min.y) / 2.0f, (max.z - min.z) / 2.0f);
	return bb;
}