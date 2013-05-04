/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Generator implementation
 * 
**/

#include "generator.h"
#include "noise/simplex1234.h"
#include <cmath>

namespace platformer
{
	
	std::vector<Block> Generator::generate(int worldX, double t)
	{
		#define gnoise(x, f)  snoise1(x * 0.125 * f)
		#define gnoise2(x, y, f)  snoise2(x * 0.125 * f, y * 0.125 * f)
		#define gnoise3(x, y, z, f)  snoise3(x * 0.125 * f, y * 0.125 * f, z)
		
		std::vector<Block> v;
		double n;
		double dy;
		double x = worldX;
		blockid_t id, lastid = _AIR;
		blockid_t blocks[WORLD_HEIGHT] = {0};
		
		// terrain pass
		for (int y = WORLD_HEIGHT-1; y >= 0; y--)
		{
			dy = (double)y / (double)(WORLD_HEIGHT-1);
			
			//n = gnoise3(x, y, t * 0.0004, 0.5) * 0.2 + gnoise(x * 0.5, 1.25) * 0.12 + 1.6 * dy - 0.2;
			n = gnoise2(x, y, 0.5) * 0.2 + gnoise(x, 0.625) * 0.12 + 1.6 * dy - 0.2;
			
			if (n < 0.0)
			{	// dense signal
				if (lastid == _AIR)
					id = _DIRT_TOP;
				else
					id = _DIRT;
			}
			else id = _AIR;
			
			
			blocks[y] = id;
			lastid = id;
		}
		
		// insertion pass
		int air = 0;
		for (int y = 0; y < WORLD_HEIGHT; y++)
		{
			id = blocks[y];
			if (id == _AIR) air++; else air = 0;
			
			dy = (double)y / (double)(WORLD_HEIGHT-1);
			
			// appropriate height for interactive content
			if (air == (int)(gnoise(x, 0.05) * 5 + 5))
			{
				// coin boxes
				if (gnoise(x, 1.0) * gnoise2(x, y, 0.5) > 0.1)
				{
					switch ((int)fabs(gnoise2(x, y, 0.3) * 3))
					{
					case 0:
						id = _COINBOX; break;
					case 1:
						id = _FLIPBOX; break;
					case 2:
						id = _NOTEBOX; break;
						
					default:
						id = _PIPE_UP_TOP;
					}
				}
			}
			
			v.push_back(id);
		}
		
		return v;
	}
	
}
