/**
 * Svein Fagerheim
 * s181086
 * 
 * Loads a picture from a file and puts it in an Array so it can be used as a texture.
**/

#ifndef __BITMAP_H
#define __BITMAP_H

#include <string>

namespace platformer
{
	typedef unsigned int color_rgba8_t;
	
	class Bitmap
	{
	private:
		color_rgba8_t* buffer;
		int width, height, bits;
		
	public:
		Bitmap();
		Bitmap(const std::string);
		Bitmap(int w, int h, int bits);
		~Bitmap();
		
		bool load(const std::string file);
		void replace(const color_rgba8_t color, const color_rgba8_t replacecolor);
		void parse2D(int, int);
		
		// getters
		const color_rgba8_t* data();
		int getwidth();
		int getheight();
		int getbits();
		
		static color_rgba8_t makeColor(int r, int g, int b, int a);
		static const color_rgba8_t TRANSPARENT = 0;
		static const color_rgba8_t BLACK = 0xFF000000;
		static const color_rgba8_t WHITE = 0xFFFFFFFF;
		static const color_rgba8_t MAGENTA = 0xFFFF00FF;
	};
	
}

#endif
