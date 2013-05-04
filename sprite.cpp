/*

*/

#include "sprite.h"
#include "opengl.h"

namespace platformer
{
	
	Sprite::Sprite(const vec3& pos, int loc)
	{
		this->position = pos; // coordinates
		this->location = loc; // relative screen location
	}
	
	void Sprite::render(const vec3& scale)
	{
		float x = this->position.x;
		float y = this->position.y;
		float z = this->position.z;
		
		if (this->location & SPRITE_CENTER_X) x -= scale.x * 0.5;
		if (this->location & SPRITE_CENTER_Y) y -= scale.y * 0.5;
		
		// potential parallax:
		x += scale.z;
		
		// render quad
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x,           y,           z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + scale.x, y,           z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + scale.x, y + scale.y, z);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x,           y + scale.y, z);
		glEnd();
		
	}
	
	void SpriteTile::render(const vec3& scale, int tile)
	{
		float x = this->position.x;
		float y = this->position.y;
		float z = this->position.z;
		
		if (this->location & SPRITE_CENTER_X) x -= scale.x * 0.5;
		if (this->location & SPRITE_CENTER_Y) y -= scale.y * 0.5;
		
		// potential parallax:
		x += scale.z;
		
		// render quad
		glBegin(GL_QUADS);
			glTexCoord3f(0.0f, 0.0f, tile); glVertex3f(x,           y,           z);
			glTexCoord3f(1.0f, 0.0f, tile); glVertex3f(x + scale.x, y,           z);
			glTexCoord3f(1.0f, 1.0f, tile); glVertex3f(x + scale.x, y + scale.y, z);
			glTexCoord3f(0.0f, 1.0f, tile); glVertex3f(x,           y + scale.y, z);
		glEnd();
		
	}
	
	void Sprite::setPosition(const vec3& pos)
	{
		this->position = pos;
	}
	
}
