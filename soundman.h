/**
 * Svein Fagerheim
 * s181086
 *
 * SoundMan controls sound and music in the game.
**/

#ifndef __SOUNDMAN_H
#define __SOUNDMAN_H

#include "sound.h"
#include "music.h"
#include "vector.h"

namespace platformer
{	
	
	typedef enum
	{
		S_PLAYER_DIED,
		S_PLAYER_GROW,
		S_PLAYER_SHRINK,
		S_PLAYER_JUMP,
	
		SND_PAUSE,
		SND_START,
		
		NUM_SOUNDS
	} named_sound_t;
	
	typedef enum
	{	
	//	M_SMW_BOSS,
	//	M_SMW_BOWSERCASTLE,
	//	M_SMW_CASTLE,
	//	M_SMW_CAVE,
	//	M_SMW_FORESTOFILLUSION,
	//	M_SMW_GHOSTHOUSE,
	//	M_SMW_OVERWORLD,
	//	M_SMW_SKY,
	//	M_SMW_SPECIAL,
	//	M_SMW_STARROAD,
	//	M_SMW_SWITCH,
	//	M_SMW_VANILLADOME,
	//	M_SMW_WATER,
	//	M_SMW_WORLDMAP,
		M_SMW_YOSHISISLAND,
		MUSIC_TITLE,
		
		NUM_STREAMS
	} named_music_t;
	
	const int MUSIC_NOTHING = -1;
	
	class Soundman //Sound Manager
	{
		void soundPlaylist();
		void musicPlaylist();
		Sound sounds[NUM_SOUNDS];
		Music music[NUM_STREAMS];
		
		int prevMusic, currMusic;
		float vol;
		
	public:
		~Soundman();
		void init();
		
		void playMusic(named_music_t);
		void stopMusic(named_music_t);
		
		void playSound(named_sound_t, vec3 );
		void playSound(named_sound_t);
		
		void musicChange( double );
		int randomMusic();
	};
}

#endif
