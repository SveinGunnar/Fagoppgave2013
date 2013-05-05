/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * GLFW Inputs definition
 * all events, such as keyboard(), is called by GLFW on glfwSwapBuffers
 * (or manually by calling glfwPollEvents())
 * Should be joystick handlers here as well, but ... TIME was not infinite
 * 
**/

#ifndef __INPUT_H
#define __INPUT_H

#include "GL/glfw.h"

namespace platformer
{
	typedef enum
	{
		KEY_RELEASED,
		KEY_PRESSED,
		KEY_LOCKED
	} keystate_t;
	typedef unsigned short key_t;
	
	class Input
	{
		static const int MAX_KEYS = 512;
		static key_t keys[MAX_KEYS];
		
		static void GLFWCALL keyboard(int key, int action);
		static void GLFWCALL keyboardType(int character, int action);
		
	public:
		static void init();
		
		static key_t getKey(int);
		static void hold(int);
	};
	
}

#endif
