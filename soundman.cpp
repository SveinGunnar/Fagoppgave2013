/**
 * Svein Fagerheim
 * s181086
 *
 * Soundman implementation
**/

#include "soundman.h"
#include <string>

#include <stdlib.h>
#include <time.h>

namespace platformer
{
	void Soundman::init()
	{
		if (!BASS_Init( -1, 44100,  0,   0,  NULL ))
			throw "Soundman(): Error initializing BASS library";
		
		soundPlaylist();
		musicPlaylist();
		
		prevMusic = MUSIC_NOTHING; 
		currMusic = MUSIC_NOTHING;
	}
	
	Soundman::~Soundman()
	{
		BASS_Free();
	}
	
	void Soundman::playMusic(named_music_t m)
	{
		if( currMusic != prevMusic && prevMusic != MUSIC_NOTHING )
		{
			music[prevMusic].stop();
		}
		prevMusic = currMusic;
		this->music[m].play();
		currMusic = m;
		
		//muting the sound
		vol = 0;
		this->music[currMusic].changeVolume( vol );
	}
	
	void Soundman::stopMusic(named_music_t m)
	{
		this->music[m].stop();
		prevMusic = currMusic;
		currMusic = MUSIC_NOTHING;
	}
	
	void Soundman::playSound(named_sound_t s, vec3 v)
	{
		this->sounds[s].play( v );
	}
	
	void Soundman::playSound(named_sound_t s)
	{
		this->sounds[s].play();
	}
	
	void Soundman::soundPlaylist()
	{
		// NOTE: cannot initialize with Sound("") because it would create
		// a temporary object, copy it over, and destroy the temporary object,
		// calling its destructor: Which removes it from BASS internally!
		
		sounds[S_PLAYER_DIED].load("sound/player-died.mp3");
		sounds[S_PLAYER_GROW].load("sound/player-grow.mp3");
		sounds[S_PLAYER_SHRINK].load("sound/player-shrink.mp3");
		sounds[S_PLAYER_JUMP].load("sound/player-jump.mp3");
		
		sounds[SND_PAUSE].load("sound/pause.mp3");
		sounds[SND_START].load("sound/level-select.mp3");
	}
	
	void Soundman::musicPlaylist()
	{
	/*	music[M_SMW_BOSS].load("music/smw-boss.mp3");
		music[M_SMW_BOWSERCASTLE].load("music/smw-bowserscastle.mp3");
		music[M_SMW_CASTLE].load("music/smw-castle.mp3");
		music[M_SMW_CAVE].load("music/smw-cave.mp3");
		music[M_SMW_FORESTOFILLUSION].load("music/smw-forestofillusion.mp3");
		music[M_SMW_GHOSTHOUSE].load("music/smw-ghosthouse.mp3");
		music[M_SMW_OVERWORLD].load("music/smw-overworld.mp3");
		music[M_SMW_SKY].load("music/smw-sky.mp3");
		music[M_SMW_SPECIAL].load("music/smw-special.mp3");
		music[M_SMW_STARROAD].load("music/smw-starroad.mp3");
		music[M_SMW_SWITCH].load("music/smw-switch.mp3");
		music[M_SMW_VANILLADOME].load("music/smw-vanilladome.mp3");
		music[M_SMW_WATER].load("music/smw-water.mp3");
		music[M_SMW_WORLDMAP].load("music/smw-worldmap.mp3"); */
		music[M_SMW_YOSHISISLAND].load("music/smw-yoshisisland.mp3");
		music[MUSIC_TITLE].load("music/title.mp3");
	}
	
	void Soundman::musicChange( double dtime)
	{	
		if( prevMusic == currMusic ) return;
		
		//volume change each time function is called.
		float change = 0.01;
		float dt = static_cast<float>(dtime);
		float prevVol = -1, currVol = -1;
		
		vol += change;
		
		//turning the volume on the previous track down
		if( prevMusic != MUSIC_NOTHING )
		{
			prevVol = music[prevMusic].changeVolume( 1 - vol );
		}
		//turning the volume on the new track up
		if( currMusic != MUSIC_NOTHING )
		{
			currVol = music[currMusic].changeVolume( vol  );
		}
		
		if( vol >= 1 )
		{
			music[prevMusic].stop();
			prevMusic = currMusic;
		}
	}
	
	//Play a random music
	int Soundman::randomMusic()
	{
		srand (time(NULL));
		int i = rand() % NUM_STREAMS;
	//	playMusic( i );
		
		return i;
	}

}