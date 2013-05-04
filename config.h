/**
 * Svein Fagerheim
 * s181086
 *
 * Config.h
 * Loads variables from config-file and puts them in a keymap.
**/

#ifndef __CONFIG_H
#define __CONFIG_H

#include <map>
#include <utility>
#include <string>

namespace platformer
{
	class Config
	{
		static std::map<std::string, std::string> kv;
		
	public:
		static bool get(const std::string, const bool);
		static int get(const std::string, const int);
		static float get(const std::string, const float);
		static std::string get(const std::string, const std::string);

		//Changing the value in the key map.
		template <typename T>
		static void set( std::string v, T b )
		{
			if ( Config::kv.find(v) == Config::kv.end()) 
				return;
			
			kv[v] = b;
		}
		static bool load( std::string file );
	};
}

#endif
