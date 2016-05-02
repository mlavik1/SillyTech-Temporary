#include "actor_factory.h"
#include "debug.h"
#include "mesh.h"
#include "mesh_data.h"
#include "glm.hpp"
#include "resource_manager.h"
#include "mesh_res.h"
#include "material.h"
#include "texture_factory.h"
#include "material_res.h"
#include "texture_res.h"

Actor* ActorFactory::CreateFromModel(const char* arg_path)
{
	const aiScene * scene;
	Assimp::Importer importer;

	scene = importer.ReadFile(arg_path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_RemoveRedundantMaterials | aiProcess_GenSmoothNormals);

	Actor *actor = new Actor();

	if (!scene)
	{
		LOG_ERROR() << "Failed to load model: " << arg_path;
		return 0;
	}

	for (int m = 0; m < scene->mNumMeshes; m++)
	{
		Actor *child = new Actor();
		child->SetName(scene->mMeshes[m]->mName.C_Str());
		actor->AddChild(child);

		Mesh *mesh = new Mesh();
		MeshData *meshData = new MeshData();
		mesh->setMeshData(meshData);


		// Get Vertices
		if (scene->mMeshes[m]->mNumVertices > 0)
		{
			for (unsigned int i = 0; i < scene->mMeshes[m]->mNumVertices; ++i)
			{
				aiVector3D &v = scene->mMeshes[m]->mVertices[i];

				meshData->mVertices.push_back(glm::vec3(v.x, v.y, v.z));
			}
		}

		// Get Normals
		if (scene->mMeshes[m]->HasNormals())
		{
			for (unsigned int i = 0; i < scene->mMeshes[m]->mNumVertices; ++i)
			{
				aiVector3D &vn = scene->mMeshes[m]->mNormals[i];
				meshData->mNormals.push_back(glm::vec3(vn.x, vn.y, vn.z));
			};
		}

		// Get Texture coordinates
		if (scene->mMeshes[m]->HasTextureCoords(0))
		{
			for (unsigned int i = 0; i < scene->mMeshes[m]->mNumVertices; ++i)
			{
				aiVector3D vt = scene->mMeshes[m]->mTextureCoords[0][i];
				meshData->mTexCoords.push_back(glm::vec2(vt.x, vt.y));

			};
		}
		
		for (int f = 0; f < scene->mMeshes[m]->mNumFaces; f++)
		{
			const aiFace& face = scene->mMeshes[m]->mFaces[f];

			for (int i = 0; i < 3; i++)
			{/*
				aiVector3D v = scene->mMeshes[m]->mVertices[face.mIndices[i]];
				meshData->mVertices.push_back(glm::vec3(v.x, v.y, v.z));

				aiVector3D vn = scene->mMeshes[m]->HasNormals() ? scene->mMeshes[m]->mNormals[face.mIndices[i]] : aiVector3D(0.0f, 0.0f, 0.0f);
				meshData->mNormals.push_back(glm::vec3(vn.x, vn.y, vn.z));

				aiVector3D vt = scene->mMeshes[m]->mTextureCoords[0][face.mIndices[i]];
				meshData->mTexCoords.push_back(glm::vec2(vt.x, vt.y));
				*/
				meshData->mIndices.push_back(face.mIndices[i]);
			}
		}

		std::string name = arg_path; name += ":"; name += std::to_string(m);
		MeshRes *meshRes = new MeshRes(name.c_str());
		meshRes->SetMesh(mesh);
		ResourceManager<MeshRes>::Instance()->AddResource(meshRes);

		mesh->BufferMeshData();

		MeshRenderComponent *meshRenderComp = new MeshRenderComponent();
		meshRenderComp->SetMeshID(meshRes->GetResourceName().c_str());
		

		int matIndex = scene->mMeshes[m]->mMaterialIndex;
		std::string matName = name + std::to_string(matIndex);
		MaterialRes *matRes = ResourceManager<MaterialRes>::Instance()->GetResource(matName.c_str());
		if (!matRes)
		{
			matRes = new MaterialRes(matName.c_str(), new Material());
			ResourceManager<MaterialRes>::Instance()->AddResource(matRes);
			
			aiString path;  // filename
			if (scene->mMaterials[matIndex]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				std::string fullPath = arg_path;
				fullPath = fullPath.substr(0, fullPath.find_last_of("\\/"));
				fullPath += "/"; fullPath += path.C_Str();

				TextureFactory::CreateFromFile(fullPath.c_str());
				matRes->GetMaterial()->SetTexture(TEXTURE_TYPE_DIFFUSE, fullPath.c_str());
			}
			else
			{
				aiColor4D diffuse;
				if (AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[matIndex], AI_MATKEY_COLOR_DIFFUSE, &diffuse))
					matRes->GetMaterial()->SetColour(glm::vec4(diffuse.r, diffuse.g, diffuse.g, diffuse.a));
				else
					matRes->GetMaterial()->SetColour(glm::vec4(0.0f,0.0f,0.0f,1.0f));
			}
				

		}
		
		meshRenderComp->SetMaterialID(matName.c_str());
		child->AttachComponent(meshRenderComp);

		// TODO: load texture resource

	}

	LOG_INFO() << "Successfully loaded model: " << arg_path;

	return actor;

}