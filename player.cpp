/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * Svein Gunnar Fagerheim, s181086
 * 
 * Game manager implementation
 * 
**/

#include "player.h"
#include <stddef.h>     /* offsetof */
#include "opengl.h"
#include "toolbox.hpp"
#include <cmath>

namespace platformer
{
	const float Player::SMLSIZE_X = 1.0;
	const float Player::SMLSIZE_Y = 1.0;
	
	const float Player::BIGSIZE_X = 1.0;
	const float Player::BIGSIZE_Y = 2.0;
	
	const float Player::MAX_SPEED = 0.15;
	const float Player::JUMP_POWER = 0.06;
	
	Player::Player( vec3 position ):
	Entity( position, vec3(SMLSIZE_X, SMLSIZE_Y, 0), MAX_SPEED )
	{
		alive = true;
		power = POWER_SMALL_MARIO;
		invincible = false;
		
		keyboard = true;
		
		frame = MFR_WALK;
		framecounter = 0;
		facing = true;
	}
	
	bool Player::isAlive()
	{
		return alive;
	}
	
	void Player::die()
	{
		alive = false;
	}
	
	//Function written by Svein Gunnar Fagerheim, s181086
	bool Player::damage()
	{
		//If player is invincible, then nothing happens
		if( invincible )
			return false;
		//Player goes from a special power to being just big.
		if( power >= POWER_FLOWER_MOLTEN )
		{
			power = POWER_BIG_MARIO;
			return false;
		}
		else //Player goes from big to small.
		if( power == POWER_BIG_MARIO )
		{
			power = POWER_SMALL_MARIO;
			return false;
		}
		else //Player dies.
		if( power == POWER_SMALL_MARIO )
		{
			return true;
		}
	}
	
	void Player::powerup(playerpower_t p)
	{
		if (p == POWER_STAR)
		{
			invincible = INVINCIBLE_TICKS;
			return;
		}
		// no downgrades!
		if (power > POWER_BIG_MARIO && p <= POWER_BIG_MARIO) return;
		
		this->power = p;
		
		// FIXME: play sound.. (but not here!)
	}
	
	void Player::setFrame()
	{
		bool hasspeed = std::abs(getSpeed().x) > 0.005;
		
		if (grounded == false)
		{	// jumping frame
			frame = MFR_JUMP;
		}
		else if (turning)
		{	// turning frame
			frame = MFR_TURN;
		}
		else if (hasspeed)
		{	// walking animation
			frame = (framecounter / 4 % 4) ? MFR_WALK : MFR_WALK1;
			framecounter++;
		}
		else
		{	// idle frame
			frame = MFR_WALK;
		}
		
		if (hasspeed) facing = (getSpeed().x > 0.0);
	}
	
	void Player::render()
	{
		// determine frame number
		float tframe = this->frame;
		float bframe = tframe + 16; // next scanline
		// color, star effect only
		unsigned int color = 0;
		if ((invincible / 4) % 4) color = 0xFFCC33FF;
		
		if (this->vbo == 0)
		{
			glGenBuffers(1, &this->vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER_ARB, this->vbo);
		
		// create 2 quads
		const int vertices = 8;
		vec3 pos = getPosition();
		
		playervertex_t pv[vertices] =
		{ //   x,         y,         z,    u, v,    w,     c
			// lower
			{ pos.x,     pos.y,     pos.z, 0, 0, bframe, color },
			{ pos.x + 1, pos.y,     pos.z, 1, 0, bframe, color },
			{ pos.x + 1, pos.y + 1, pos.z, 1, 1, bframe, color },
			{ pos.x,     pos.y + 1, pos.z, 0, 1, bframe, color },
			// upper
			{ pos.x,     pos.y + 1, pos.z, 0, 0, tframe, color },
			{ pos.x + 1, pos.y + 1, pos.z, 1, 0, tframe, color },
			{ pos.x + 1, pos.y + 2, pos.z, 1, 1, tframe, color },
			{ pos.x,     pos.y + 2, pos.z, 0, 1, tframe, color }
		};
		
		if (facing == false)
		{	// flip x on both quads
			for (int i = 0; i < 4; i++)
			{
				pv[i].u = pv[4 + i].u = 1 - pv[4 + i].u;
			}
		}
		
		// upload data
		glBufferData(GL_ARRAY_BUFFER_ARB, vertices * sizeof(playervertex_t), &pv[0], GL_STREAM_DRAW_ARB);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		// vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(playervertex_t), (GLvoid*)offsetof(playervertex_t, x));
		// texture
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(playervertex_t), (GLvoid*)offsetof(playervertex_t, u));
		// color (normalized)
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(playervertex_t), (GLvoid*)offsetof(playervertex_t, color));
		
		// render call
		glDrawArrays(GL_QUADS, 0, vertices);
		
		// unbind states
		glBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		
		if (OpenGL::checkError())
		{
			throw "Player::render(): OpenGL state error";
		}
		
	}
	
}
