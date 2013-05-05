/**
 *	Block, a single cell/tile in the world grid
 *	Static helper functions, mostly
 *	
 *	s181087, Alf-Andre Walla
 *	
**/

#include "blocks.h"

namespace platformer
{
	
	bool Block::isDirt(blockid_t id)
	{
		// true if the current id is part of the grass/dirt tileset
		return (id >= _DIRT_TOP_L && id <= _DIRT_BLOCK);
	}
	
	int Block::toTexture(blockid_t id)
	{
		const int SCANLINE = 16;
		
		// converts a block id to a (renderable) texture tile number
		int base;
		
		switch (id)
		{
		case _AIR:
			return 255;       // max texture_array tile id
			
		case _DIRT_TOP_L:
		case _DIRT_TOP:
		case _DIRT_TOP_R:
		case _DIRT_LEFT:
		case _DIRT:
		case _DIRT_RIGHT:
		case _DIRT_BOT_L:
		case _DIRT_BOT:
		case _DIRT_BOT_R:
			base = id - _DIRT_TOP_L;
			return (base % 3) + (base / 3) * SCANLINE;
			
		case _DIRT_PILLAR_TOP:
			return 3 + 2 * SCANLINE; // (3, 2)
		case _DIRT_PILLAR_BOT:
			return 4 + 2 * SCANLINE; // (4, 2)
		case _DIRT_PILLAR_LFT:
			return 3 + 3 * SCANLINE; // (3, 3)
		case _DIRT_PILLAR_RGT:
			return 4 + 3 * SCANLINE; // (4, 3)
			
		case _DIRT_CORN_UL:
			return 3 + 0 * SCANLINE;
		case _DIRT_CORN_UR:
			return 4 + 0 * SCANLINE;
		case _DIRT_CORN_BL:
			return 3 + 1 * SCANLINE;
		case _DIRT_CORN_BR:
			return 4 + 1 * SCANLINE;
			
		case _DIRT_BLOCK:
			return 5 + 2 * SCANLINE;
			
		case _FLIPBOX:
			return 0 + 13 * SCANLINE;
		case _COINBOX:
			return 0 + 12 * SCANLINE;
		case _NOTEBOX:
			return 4 + 12 * SCANLINE;
			
		case _PIPE_UP_TOP:
			return 0 + 4 * SCANLINE;
		case _PIPE_UP_MID:
			return 1 + 4 * SCANLINE;
			
		}
		
	}
	
}
