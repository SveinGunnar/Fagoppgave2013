/**
 *	Alf-Andre Walla
 *	s181087
 *	
 *	Shader manager definition
 *	
**/

#ifndef __SHADERMAN_H
#define __SHADERMAN_H

#include "shader.h"
#include <string>

namespace platformer
{
	typedef enum
	{
		STANDARD_SHADER,
		TILESET_SHADER,
		PLAYER_SHADER,
		
		FULLSCREEN_SHADER,
		
		NUMBER_OF_SHADERS
		
	} shaderlist_t;
	
	class Shaderman
	{
		Shader shaders[NUMBER_OF_SHADERS];
		int lastShader;
		
	public:
		Shaderman();
		void init();
		
		void sendProjection(Matrix&);
		void sendView(Matrix&);
		void sendFrame(float);
		void sendFloat(int, float);
		int getUniform(std::string);
		
		void bind(shaderlist_t);
		
	};
}

#endif
