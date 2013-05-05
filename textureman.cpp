/**
 *	Alf-Andre Walla
 *	s181087
 *	
 *	Texture manager implementation
 *	
**/

#include "textureman.h"
#include "bitmap.h"

namespace platformer
{
	Textureman::Textureman() {}
	
	bool Textureman::init()
	{
		Bitmap bmp;
		
		if (bmp.load("bitmap/skybg.bmp"))
		{	// replace magenta with blendable transparency
			const color_rgba8_t bgcolor = Bitmap::makeColor(168, 224, 248, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_SKYBG] = Texture(GL_TEXTURE_2D);
			textures[T_SKYBG].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		}
		
		if (bmp.load("bitmap/normalbg.bmp"))
		{	// replace magenta with blendable transparency
			const color_rgba8_t bgcolor = Bitmap::makeColor(168, 184, 0, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_NORMALBG] = Texture(GL_TEXTURE_2D);
			textures[T_NORMALBG].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		}
		
		if (bmp.load("bitmap/forestbg.bmp"))
		{	// replace magenta with blendable transparency
			color_rgba8_t bgcolor = Bitmap::makeColor(168, 184, 0, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_FORESTBG] = Texture(GL_TEXTURE_2D);
			textures[T_FORESTBG].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		}
		
		if (bmp.load("bitmap/pillarbg.bmp"))
		{	// replace magenta with blendable transparency
			color_rgba8_t bgcolor = Bitmap::makeColor(168, 184, 0, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_PILLARBG] = Texture(GL_TEXTURE_2D);
			textures[T_PILLARBG].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		}
		
		if (bmp.load("bitmap/title.bmp"))
		{	// replace magenta with blendable transparency
			const color_rgba8_t bgcolor = Bitmap::makeColor(69, 25, 0, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_TITLE] = Texture(GL_TEXTURE_2D);
			textures[T_TITLE].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			
		}
		
		if (bmp.load("bitmap/introtext.bmp"))
		{	// replace magenta with blendable transparency
			const color_rgba8_t bgcolor = Bitmap::makeColor(0, 0, 0, 0);
			
			bmp.replace(Bitmap::MAGENTA, bgcolor);
			
			textures[T_INTROTEXT] = Texture(GL_TEXTURE_2D);
			textures[T_INTROTEXT].create(bmp, true, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			
		}
		
		if (bmp.load("bitmap/tileset.bmp"))
		{	// replace magenta with blendable transparency
			bmp.replace(Bitmap::MAGENTA, 0);
			bmp.parse2D(16, 16);			// FIXME: Magic constant
			
			textures[T_TILESET] = Texture(GL_TEXTURE_2D_ARRAY);
			textures[T_TILESET].create(bmp, true, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR);
			
		}
		
		if (bmp.load("bitmap/mario.bmp"))
		{	
			bmp.replace(Bitmap::MAGENTA, 0);
			bmp.parse2D(16, 16);			// FIXME: Magic constant
			
			textures[T_MARIO] = Texture(GL_TEXTURE_2D_ARRAY);
			textures[T_MARIO].create(bmp, true, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR);
		}
		
		// fullscreen postprocess buffer
		textures[T_FULLSCREEN] = Texture(GL_TEXTURE_2D);
		textures[T_FULLSCREEN].create(true, 3, ogl.SW, ogl.SH);
		
	}
	
	void Textureman::bind(int unit, named_textures_t tx)
	{
		textures[tx].bind(unit);
	}
	
}