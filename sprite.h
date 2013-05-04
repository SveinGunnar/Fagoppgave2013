/*

*/

#ifndef __SPRITE_H
#define __SPRITE_H

#include "vector.h"

namespace platformer
{
	typedef enum
	{
		SPRITE_FIXED    = 0x0,
		SPRITE_CENTER_X = 0x1,
		SPRITE_CENTER_Y = 0x2,
		SPRITE_REL_X    = 0x4,
		SPRITE_REL_Y    = 0x8
		
	} sprite_placement_t;
	
	class Sprite
	{
	protected:
		int location;
		vec3 position;
		
	public:
		Sprite(const vec3& pos, int);
		
		void setPosition(const vec3&);
		virtual void render(const vec3&);
	};
	
	class SpriteTile : public Sprite
	{
	public:
		SpriteTile(const vec3& pos, int loc) : Sprite(pos, loc) {};
		void render(const vec3&, int);
	};
	
}

#endif
