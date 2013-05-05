/**
 * Svein Fagerheim
 * s181086
 *
 * Sound implementation
**/

#include "sound.h"
#include "toolbox.hpp"
#include "global.h"

namespace platformer
{
	Sound::Sound() {}
	
	Sound::~Sound()
	{	
		if (handle) BASS_SampleFree( handle );
	}
	
	Sound::Sound(std::string s):handle(0)
	{
		load(s);
	}
	
	void Sound::load(std::string s)
	{
		const int BASS_SIMULT_SAMPLES = 1;
		this->handle = BASS_SampleLoad(FALSE, s.c_str(), 0, 0, BASS_SIMULT_SAMPLES, BASS_SAMPLE_OVER_VOL);
		
		if ( BASS_ErrorGetCode() )
		{
			logger.write(LERR, "Sound::load(): BASS_SampleLoad returned error code.");
			throw "Sound::load(): BASS error";
		}
		
		if (this->handle == 0)
		{
			throw "Sound::load(): Invalid handle from BASS_SampleLoad";
		}
		
		HCHANNEL ch = BASS_SampleGetChannel( this->handle, FALSE );
		
		if (ch == 0)
		{
			logger.write(LERR, "Could not get channel handle for sample: " + s);
			throw "Sound::load(): Could not get valid channel handle";
		}
		
	}
	
	void Sound::play()
	{
		HCHANNEL ch = BASS_SampleGetChannel( this->handle, FALSE );
		
		if (ch == 0) throw "Sound::play(): Invalid handle from BASS_SampleGetChannel";
		
		BASS_ChannelPlay(ch, FALSE);
		
	}
	
	
	
	void Sound::play( vec3 v )
	{
		//Creates stereo sound.
		float L = v.length(); // distance from origin
		v.normalize();
		float pan = toolbox::min(1.0, v.x * L / MAX_PAN_DIST);
		float vol = toolbox::clamp(0.0,1.0, L / MAX_VOL_DIST);
		
		HCHANNEL ch=BASS_SampleGetChannel( handle, FALSE );
		BASS_ChannelSetAttribute( ch, BASS_ATTRIB_VOL, vol );
		BASS_ChannelSetAttribute( ch, BASS_ATTRIB_PAN, pan );

		if (!BASS_ChannelPlay(ch,FALSE))
			throw "fail";
	}
}


