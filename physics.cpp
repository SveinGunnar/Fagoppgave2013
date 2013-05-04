/**
 * Alf-Andre Walla
 * s181087
 * 
 * Physics implementation
 * 
**/

#include "physics.h"
#include "player.h"
#include "toolbox.hpp"

namespace platformer
{
	const vec3 Physics::AIR_FRICTION(0.75, 1.0, 0.0);
	const vec3 Physics::GROUND_FRICTION(0.5, 0.1, 0.0);
	
	void Physics::momentum(Entity& entity, double dt, const vec3& mv)
	{
		dt /= 16.7;
		
		float GRAVITY     = 0.07 * dt;
		//float MAX_GRAVITY = 0.6 * dt;
		
		vec3 acc   = entity.getAcc();
		vec3 speed = entity.getSpeed();
		float maxspeed = entity.getMaxSpeed();
		
		// accumulate speed
		float d = toolbox::signum(mv.x);
		float spd_x = d * toolbox::min(maxspeed, (speed.x + maxspeed * mv.x) * d);
		float spd_y = speed.y + acc.y - GRAVITY;
		
		// new speed
		vec3 newspeed(spd_x * dt, spd_y * dt, 0.0);
		entity.setSpeed( newspeed );
		
	}
	
	blockid_t Physics::testGrid(Grid& grid, vec3 coord)
	{
		int x = (int)coord.x;
		int y = (int)coord.y;
		return grid.get(x, y).id;
	}
	
	bool Physics::testGround(Grid& grid, Entity& entity)
	{
		const float GROUND_LEVEL = -0.05;
		
		vec3 position = entity.getPosition();
		vec3 size = entity.getSize();
		vec3 c0(size.x * 0.1, GROUND_LEVEL, 0.0);
		vec3 c1(size.x * 0.9, GROUND_LEVEL, 0.0);
		
		if ((testGrid(grid, position + c0) | testGrid(grid, position + c1)) == _AIR)
			return false;
		return true;
	}
	
	bool Physics::integrate(Grid& grid, Entity& entity, vec3& mv)
	{
		const float SPEED_TRESHOLD = 0.005;
		const float STEPSIZE = 0.001;
		
		vec3 position = entity.getPosition();
		
		float L = mv.length();
		if (L > SPEED_TRESHOLD)
		{
			// integrate
			vec3 norm = mv / L;
			vec3 step = norm * STEPSIZE;
			vec3 size = entity.getSize();
			vec3 c0(size.x * 0.1, 0.0, 0.0);
			vec3 c1(size.x * 0.9, 0.0, 0.0);
			vec3 c2(size.x * 0.1, size.y, 0.0);
			vec3 c3(size.x * 0.9, size.y, 0.0);
			
			int Nsteps = L / STEPSIZE;
			for (int i = 0; i < Nsteps; i++)
			{
				position = position + step;
				
				if ((testGrid(grid, position + c0) | testGrid(grid, position + c1)
				   | testGrid(grid, position + c2) | testGrid(grid, position + c3)) == _AIR)
				{
					// move player (one step at a time)
					entity.setPosRel(step);
				}
				else return true;
				
			}
			// TODO: test remainder of integration
		}
		return false;
	}
	
}
