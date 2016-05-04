#include "gl_graphics_system.h"

#include "debug.h"
#include "graphics_feature.h"

void GLGraphicsSystem::Initialise()
{
	LOG_INFO() << "Initialising GLGraphicsSystem";

	int max_texture_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
	LOG_INFO() << "Maximum texture size: " << max_texture_size;

	mPostProcessShaderProgram = new ShaderProgram();

}
void GLGraphicsSystem::BufferVectorData(std::vector<glm::vec3> &arg_vecs)
{

}
void GLGraphicsSystem::BufferVectorData(std::vector<glm::vec2> &arg_vecs)
{

}
void GLGraphicsSystem::ClearScreen(float r, float g, float b)
{
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLGraphicsSystem::PrepareRender()
{
	glLoadIdentity();
	ClearScreen(0.2f, 0.2f, 0.8f);
}

void GLGraphicsSystem::InitMainFrameBuffer(int arg_width, int arg_height)
{
	
	mPostProcessShaderProgram->SetShader(SHADER_TYPE_VERTEXSHADER, "Resources/Shaders/default_postprocess.vs");
	mPostProcessShaderProgram->SetShader(SHADER_TYPE_FRAGMENTSHADER, "Resources/Shaders/default_postprocess.fs");
	mPostProcessShaderProgram->SetIsPostProcess(true);

	mPostProcessShaderProgram->CreatePogram();

	// The framebuffer
	glGenFramebuffers(1, &mMainFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, mMainFrameBuffer);

	// Texture we will render to
	glGenTextures(1, &mMainFrameBufferTexture);

	// Bind the newly created texture
	glBindTexture(GL_TEXTURE_2D, mMainFrameBufferTexture);

	// Give an empty image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, arg_width, arg_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0); // last 0 means empty

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, arg_width, arg_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "mMainFrameBufferTexture" as colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mMainFrameBufferTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR() << "Error in FrameBuffer";


	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};


	glGenBuffers(1, &mQuadVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mQuadVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	
}

void GLGraphicsSystem::RenderMainFrameBuffer()
{
	glUseProgram(mPostProcessShaderProgram->GetShaderProgram());
	mPostProcessShaderProgram->SetUniform("renderedTexture", 0);

	// Render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLint shaderProgram = mPostProcessShaderProgram->GetShaderProgram();
	if (shaderProgram != -1)
		glUseProgram(shaderProgram);
	else
	{
		LOG_ERROR() << "Post process shader program not found!";
		return;
	}
		

	//glUniform1fv(g_uniformShaderSettings2, shaderSettings.numSettings, shaderSettings.GetSettings());

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMainFrameBufferTexture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mQuadVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
}

void GLGraphicsSystem::BindMainFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mMainFrameBuffer);
}

ShaderProgram *GLGraphicsSystem::GetPostProcessProgram()
{
	return mPostProcessShaderProgram;
}