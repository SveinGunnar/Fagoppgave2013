/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * Svein Gunnar Fagerheim, s181086
 * 
 * Player definition
 * 
**/

#ifndef __PLAYER_H
#define __PLAYER_H

#include "entity.h"
#include "vector.h"

namespace platformer
{
	
	typedef enum
	{
		POWER_SMALL_MARIO,
		POWER_BIG_MARIO,
		POWER_FLOWER_MOLTEN,
		POWER_FLOWER_ICE,
		POWER_FLYING_FEATHER,
		POWER_STAR
	} playerpower_t;
	
	typedef enum
	{
		PLO_AIR,
		PLO_GROUND,
		PLO_WATER
	} playerLocation;
	
	typedef enum
	{
		PST_STAND,
		PST_CROUNCH,
		PST_PRONE
	} playerStand;
	
	typedef enum
	{
		MFR_WALK,
		MFR_WALK1,
		
		MFR_HOLD,
		MFR_HOLD1,
		
		MFR_KICK,
		MFR_SLIDE,
		
		MFR_JUMP,
		MFR_FALL,
		
		MFR_TURN,
		MFR_DUCK,
		MFR_DUCKHOLD,
		
		MFR_RUN,
		MFR_RUN_FLY,
		
		MFR_LOOKUP,
		MFR_DEAD,
		MFR_WIN
		
	} marioframe_t;
	
	typedef struct
	{
		float x, y, z;
		float u, v, w;
		unsigned int color;
		
	} playervertex_t;
	
	class Player: public Entity
	{
		// state
		bool alive;
		playerpower_t power;
		
		// rendering
		marioframe_t frame;
		int framecounter;
		unsigned int vbo;
		// input method
		bool keyboard; // keyboard or joystick
		int joystick; // joystick number: GLFW_JOYSTICK0 + n
		
	public:
		Player(vec3 position);
		int  invincible;  // star
		bool facing; // left=false, right=true
		bool turning; // if the player is turning, show turning frame
		
		bool isAlive();
		void die();
		bool damage(); // true if player dies
		void powerup(playerpower_t);
		
		void setFrame();
		void render();
		
		static const float SMLSIZE_X, SMLSIZE_Y; // small mario
		static const float BIGSIZE_X, BIGSIZE_Y; // big mario
		static const float MAX_ACC, MAX_SPEED;
		static const float JUMP_POWER;
		static const int   INVINCIBLE_TICKS = 500; // length of star-powerup
	};
	
}
#endif