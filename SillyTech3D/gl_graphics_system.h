#ifndef GLGRAPHICSSYSTEM_H
#define GLGRAPHICSSYSTEM_H

#include "graphics_system.h"
#include <vector>
#include "GL\glew.h"

#include "glm.hpp"
#include "shader_program.h"

class GLGraphicsSystem
{
public:
	void Initialise();
	void BufferVectorData(std::vector<glm::vec3> &arg_vecs);
	void BufferVectorData(std::vector<glm::vec2> &arg_vecs);
	void PrepareRender();
	void ClearScreen(float r, float g, float b);
	void InitMainFrameBuffer(int arg_width, int arg_height);
	void BindMainFrameBuffer();
	void RenderMainFrameBuffer();
	ShaderProgram *GetPostProcessProgram();

private:
	GLuint mMainFrameBuffer;
	GLuint mMainFrameBufferTexture;
	GLuint mQuadVertexBuffer;
	ShaderProgram *mPostProcessShaderProgram;
};

#endif