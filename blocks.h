/**
 *	Block, a single cell/tile in the world grid
 *	Block id definitions, class prototype
 *	
 *	s181087, Alf-Andre Walla
 *	
**/

#ifndef __BLOCKS_H
#define __BLOCKS_H

namespace platformer
{
	static const int WORLD_HEIGHT = 64;
	
	typedef unsigned char blockid_t;
	
	#define _AIR        0
	
	#define _DIRT_TOP_L  32
	#define _DIRT_TOP    33
	#define _DIRT_TOP_R  34
	#define _DIRT_LEFT   35
	#define _DIRT        36
	#define _DIRT_RIGHT  37
	#define _DIRT_BOT_L  38
	#define _DIRT_BOT    39
	#define _DIRT_BOT_R  40
	
	#define _DIRT_PILLAR_TOP 41
	#define _DIRT_PILLAR_BOT 42
	#define _DIRT_PILLAR_RGT 43
	#define _DIRT_PILLAR_LFT 44
	
	#define _DIRT_CORN_UL 45
	#define _DIRT_CORN_UR 46
	#define _DIRT_CORN_BL 47
	#define _DIRT_CORN_BR 48
	
	#define _DIRT_BLOCK   50
	
	#define _FLIPBOX  64
	#define _COINBOX  65
	#define _NOTEBOX  66
	
	#define _PIPE_UP_TOP 128
	#define _PIPE_UP_MID 129
	
	#define _WATER    200
	
#pragma pack(push, 1)
	class Block
	{
	public:
		Block(blockid_t i) : id(i) {}
		blockid_t id;
		
		static bool isDirt(blockid_t);
		static int toTexture(blockid_t);
		
	};
#pragma pack(pop)
	
}

#endif
