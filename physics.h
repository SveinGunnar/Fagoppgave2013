/**
 * Alf-Andre Walla
 * s181087
 * 
 * Physics definition
 * momentum: applies physics
 * testGrid / testGround - returns contents of grid at entity position
 * integrate - raycasts a point as far as it can go using small steps
 * 
**/

#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "vector.h"
#include "player.h"
#include "grid.h"

namespace platformer
{
	class Physics
	{
	public:
		static void momentum( Entity&, double, const vec3& );
		
		static blockid_t testGrid(Grid& grid, vec3 coord);
		static bool testGround(Grid& grid, Entity& entity);
		static bool integrate(Grid& grid, Entity& entity, vec3& mv);
		
		static const vec3 AIR_FRICTION, GROUND_FRICTION;
	};
}
#endif