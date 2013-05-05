/**
 * Svein Fagerheim
 * s181086
 *
 * Loads a sound-file into memory an play it from memory when needed.
**/

#ifndef __SOUND_H
#define __SOUND_H

#include "bass.h"
#include <string>
#include "vector.h"

namespace platformer
{
	class Sound
	{
		HSAMPLE handle;
		
	public:
		Sound();
		Sound(std::string);
		~Sound();
		
		void load(std::string);
		void play( vec3 );
		void play();
		
		static const float MAX_PAN_DIST = 100.0;
		static const float MAX_VOL_DIST = 25.0;
	};
}

#endif
