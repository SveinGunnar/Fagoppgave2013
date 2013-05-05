/**
 * Svein Fagerheim
 * s181086
 *
 * Music implementation
**/

#include "music.h"
#include "toolbox.hpp"

namespace platformer
{
	Music::Music() {}
	
	Music::Music(std::string s):handle(0)
	{
		load(s);
	}
	
	Music::~Music()
	{
		if (handle) BASS_StreamFree( handle );
	}
	
	void Music::load( std::string s )
	{
		this->handle = BASS_StreamCreateFile(FALSE, s.c_str(), 0, 0, BASS_SAMPLE_LOOP);
		
		if ( BASS_ErrorGetCode() )
		{
			//logger.write(LERR, "Music::load(): BASS_SampleLoad returned error code.");
			throw "Music::load(): BASS error";
		}
	}
	
	bool Music::play()
	{
		if (!handle) 
			throw "fail";
		BASS_ChannelPlay(handle, TRUE);
	}
	
	void Music::stop()
	{
		BASS_ChannelStop(handle);
	}
	
	float Music::changeVolume( float change )
	{
		//Clamp is used to ensure that volume i between 0 and 1.
		float newVol = toolbox::clamp(0.0,1.0, change);
		BASS_ChannelSetAttribute( handle, BASS_ATTRIB_VOL, newVol );
		
		return newVol;
	}

}