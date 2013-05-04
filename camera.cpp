/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Camera implementation
 * 
**/

#include "camera.h"

namespace platformer
{
	Camera::Camera() { }
	
	Camera::Camera(const vec3& p, const vec3& r)
	{
		this->position = p;
		//this->rotation = r;
	}
	
	void Camera::focus(const Player& player, float lerp)
	{
		const vec3 posv = player.getPosition();
		position.x = position.x * lerp + posv.x * (1.0 - lerp);
		position.y = position.y * lerp + posv.y * (1.0 - lerp); // + half height
	}
	
	void Camera::focus(const std::vector<Player>& pv, float lerp)
	{
		// focus N players
		int N = pv.size();
		if (N == 0) return;
		
		vec3 mv(0.0);
		for (int i = 0; i < N; i++)
		{
			const vec3 posv = pv[i].getPosition();
			mv = mv + posv;
		}
		mv /= N;
		
		position.x = position.x * lerp + mv.x * (1.0 - lerp); // 
		position.y = position.y * lerp + mv.y * (1.0 - lerp); // FIXME: + half player height
	}
	
}
