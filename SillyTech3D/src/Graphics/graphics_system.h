#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "glm.hpp"
#include <vector>
#include "shader_program.h"

class GraphicsSystem
{
public:
	virtual void Initialise() {}
	virtual void BufferVectorData(std::vector<glm::vec3> &arg_vecs) {}
	virtual void BufferVectorData(std::vector<glm::vec2> &arg_vecs) {}
	virtual void PrepareRender() {}
	virtual void ClearScreen(float r, float g, float b) {}
	virtual void InitMainFrameBuffer(int arg_width, int arg_height) {}
	virtual void BindMainFrameBuffer() {}
	virtual void RenderMainFrameBuffer() {}
	virtual ShaderProgram &GetPostProcessProgram() { return ShaderProgram(); }
};

#endif