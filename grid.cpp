/**
 * Alf-Andre Walla
 * s181087
 * 
 * Grid implementation
 * 
**/

#include "grid.h"
#include <cmath>
#include "mesh.h"
#include "generator.h"
#include <stddef.h>     /* offsetof */
#include "toolbox.hpp"

namespace platformer
{
	
	Grid::Grid()
	{
		this->vbo = this->vao = 0;
		this->worldX = -BLOCKS_WIDTH / 2;
	}
	
	void Grid::update(vec3& camera, double tick)
	{
		int d = (int)(camera.x - worldX - BLOCKS_WIDTH / 2);
		bool createmesh = false;
		
		// clear makes function recreate the grid from scratch
		grid.clear();
		
		while (grid.size() < BLOCKS_WIDTH)
		{	// keep adding until full width
			grid.push_back( Generator::generate( worldX + grid.size(), tick ) );
			createmesh = true;
		}
		
		if (d != 0)
		{
			int dir = toolbox::signum(d);
			int max = std::abs(d);
			
			for (int i = 0; i < max; i++)
			{
				// shift terrain in direction dir
				if (dir > 0)
				{ // shift right first, avoid compacting
					grid.erase(grid.begin(), grid.begin() + 1);
					// generate tail
					grid.push_back( Generator::generate( worldX + grid.size(), tick ) );
					worldX++;
					createmesh = true;
				}
				else
				{	// shift left first, avoid compacting
					grid.pop_back();
					worldX--;
					// generate front
					grid.insert( grid.begin(), Generator::generate( worldX, tick ) );
					createmesh = true;
				}
				
			}
		}
		// create renderable mesh, but only if necessary
		if (createmesh)
		{
			postProcess();
			createMesh();
		}
		
	} // update
	
	void Grid::postProcess()
	{
		if (grid.size() == 0) return;
		
		// change blocks based on axis neighbors
		// for each block, find 4 neighbors, apply ruleset from Blocks
		int width = grid.size(); // assumption
		int tile;
		int NG[3][3], nx, ny, tx, ty;
		
		// iterate grid, ignore edges on both sides
		for (int x = 1; x < width-1; x++)
		for (int y = 0; y < grid[x].size(); y++)
		{
			tile = grid[x][y].id;
			
			for (nx = 0; nx < 3; nx++)
			for (ny = 0; ny < 3; ny++)
			{
				NG[nx][ny] = _AIR;
				
				tx = x - 1 + nx;
				if (tx >= 0 && tx < grid.size())
				{
					ty = y - 1 + ny;
					if (ty >= 0 && ty < grid[tx].size())
						NG[nx][ny] = grid[tx][ty].id;
				}
			}
			
			if (Block::isDirt(tile))
			{
				int cx = 1, cy = 1;
				
				// dirt block (air on all four sides)
				if ((NG[0][1] | NG[1][0] | NG[1][2] | NG[2][1]) == _AIR)
				{
					tile = _DIRT_BLOCK;
				}
				//   LEFT		 RIGHT		TOP
				else if ((NG[0][1] | NG[2][1] | NG[1][2]) == _AIR)
				{
					tile = _DIRT_PILLAR_TOP;
				}		// LEFT		  RIGHT		 BOT
				else if ((NG[0][1] | NG[2][1] | NG[1][0]) == _AIR)
				{
					tile = _DIRT_PILLAR_BOT;
				}
				else if ((NG[0][1] | NG[1][2] | NG[1][0]) == _AIR)
				{
					tile = _DIRT_PILLAR_LFT;
				}
				else if ((NG[2][1] | NG[1][2] | NG[1][0]) == _AIR)
				{
					tile = _DIRT_PILLAR_RGT;
				}
				else if (Block::isDirt(NG[0][1]) && Block::isDirt(NG[1][2]) && (NG[0][2] == _AIR))
				{
					tile = _DIRT_CORN_BR;
				}
				else if (Block::isDirt(NG[2][1]) && Block::isDirt(NG[1][2]) && (NG[2][2] == _AIR))
				{
					tile = _DIRT_CORN_BL;
				}
				else if (Block::isDirt(NG[0][1]) && Block::isDirt(NG[1][0]) && (NG[0][0] == _AIR))
				{
					tile = _DIRT_CORN_UR;
				}
				else if (Block::isDirt(NG[2][1]) && Block::isDirt(NG[1][0]) && (NG[2][0] == _AIR))
				{
					tile = _DIRT_CORN_UL;
				}
				else
				{
					//					LEFT					  RIGHT
					if (Block::isDirt(NG[0][1]) && Block::isDirt(NG[2][1]))
						cx = 1;
					else if (Block::isDirt(NG[0][1])) // LEFT
						cx = 2;
					else if (Block::isDirt(NG[2][1])) // RIGHT
						cx = 0;
					
					if (Block::isDirt(NG[1][0]) && Block::isDirt(NG[1][2]))
						cy = 1;
					else if (Block::isDirt(NG[1][2])) // TOP
						cy = 2;
					else if (Block::isDirt(NG[1][0])) // BOTTOM
						cy = 0;
					
					tile = _DIRT_TOP_L + cx + cy * 3;
				}
				
			}
			
			grid[x][y].id = tile;
		}
		
	}
	
	void Grid::createMesh()
	{
		// generate modern opengl containers, if they don't already exist
		// create a mesh, add quadrilateral primitives, 'extract' a memory
		// array of mesh (plain data), upload data to the gpu
		
		// generate mesh
		if (this->vao == 0)
		{
			glGenVertexArrays(1, &this->vao);
		}
		glBindVertexArray(this->vao);
		
		if (this->vbo == 0)
		{
			glGenBuffers(1, &this->vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER_ARB, this->vbo);
		
		// add as we go
		Mesh mesh;
		int tile;
		
		for (int x = 0; x < grid.size(); x++)
		for (int y = 0; y < grid[x].size(); y++)
		{
			// convert to texture tile-id
			tile = Block::toTexture( grid[x][y].id );
			
			// add to mesh
			vec3 v = vec3(x + worldX, y, 0.0);
			mesh.add( v, tile, 0 );
		}
		
		mesh_vertex_t* mesh_data = mesh.extract();
		this->vertices = mesh.size();
		
		// upload data
		glBufferData(GL_ARRAY_BUFFER_ARB, this->vertices * sizeof(mesh_vertex_t), mesh_data, GL_STATIC_DRAW_ARB);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		// vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex_t), (GLvoid*)offsetof(mesh_vertex_t, x));
		// texture
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex_t), (GLvoid*)offsetof(mesh_vertex_t, u));
		// color (normalized)
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(mesh_vertex_t), (GLvoid*)offsetof(mesh_vertex_t, color));
		
		glBindVertexArray(0);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		
		// cleanup
		delete mesh_data;
	}
	
	void Grid::render()
	{	// nothing to render (yet)
		if (this->vao == 0 || this->vertices == 0) return;
		
		// bind container, render using it, unbind
		glBindVertexArray(this->vao);
		
		glDrawArrays(GL_QUADS, 0, this->vertices);
		
		glBindVertexArray(0);
	}
	
	Block Grid::get(int x, int y)
	{
		int dx = x - worldX;
		int dy = y;
		
		if (dx < 0 || dx >= BLOCKS_WIDTH) throw "Grid::get(): X-coordinate out of bounds";
		if (dy < 0 || dy >= WORLD_HEIGHT) throw "Grid::get(): Y-coordinate out of bounds";
		
		return grid[dx][dy];
		
	}
	
}