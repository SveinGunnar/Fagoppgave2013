/**
 * Svein Fagerheim
 * s181086
 *
 * Config implementation
**/

#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace platformer
{	
	std::map<std::string, std::string> Config::kv;
	
	//Gets a bool value from map
	bool Config::get(const std::string v, const bool def)
	{
		if ( Config::kv.find(v) == Config::kv.end()) 
			return def;
		bool b;
		std::istringstream convert( kv[v] );
		if ( !(convert >> b) )
			return def;
		return b;
	}
	
	//Gets an int value from map
	int Config::get(const std::string v, const int def)
	{
		if ( Config::kv.find(v) == Config::kv.end()) 
			return def;
		int i;
		std::istringstream convert( kv[v] );
		if ( !(convert >> i) )
			return def;
		return i;
	}
	
	//Gets a float value from map
	float Config::get(const std::string v, const float def)
	{
		if ( Config::kv.find(v) == Config::kv.end()) 
			return def;
		float f;
		std::istringstream convert( kv[v] );
		if ( !(convert >> f) )
			return def;
		return f;
	}
	//Gets a string value from map
	std::string Config::get(const std::string v, const std::string def)
	{
		if ( Config::kv.find(v) == Config::kv.end()) 
			return def;
		return kv[v];
	}
	//Loading the config file into the keymap.
	bool Config::load( std::string f )
	{
		std::fstream filestream;
		filestream.open( f.c_str(), std::fstream::in );
		
		if (!filestream) return false; // could not open file
		
		//Reads one line in config file at a time and place it in the map.
		while( !filestream.eof() )
		{
			char line[256];
			filestream.getline( line, 256 );
			std::string test( line );
			std::string en;
			std::string to;
			bool temp = true;
			//en is the value name and to is the value.
			for ( std::string::iterator it=test.begin(); it!=test.end(); ++it)
			{
				if( *it == '#' ) 
					break;
				if( *it == '=' )
					temp = false;
				if( *it != '=' && *it != ' ' )
				{
					if(temp)
						en += *it;
					else
						to += *it;
				}
			}
			if( en.length() > 0)
				kv.insert( std::pair<std::string,std::string>(en,to) );
		}
		filestream.close();
		return true;
	}

}









