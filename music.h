/**
 * Svein Fagerheim
 * s181086
 * 
 * Plays a music-file from disc.
**/
#ifndef __MUSIC_H
#define __MUSIC_H

#include "bass.h"
#include <string>

namespace platformer
{
	class Music
	{	
		HSTREAM handle;
		
	public:
		Music();
		Music( std::string );
		~Music();
		
		void load( std::string );
		bool play();
		void stop();
		float changeVolume( float );
	};
}

#endif