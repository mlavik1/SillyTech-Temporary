#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void BufferTexture();

	inline GLuint GetTextureBuffer()
	{
		return mTextureBuffer;
	}
	inline void SetTextureBuffer(GLuint arg_tBuffer)
	{
		mTextureBuffer = arg_tBuffer;
	}
	inline void SetFilename(const char* arg_filename)
	{
		mFilename = arg_filename;
	}

private:
	GLuint mTextureBuffer;
	std::string mFilename;
};

#endif