/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Texture manager definition
 * 
 * init - Creates and loads all textures needed
 * bind - Binds the given texture (by enum), which is then used in rendering
 * 
**/

#ifndef __TEXTUREMAN_H
#define __TEXTUREMAN_H

#include "opengl.h"
#include "texture.h"

namespace platformer
{
	typedef enum
	{
		T_SKYBG,
		T_NORMALBG,
		T_FORESTBG,
		T_PILLARBG,
		
		T_TITLE,
		T_INTROTEXT,
		T_TILESET,
		T_MARIO,
		
		T_FULLSCREEN,
		
		NUM_TEXTURES
	} named_textures_t;
	
	class Textureman
	{
	private:
		Texture textures[NUM_TEXTURES];
		
	public:
		Textureman();
		
		bool init();
		void bind(int, named_textures_t);
		
	};
}

#endif
