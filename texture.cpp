/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Texture implementation
 * 
**/

#include "texture.h"

#include "global.h"
#include "opengl.h"

namespace platformer
{
	GLuint Texture::lastid[TEXTURE_UNITS] = {0};
	
	Texture::Texture() : id(0), type(0) {}
	
	Texture::Texture(GLenum target)
	{
		this->type = target;
		glGenTextures(1, &this->id);
	}
	
	void Texture::create(Bitmap& b, bool mipmap = true, GLint wrapmode = GL_CLAMP_TO_EDGE, GLint magfilter = GL_NEAREST, GLint minfilter = GL_LINEAR_MIPMAP_LINEAR)
	{
		glBindTexture(this->type, this->id);
		glTexParameteri(this->type, GL_TEXTURE_MAX_ANISOTROPY_EXT, ogl.anisotrophy);
		
		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, wrapmode);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, magfilter);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, minfilter);
		
		// openGL is a C library, so const& is never going to work :)
		int width  = b.getwidth();
		int height = b.getheight();
		GLuint* pixel = const_cast<GLuint*>(b.data());
		
		if (mipmap)
		{
			//glTexParameteri(this->type, GL_TEXTURE_BASE_LEVEL, 0);
			//glTexParameteri(this->type, GL_TEXTURE_MAX_LEVEL, log(width) / log(2.0));
		}
		switch (this->type)
		{
		case GL_TEXTURE_2D:
			glTexImage2D(this->type, 0, ogl.imageformat, width, height, 0, GL_BGRA, ogl.storageformat, pixel);
			break;
		case GL_TEXTURE_2D_ARRAY:
			glTexImage3D(this->type, 0, ogl.imageformat, width, height, b.getbits(), 0, GL_BGRA, ogl.storageformat, pixel);
			break;
		default:
			logger.write(LERR, "@Texture::create(): Unknown texture target");
		}
		
		if (mipmap) glGenerateMipmap(this->type);
		
		if (OpenGL::checkError()) logger.write(LERR, "@Texture::create()");
		
	}
	
	void Texture::create(bool mipmap, int levels, int width, int height)
	{
		glBindTexture(this->type, this->id);
		//glTexParameteri(this->type, GL_TEXTURE_MAX_ANISOTROPY_EXT, ogl.anisotrophy);
		
		GLint minfilter = (mipmap) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
		
		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, minfilter);
		
		GLuint* pixel = NULL;
		
		if (mipmap)
		{
			glTexParameteri(this->type, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(this->type, GL_TEXTURE_MAX_LEVEL, levels);
		}
		
		switch (this->type)
		{
		case GL_TEXTURE_2D:
			glTexImage2D(this->type, 0, ogl.imageformat, width, height, 0, GL_BGRA, ogl.storageformat, pixel);
			break;
		default:
			logger.write(LERR, "@Texture::create(): Unknown texture target");
		}
		
		if (mipmap) glGenerateMipmap(this->type);
		
		if (OpenGL::checkError()) logger.write(LERR, "@Texture::create()");
		
	}
	
	void Texture::bind(int unit)
	{	// avoid binding same texture twice
		if (lastid[unit] == id) return;
		
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(this->type, this->id);
		if (OpenGL::checkError()) logger.write(LERR, "@Texture::bind()");
		lastid[unit] = id;
	}
	
}
