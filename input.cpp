/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * GLFW inputs implementation
 * 
**/

#include "input.h"
#include <iostream>

namespace platformer
{
	key_t Input::keys[MAX_KEYS] = {KEY_RELEASED};
	
	void Input::init()
	{
		glfwSetKeyCallback(&keyboard);
		glfwSetCharCallback(&keyboardType);
		
	}
	
	void GLFWCALL Input::keyboard(int key, int action)
	{
		// action: GLFW_PRESS or GLFW_RELEASE
		keys[key] = (action == GLFW_PRESS) ? KEY_PRESSED : KEY_RELEASED;
		
	}
	
	void GLFWCALL Input::keyboardType(int character, int action)
	{
		// typing!
	}
	
	key_t Input::getKey(int key)
	{
		if (key < 0 || key >= MAX_KEYS) throw "Input::getKey(): Invalid key value";
		return keys[key];
	}
	
	void Input::hold(int key)
	{
		keys[key] = KEY_LOCKED;
	}
	
}
