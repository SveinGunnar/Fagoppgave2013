/*

*/

#ifndef __MESH_H
#define __MESH_H

#include "opengl.h"
#include "vector.h"
#include <vector>

namespace platformer
{
	typedef struct
	{
		GLfloat x, y, z;
		GLfloat u, v, w;
		GLuint color;
		
	} mesh_vertex_t;
	
	class Mesh
	{
	private:
		std::vector< mesh_vertex_t > mesh;
		int finalSize;
		GLfloat offsetX, offsetY;
		
	public:
		void add(vec3& p, int w, unsigned int color);
		void offset(GLfloat x, GLfloat y);
		
		mesh_vertex_t* extract();
		int size();
	};
}

#endif
