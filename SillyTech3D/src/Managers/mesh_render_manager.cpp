#include "mesh_render_manager.h"

#include "resource_manager.h"
#include "mesh_res.h"
#include "material_res.h"
#include "texture_res.h"
#include "shader.h"
#include "shader_res.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "camera_component.h"
#include "camera_manager.h"
#include "graphics_feature.h"
#include "actor.h"


__ImplementSingleton(MeshRenderManager)

MeshRenderManager::MeshRenderManager()
{
	__ConstructSingleton(MeshRenderManager)
}


MeshRenderManager::~MeshRenderManager()
{
	__DestructSingleton(MeshRenderManager)
}

void MeshRenderManager::OnFrame()
{
	Manager::OnFrame();

	mDrawCalls = 0; mDrawCallsSkipped = 0;

	int numCams = CameraManager::Instance()->GetNumCameraComponents();
	if (numCams < 1)
		LOG_WARNING() << "No active CameraComponents in scene! Cannot render to viewport.";

	for (int c = 0; c < numCams; c++)
	{
		CameraComponent *camComp = CameraManager::Instance()->GetCameraComponent(c);
		Viewport vp = camComp->GetViewport();
		glm::mat4 camMat = camComp->GetViewMatrix();

		GraphicsFeature::Instance()->GetDisplay()->Reshape(vp);
		glClear(GL_DEPTH_BUFFER_BIT);


		for (MeshRenderComponent *comp : mMeshRenderComponents)
		{
			Mesh *mesh;
			Material *material;
			Texture *texture = 0;

			MeshRes *meshRes = ResourceManager<MeshRes>::Instance()->GetResource(comp->GetMeshID().c_str());
			mesh = meshRes->GetMesh();
			
			BoundingBox *boundingBox = comp->GetBoundingBox();
			if (boundingBox)
			{
				glm::vec3 camPos = camComp->GetParent()->GetTransform().GetGlobalPosition();
				glm::vec3 f = glm::normalize(camComp->GetParent()->GetTransform().Forward());
				bool skip = true;
				// ***** TODO *****
				// Check ifbertex lies inside the view frustrum
				// MVP*v has x: [0,Pclip.w]
				// MVP*v has y: [0,Pclip.h]
				for (glm::vec3 v : boundingBox->GetMeshData()->mVertices) // TODO: use ModelView matrix
				{
					skip &= (glm::dot(glm::normalize(v*comp->GetParent()->GetTransform().GetGlobalScale() +comp->GetParent()->GetTransform().GetGlobalPosition() - camPos), glm::normalize(f)) < 0);
					if (!skip)
						continue;
				}
					
				if (skip)
				{
					mDrawCallsSkipped++;
					continue;
				}
			}
			

			

			MaterialRes *matRes = ResourceManager<MaterialRes>::Instance()->GetResource(comp->GetMaterialID().c_str());
			material = matRes->GetMaterial();
			TextureRes *texRes = ResourceManager<TextureRes>::Instance()->GetResource(material->GetTexture(TEXTURE_TYPE_DIFFUSE).c_str());
			
			glUseProgram(material->GetShaderProgram().GetShaderProgram());
			glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferObject);
			//glUniformBlockBinding(material->GetShaderProgram().GetShaderProgram(), uniformBufferObject, uniformBufferObject);
			if (texRes)
				texture = texRes->GetTexture();
			else
			{
				material->GetShaderProgram().SetUniform("diffuse_colour", material->GetColour());
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			if(texture)
				glEnable(GL_TEXTURE_2D);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);


			// Vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->mVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Normals
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->mNBO);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			if (texture)
			{
				// Textures
				glEnableVertexAttribArray(2);
				glActiveTexture(GL_TEXTURE0);	// TODO: +i
				glBindBuffer(GL_ARRAY_BUFFER, mesh->mTBO);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glBindTexture(GL_TEXTURE_2D, texture->GetTextureBuffer());
			}

			/*
			glLoadIdentity();
			glm::vec3 pos = comp->GetParent()->GetTransform().GetGlobalPosition();
			glm::vec3 scale = comp->GetParent()->GetTransform().GetGlobalScale();
			glTranslatef(pos.x, pos.y, pos.z);
			//comp->GetParent()->GetTransform().rotate(1.0f,glm::vec3(0.0f,1.0f,0.0f));
			glMultMatrixf(glm::value_ptr(comp->GetParent()->GetTransform().GetGlobalRotation()));
			glScalef(scale.x, scale.y, scale.z);


			GLfloat projection[16];
			glGetFloatv(GL_PROJECTION_MATRIX, projection);
			GLfloat modelview[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			*/
			
			GLfloat projection[16];

			glm::mat4 transMat, scaleMat;
			transMat = glm::translate(glm::mat4(1.0f),comp->GetParent()->GetTransform().GetGlobalPosition());
			scaleMat = glm::scale(glm::mat4(1.0f), comp->GetParent()->GetTransform().GetGlobalScale());
			//glm::mat4 modelMatrix = transMat * comp->GetParent()->GetTransform().GetGlobalRotation() * scaleMat;
			glm::mat4 modelMatrix = comp->GetParent()->GetTransform().GetGlobalModelMatrix();
			GLfloat *modelview = glm::value_ptr(modelMatrix);
			glLoadIdentity();
			glGetFloatv(GL_PROJECTION_MATRIX, projection);
			
			material->GetShaderProgram().SetUniform4fv("ModelView", (const GLfloat*)modelview);
			material->GetShaderProgram().SetUniform4fv("ProjectionView", (const GLfloat*)projection);
			material->GetShaderProgram().SetUniform4fv("CameraView", (const GLfloat*)glm::value_ptr(camMat));
			if(texture)
				material->GetShaderProgram().SetUniform("sampler", 0);
			else
				material->GetShaderProgram().SetUniform("use_colour", 1);
			material->GetShaderProgram().SetUniform("EyePosW", camComp->GetParent()->GetTransform().GetGlobalPosition());

			// Lights:
			// ***** TODO *****
			// Only do this when neccessary!!!
			material->GetShaderProgram().SetUniform("numLights", (GLint)mLightComponents.size());
			for (size_t i = 0; i < mLightComponents.size(); i++)
			{
				LightComponent *light = mLightComponents[i];
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].type")).c_str(), (GLint)light->GetLightType());
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].position")).c_str(), light->GetParent()->GetTransform().GetGlobalPosition());
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].direction")).c_str(), light->GetParent()->GetTransform().Forward());
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].ambientColour")).c_str(), light->GetAmbientColour());
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].diffuseColour")).c_str(), light->GetDiffuseColour());
				material->GetShaderProgram().SetUniform((std::string("lights[")+std::to_string(i)+std::string("].specularColour")).c_str(), light->GetSpecularColour());
			}

			if (!mesh->mVBO)
			{
				LOG_ERROR() << "VBO is NULL for: " << comp->GetMeshID().c_str();
				return;
			}

			if (mesh->GetMeshData()->mIndices.empty())
			{
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			else {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIBO);
				glDrawElements(GL_TRIANGLES, mesh->GetMeshData()->mIndices.size(), GL_UNSIGNED_INT, 0);
			}
			mDrawCalls++;
		}

	}



}

void MeshRenderManager::OnStart()
{
	Manager::OnStart();

	/*
	ShaderProgram *p = new ShaderProgram();
	p->SetShader(SHADER_TYPE_VERTEXSHADER, "Resources/Shaders/default_shader.vs");
	p->SetShader(SHADER_TYPE_FRAGMENTSHADER, "Resources/Shaders/default_shader.fs");
	p->SetShader(SHADER_TYPE_GEOMETRYSHADER, "Resources/Shaders/default_shader.gs");
	p->CreatePogram();

	float myFloats[8] = { 1.0, 0.0, 0.0, 1.0,   0.4, 0.0, 0.0, 1.0 };
	GLuint bindingPoint = 1;
	GLuint blockIndex = glGetUniformBlockIndex(p->GetShaderProgram(), "ColorBlock");
	glUniformBlockBinding(p->GetShaderProgram(), blockIndex, bindingPoint);

	glGenBuffers(1, &uniformBufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferObject);

	glBufferData(GL_UNIFORM_BUFFER, sizeof(myFloats), myFloats, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uniformBufferObject);
	*/
}

void MeshRenderManager::OnStop()
{
	Manager::OnStop();

}

void MeshRenderManager::OnActivate()
{
	Manager::OnActivate();
}

void MeshRenderManager::OnDeactivate()
{
	Manager::OnDeactivate();
}


void MeshRenderManager::AttachMeshRenderComponent(MeshRenderComponent *arg_comp)
{
	mMeshRenderComponents.push_back(arg_comp);
}

void MeshRenderManager::RemoveMeshRenderComponent(MeshRenderComponent *arg_comp)
{

	for (size_t i = 0; i < mMeshRenderComponents.size(); i++)
		if (mMeshRenderComponents[i] == arg_comp)
			mMeshRenderComponents.erase(mMeshRenderComponents.begin() + i);
}

void MeshRenderManager::AttachLightComponent(LightComponent *arg_comp)
{
	mLightComponents.push_back(arg_comp);
}

void MeshRenderManager::RemoveLightComponent(LightComponent *arg_comp)
{
	for (size_t i = 0; i < mLightComponents.size(); i++)
		if (mLightComponents[i] == arg_comp)
			mLightComponents.erase(mLightComponents.begin() + i);
}

