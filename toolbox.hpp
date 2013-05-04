/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Toolbox template
 * Static template helper functions
 * 
**/

#ifndef __TOOLBOX_H
#define __TOOLBOX_H

namespace platformer
{
	namespace toolbox
	{
		template <typename T>
		int signum(T v)
		{
			return (T(0) < v) - (v < T(0));
		}
		
		template <class T, class R>
		inline T min(T a, R b)
		{
			return (a <= b ? a : b);
		}
		
		template <class T, class R>
		inline T max(T a, R b)
		{
			return (a >= b ? a : b);
		}
		
		//Function written by Svein Gunnar Fagerheim, s181086
		template <class T, class R>
		inline T clamp( T a, T b, R c )
		{
			if( c < a )
				return a;
			else if( c > b )
				return b;
			else
				return c;
		}
	}
}

#endif
