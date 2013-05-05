/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Unit implementation
 * 
**/

#include "unit.h"
#include "opengl.h"

namespace platformer
{
	// TODO
	
	void Unit::render()
	{
		float w = (float)getFrame();
		vec3 pos = getPosition();
		
		glBegin(GL_QUADS);
			glTexCoord3f(0.0, 0.0, w); glVertex3f(pos.x,       pos.y, pos.z);
			glTexCoord3f(1.0, 0.0, w); glVertex3f(pos.x + 1.0, pos.y, pos.z);
			glTexCoord3f(1.0, 1.0, w); glVertex3f(pos.x + 1.0, pos.y + 1.0, pos.z);
			glTexCoord3f(0.0, 1.0, w); glVertex3f(pos.x,       pos.y + 1.0, pos.z);
		glEnd();
		
				
	}
	
}