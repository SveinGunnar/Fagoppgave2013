/*

*/

#include "mesh.h"

namespace platformer
{
	
	void Mesh::add(vec3& p, int w, unsigned int color)
	{
		// create quad
		mesh_vertex_t m[4] =
		{ //   x,       y,       z,  u, v, w,  c
			{ p.x,     p.y,     p.z, 0, 0, w, color },
			{ p.x + 1, p.y,     p.z, 1, 0, w, color },
			{ p.x + 1, p.y + 1, p.z, 1, 1, w, color },
			{ p.x,     p.y + 1, p.z, 0, 1, w, color }
		};
		
		for (int i = 0; i < 4; i++)
			mesh.push_back( m[i] );
		
	}
	
	mesh_vertex_t* Mesh::extract()
	{
		mesh_vertex_t* m = new mesh_vertex_t[mesh.size()];
		for (int i = 0; i < mesh.size(); i++)
			m[i] = mesh[i];
		
		this->finalSize = mesh.size();
		return m;
	}
	
	int Mesh::size()
	{
		return this->finalSize;
	}
	
}