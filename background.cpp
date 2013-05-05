/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Background implementation
 * 
**/

#include "background.h"
#include "opengl.h"

namespace platformer
{
	
	Background::Background() : parallax(0) {};
	
	Background::Background(float p)
	{
		this->parallax = p;
	}
	
	void Background::render(float cx, float z, float scale)
	{
		vec3 pos(0.0, 0.0, z);
		render(cx, pos, scale);
	}
	
	void Background::render(float cx, vec3& pos, float scale)
	{
		float px = this->parallax * cx;
		
		for (float x = -scale; x < 2.0 * scale; x += scale)
		{
			// next rectangle
			glBegin(GL_QUADS);
				glTexCoord2f(px + 0.0f, 0.0f); glVertex3f(pos.x + x - scale * 0.5f, pos.y + scale * -0.5f, pos.z);
				glTexCoord2f(px + 1.0f, 0.0f); glVertex3f(pos.x + x + scale * 0.5f, pos.y + scale * -0.5f, pos.z);
				glTexCoord2f(px + 1.0f, 1.0f); glVertex3f(pos.x + x + scale * 0.5f, pos.y + scale *  0.5f, pos.z);
				glTexCoord2f(px + 0.0f, 1.0f); glVertex3f(pos.x + x - scale * 0.5f, pos.y + scale *  0.5f, pos.z);
			glEnd();
		}
	}
	
}