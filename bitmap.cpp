/**
 * Svein Fagerheim
 * s181086
 * 
 * Bitmap implementation
**/

#include "bitmap.h"
#include "global.h"
#include <fstream>
#include <iostream>

namespace platformer
{
	Bitmap::Bitmap():buffer(0), width(0), height(0), bits(0)
	{
		
	}
	
	Bitmap::Bitmap(const std::string f)
	{
		load( f );
	}
	Bitmap::Bitmap(int w, int h, int b): buffer(0), width(w), height(h), bits(b)
	{
		
	}
	
	bool Bitmap::load(const std::string file)
	{
		#pragma pack(push, 1)
		typedef struct //Used to get the header data from the bmp file.
		{
			char magic[2];
			int filesize;
			short res1; 
			short res2;
			int pixeldata;
		// packed: make sure the alignment is packed tight
		} bmpheader_t;
		
		typedef struct //Used to get heigth, width and bits from the bmp file.
		{
			int headersize;
			int w;
			int h;
			short planes;
			short bits;
			// don't care about the rest
		} bmpdata_t;
		#pragma pack(pop)
		
		bmpheader_t bhead;
		bmpdata_t bdata;
		std::string test = file;
		std::ifstream File( test.c_str(), std::ios::in | std::ios::binary);
		
		if (!File)
		{	// Log: could not open file
			logger.write( LERR, "Could not open file" );
			return false;
		}
		
		File.read ( (char*) &bhead, sizeof(bmpheader_t) );
		File.read ( (char*) &bdata, sizeof(bmpdata_t) );
		
		width = bdata.w;
		height = bdata.h;
		bits = bdata.bits;
		
		int n = width * height;
		if (buffer) delete buffer;
		buffer = new color_rgba8_t[ n ];
		// seek to pixeldata relative to beginning of file
		File.seekg( bhead.pixeldata, std::ios::beg );
		
		int pad = (width * 3) & 3; // 4-byte padding
		int scanline = width * 3 + pad;
		
		char* scanbuffer = new char[scanline];
		char* buf = (char*)buffer;
		char* tmp;
		
		for (int y = 0; y < height; y++)
		{
			//buf = (char*)buffer + y * width * sizeof(color_rgba8_t);
			tmp = scanbuffer;
			
			File.read( tmp, scanline );
			
			for (int x = 0; x < width; x++)
			{
				buf[0] = tmp[0];
				buf[1] = tmp[1];
				buf[2] = tmp[2];
				buf[3] = 255;
				buf += 4; tmp += 3;
			}
			
		}
		
		// cleanup
		delete scanbuffer;
		File.close();
		
		return true;
	}
	
	Bitmap::~Bitmap()
	{
		delete buffer;
	}
	
	// written by AAW, s181087
	// splits a bitmap in a 1d continous memory array
	// of tiles used by GL_TEXTURE_2D_ARRAY (GL 3.x)
	void Bitmap::parse2D(int tw, int th)
	{
		if (!this->buffer) throw "Bitmap::parse2D() null pointer";
		
		int x, y, tx, ty;
		// nearest tilew/h multiple floor
		int maxx = (this->width / tw) * tw;
		int maxy = (this->height / th) * th;
		// buffers
		color_rgba8_t* newBuffer = new color_rgba8_t[maxx * maxy];
		color_rgba8_t *p, *n = newBuffer;
		
		// for each tile
		for (y = maxy-th; y >= 0; y -= th)
		for (x = 0; x < maxx; x += tw)
		{
			//p = this->buffer + (y + th-1) * this->width + x;
			p = this->buffer + y * this->width + x;
			
			// blit internal tile
			for (ty = 0; ty < th; ty++)
			{
				for (tx = 0; tx < tw; tx++)
					*n++ = *p++;
				
				p += this->width - tw;
				
			} // ty
			
		} // (x, y)
		
		// remove old buffer
		delete this->buffer;
		// replace with new buffer
		this->buffer = newBuffer;
		// use members for texture_2d_array flags
		this->bits   = (this->width / tw) * (this->height / th);
		this->width  = tw;
		this->height = th;
	}
	
	void Bitmap::replace(const unsigned int color, const unsigned int replacecolor)
	{	//Replaces one color witg another one in the picture.
		int n = width * height;
		for( int i = 0; i < n; i++ )
		{
			if( buffer[ i ] == color )
				buffer[ i ] = replacecolor;
		}
	}
	
	const unsigned int* Bitmap::data()
	{
		return buffer;
	}
	int Bitmap::getwidth()
	{
		return width;
	}
	int Bitmap::getheight()
	{
		return height;
	}
	int Bitmap::getbits()
	{
		return bits;
	}
	
	unsigned int Bitmap::makeColor(int r, int g, int b, int a)
	{	//Creates a color.
		unsigned int tall;
		unsigned char *c = (unsigned char*) &tall;
		c[0] = b;
		c[1] = g;
		c[2] = r;
		c[3] = a;

		return tall;
	}
}
