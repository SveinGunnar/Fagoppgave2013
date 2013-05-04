/**
 * Alf-Andre Walla
 * s181087
 * 
 * Entity definition, position, speed, acceleration and size
 * 
 * A point in space with speed, acceleration and a given size
 * Base class for players and units
 * 
**/

#ifndef __ENTITY_H
#define __ENTITY_H

#include "vector.h"

namespace platformer
{
	class Entity
	{
		vec3 pos;
		vec3 spd;
		vec3 acc;
		// assuming entity is a quad
		vec3 size; // (x, y, Ø)
		float maxspeed;
		
	public:	
		bool grounded; // true = on-ground, false = in-air
		
		Entity( vec3, vec3, float );
		
		void setPosRel( vec3 delta );
		void setSpdRel( vec3 delta );
		void setAccRel( vec3 delta, vec3 clamp );
		void friction(const vec3& friction);
		
		void setSpeed(vec3&);
		const vec3& getPosition() const;
		const vec3& getSpeed() const;
		const vec3& getAcc() const;
		
		const vec3& getSize() const;
		float getMaxSpeed();
	};
}

#endif
