/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Renderer / manager definition
 * 
 * init - sets initial opengl states
 * 
**/

#ifndef __RENDERMAN_H
#define __RENDERMAN_H

#include "matrix.h"
#include "camera.h"
#include "shaderman.h"
#include "textureman.h"

namespace platformer
{
	class Gameman; // forward
	
class Renderer
{
	private:
		Camera camera;
		Matrix matrot;  // R
		Matrix matview; // MV
		Matrix matproj; // P
		
		// shader manager
		Shaderman shaderman;
		// texture manager
		Textureman textureman;
		
		float FOV;
		float znear, zfar;
		
		double framerad;
		double frametick;
		
		void renderTitleBackground(float, float, float);
		void renderGameBackground(float, vec3&, float);
		void renderTitlescreen(Gameman&);
		void renderTransition(Gameman&);
		void renderScene(Gameman&);
		void renderPause();
		
		// sky-blue background color
		static const vec3 backgroundColor;
		
	public:
		Renderer();
		void init();
		void render(double dtime, Gameman&);
		void focus(const vec3& pos);
	
};

}

#endif
