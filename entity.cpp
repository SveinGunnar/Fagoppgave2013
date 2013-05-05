/**
 * Alf-Andre Walla
 * s181087
 * 
 * Entity implementation
 * 
**/

#include "entity.h"
#include "vector.h"
#include "toolbox.hpp"
#include <cmath>

namespace platformer
{
	Entity::Entity( vec3 position, vec3 size, float maxspeed )
	{
		pos = position;
		this->size = size;
		this->maxspeed = maxspeed;
	}
	
	void Entity::setPosRel( vec3 delta )
	{
		this->pos = this->pos + delta;
	}
	
	void Entity::setSpdRel( vec3 delta )
	{
		this->spd = this->spd + delta;
	}
	
	void Entity::setAccRel( vec3 delta, vec3 clamp )
	{
		// avoid clamping when already outside clamp value
		if (std::abs(acc.x) > clamp.x);
		else
		if (std::abs(acc.x + delta.x) > clamp.x)
			acc.x = toolbox::signum(acc.x) * clamp.x;
		else
			acc.x += delta.x;
		
		if (std::abs(acc.y) > clamp.y);
		else
		if (std::abs(acc.y + delta.y) > clamp.y)
			acc.y = toolbox::signum(acc.y) * clamp.y;
		else
			acc.y += delta.y;
	}
	
	void Entity::friction(const vec3& friction)
	{
		this->spd = this->spd * friction;
		//this->acc *= 0.5;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	const vec3& Entity::getPosition() const
	{
		return pos;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	const vec3& Entity::getSpeed() const
	{
		return spd;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	void Entity::setSpeed(vec3& newspeed)
	{
		spd = newspeed;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	const vec3& Entity::getAcc() const
	{
		return acc;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	const vec3& Entity::getSize() const
	{
		return size;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	float Entity::getMaxSpeed()
	{
		return maxspeed;
	}
	
}
