/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Unit definition - inherits entity
 * Mushroom definition - inherits unit
 * 
**/

#ifndef __UNIT_H
#define __UNIT_H

#include "entity.h"
#include "vector.h"

namespace platformer
{
	class Unit : public Entity
	{
		virtual int getFrame() = 0;
		
	public:
		void render();
	};
	
	class Mushroom : public Unit
	{
		typedef enum
		{
			M_LIFE, M_1UP, M_POISON
		} mushroom_t;
		
		mushroom_t type;
		bool direction;
		
	public:
		Mushroom(vec3 position, mushroom_t type);
		
		int getFrame();
		
		static const float CONST_SPEED = 0.15;
	};
	
	
}

#endif
