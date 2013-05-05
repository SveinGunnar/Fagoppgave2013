/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * Svein Gunnar Fagerheim, s181086
 * 
 * Game manager definition
 * handletransition - handles the transition from introscreen to game
 * handlestatechanges - handles all overall game-state changes, ie. from intro to transition to game
 * handleplayercontrols - checks for play inputs and applies some indirect physics (actual movement is handled by gamemechanics)
 * gamemechanics - tests movement for players and units, and does collision detection, among many (future) things
 * worldmanager - directly manages all aspects of the game not tied to rendering
 * 
**/

#ifndef __GAMEMAN_H
#define __GAMEMAN_H

#include "grid.h"
#include "player.h"
#include "soundman.h"
#include "unit.h"
#include <vector>

namespace platformer
{
	typedef enum
	{
		GS_INIT,
		GS_INTRO,
		GS_TRANSITION,
		GS_RUNNING,
		GS_PAUSED,
		GS_DEATH,
		
		GS_EXIT
		
	} gamestate_t;
	
	class Gameman
	{
		gamestate_t gamestate;
		gamestate_t laststate;
		bool statechanged;
		double numberOfTicks;
		
		std::vector<Player> players;
		std::vector<Unit> units;
		
		void handleTransition(double);
		void handleStateChanges(double, Soundman&);
		void handlePlayerControls(double);
		void gameMechanics(double, Soundman&);
		
		Grid grid; // terrain
		
	public:
		Gameman(gamestate_t);
		void worldManager(double, Soundman&);
		
		void addPlayer(const Player&);
		void renderPlayers();
		const std::vector<Player>& getPlayers() const;
		
		void addUnit(const Unit&);
		void renderUnits();
		
		gamestate_t getState();
		
		double getTransition() const;
		static const double TRANSITION_TICKS = 1600.0d;
		
		Grid& getGrid();
		
	};
}
#endif