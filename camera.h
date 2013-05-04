/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Camera definition
 * 
 * A point in space, with some helper functions
 * Always make a camera class!
 * 
 * focus(player) - interpolates camera position towards a single player
 * focus(vector<player>) - interpolates camera position towards center of
 *                         the average area of all players in vector
**/

#ifndef __CAMERA_H
#define __CAMERA_H

#include "player.h"
#include "vector.h"
#include <vector>

namespace platformer
{
	
	class Camera
	{
	public:
		Camera();
		Camera(const vec3& p, const vec3& r);
		vec3 position;
		//vec3 rotation;
		
		void focus(const Player& player, float lerp);
		void focus(const std::vector<Player>& pv, float power);
		
	};
	
}

#endif
