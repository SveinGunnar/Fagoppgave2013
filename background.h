/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Background definition
 * 
 * Creates a x-repeatable background w/parallax
 * 
**/

#ifndef __BACKGROUND_H
#define __BACKGROUND_H

#include "vector.h"

namespace platformer
{
	class Background
	{
		float parallax;
		float alpha;
		
	public:
		Background();
		Background(float);
		
		void render(float, float, float);
		void render(float, vec3&, float);
	};
}

#endif
