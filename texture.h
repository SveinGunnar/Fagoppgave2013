/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Texture definition
 * 
 * create - Creates a texture with, or without, a bitmap
 * (Empty textures are used as offscreen buffers)
 * bind - Binds the selected texture, unless it was already bound
 * 
**/

#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "bitmap.h"
#include "GL/gl.h"

/*
	Targets:
		GL_TEXTURE_1D
		GL_TEXTURE_2D
		GL_TEXTURE_3D
		GL_TEXTURE_1D_ARRAY
		GL_TEXTURE_2D_ARRAY
		GL_TEXTURE_RECTANGLE
		GL_TEXTURE_CUBE_MAP.
		
	Wrapmodes:
		GL_REPEAT   <-- default
		GL_MIRRORED_REPEAT
		GL_CLAMP
		GL_CLAMP_TO_EDGE
		GL_CLAMP_TO_BORDER
		
	Filtermodes:
		GL_NEAREST
		GL_LINEAR
		GL_NEAREST_MIPMAP_NEAREST
		GL_LINEAR_MIPMAP_NEAREST
		GL_NEAREST_MIPMAP_LINEAR
		GL_LINEAR_MIPMAP_LINEAR
		
*/

namespace platformer
{
	const int TEXTURE_UNITS = 8;
	
	class Texture
	{
		GLuint id;
		GLenum type;
		
		static GLuint lastid[TEXTURE_UNITS];
		
	public:
		Texture();
		Texture(GLenum target);
		void create(Bitmap&, bool, GLint, GLint, GLint); // texture
		void create(bool, int, int, int);				 // buffer
		void bind(int);
	};
	
}

#endif
