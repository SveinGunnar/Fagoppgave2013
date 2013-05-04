/**
 * Alf-Andre Walla
 * s181087
 * 
 * Grid definition, an array of renderable Blocks
 * update - potentially moves the grid left or right depending on camera position
 * postprocess - converts blocks into tilsets using predefined rules
 * createmesh - creates a renderable mesh of the grid
 * render - renders the grid mesh
 * 
**/

#ifndef __GRID_H
#define __GRID_H

#include "vector.h"

#include "opengl.h"
#include <vector>
#include "blocks.h"

namespace platformer
{
	
	class Grid
	{
		std::vector< std::vector<Block> > grid;
		int worldX;
		GLuint vao, vbo, vertices;
		
	public:
		Grid();
		
		void update(vec3&, double);
		void postProcess();
		void createMesh();
		void render();
		
		Block get(int, int);
		
		static const int BLOCKS_WIDTH  = 64;
	};
	
}

#endif
