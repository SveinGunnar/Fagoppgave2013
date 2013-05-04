/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * Svein Gunnar Fagerheim, s181086
 * 
 * Game manager implementation
 * 
**/

#include "gameman.h"
#include "glfw.h"
#include "input.h"
#include "physics.h"

namespace platformer
{
	Gameman::Gameman(gamestate_t gs)
	{
		this->laststate = GS_INIT;
		this->gamestate = gs;
		this->statechanged = true;
	}
	
	#include "gameman_mechanics.cpp"
	
	void Gameman::worldManager(double dt, Soundman& soundman)
	{
		// check inputs and build momentum for each player
		handlePlayerControls(dt);
		
		// test players / units against grid (among other things)
		gameMechanics(dt, soundman);
		
		handleStateChanges(dt, soundman);
		soundman.musicChange( dt );
	}
	
	void Gameman::handlePlayerControls(double dt)
	{
		for (int i = 0; i < players.size(); i++)
		{
			// test controls for player[i]
			vec3 v(0.0);
			vec3 spd = players[i].getSpeed();
			
			// pressing jump button & grounded
			if (Input::getKey(GLFW_KEY_UP) == KEY_PRESSED && players[i].grounded)
			{
				// acc.y must be net-negative
				if (players[i].grounded)
				{
					// accelerate up
					vec3 jump(0.0, Player::JUMP_POWER * dt, 0.0);
					players[i].setSpdRel(jump);
				}
			}
			
			if( Input::getKey(GLFW_KEY_LEFT) )
			{
				v.x = -1.0;
			}
			if( Input::getKey(GLFW_KEY_RIGHT) )
			{
				v.x += 1.0; // cancels out left, if pressed
			}
			
			// players intention vs momentum determines if the player is turning
			players[i].turning = false;
			if (v.x < 0.0 && spd.x > 0.0) players[i].turning = true;
			if (v.x > 0.0 && spd.x < 0.0) players[i].turning = true;
			
			// hardcoded exit shortcut (escape)
			if (Input::getKey(GLFW_KEY_ESC)) gamestate = GS_EXIT;
			
			if (Input::getKey(GLFW_KEY_ENTER) == KEY_PRESSED && gamestate != GS_TRANSITION )
			{
				Input::hold(GLFW_KEY_ENTER);
				
				// perform gamestate change
				this->laststate = gamestate;
				this->statechanged = true;
				
				switch (gamestate)
				{
					case GS_INTRO:
						this->gamestate = GS_TRANSITION;
						break;
					case GS_RUNNING:
						this->gamestate = GS_PAUSED;
						break;
					case GS_PAUSED:
						this->gamestate = GS_RUNNING;
						break;
					default:
						throw "Gameman::handlePlayerControls(): Gamestate not implemented here!";
				}
				
			} // KEY_ENTER
			
			// build/maintain momentum
			Physics::momentum( players[i], dt, v );
		}
	}
	
	void Gameman::handleStateChanges(double dt, Soundman& soundman)
	{
		// handle music, sounds and transitions for gamestate-changes
		if (this->statechanged)
		{
			this->statechanged = false;
			
			// do stuff, handle magic
			if (gamestate == GS_INTRO)
			{
				// play intro music
				soundman.playMusic(MUSIC_TITLE);
			}
			else
			if ( gamestate == GS_TRANSITION )
			{
				numberOfTicks = 0;
				
				// play start sound
				soundman.playSound(SND_START);
				// change music
				//soundman.stopMusic(MUSIC_TITLE);
				soundman.playMusic(M_SMW_YOSHISISLAND);
				
			}
			else
			if (laststate == GS_TRANSITION && gamestate == GS_RUNNING)
			{
				// change music
				//soundman.playMusic(M_SMW_YOSHISISLAND);
			}
			else
			if (laststate == GS_PAUSED || gamestate == GS_PAUSED)
			{
				// play pause/unpause sound
				soundman.playSound(SND_PAUSE);
			}
			
		}
		
		if (this->gamestate == GS_TRANSITION)
		{
			handleTransition(dt);
		}
		
	}
	
	void Gameman::handleTransition(double dt)
	{
		numberOfTicks += dt;
		
		if( numberOfTicks >= TRANSITION_TICKS )
		{
			// perform gamestate change
			this->laststate = gamestate;
			this->statechanged = true;
			this->gamestate = GS_RUNNING;
		}
	}
	
	double Gameman::getTransition() const
	{
		return numberOfTicks;
	}
	
	void Gameman::addPlayer(const Player& p)
	{
		players.push_back(p);
	}
	
	const std::vector<Player>& Gameman::getPlayers() const
	{
		return players;
	}
	
	void Gameman::renderPlayers()
	{
		for (int i = 0; i < players.size(); i++)
			players[i].render();
	}
	
	void Gameman::renderUnits()
	{
		for (int i = 0; i < units.size(); i++)
			units[i].render();
	}
	
	gamestate_t Gameman::getState()
	{
		return this->gamestate;
	}
	
	Grid& Gameman::getGrid()
	{
		return grid;
	}
}