/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Generator definition
 * Uses signals noise to generate blocks
 * Uses simplex (coherent gradient) noise as detailed by Ken Perlin
 * If i had more time I would use my own cosnoise() (shameless plug!)
 * 
**/

#ifndef __GENERATOR_H
#define __GENERATOR_H

#include <vector>
#include "blocks.h"

namespace platformer
{
	class Generator
	{
	public:
		
		static std::vector<Block> generate(int worldX, double t);
		
	};
}

#endif
