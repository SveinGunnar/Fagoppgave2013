/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Renderer implementation
 * 
 * Also: render_titlescreen.cpp
 * Also: render_gamescreen.cpp
 * 
**/

#include "renderman.h"

#include <cmath>
#include "background.h"
#include "config.h"
#include "gameman.h"
#include "global.h"
#include "grid.h"
#include "opengl.h"
#include "sprite.h"
#include "toolbox.hpp"

namespace platformer
{
	static const double PI = 4.0 * atan(1);
	const vec3 Renderer::backgroundColor(0.2, 0.5, 0.9);
	
	Renderer::Renderer()
	{
		this->frametick = 0.0;
		this->framerad  = 0.0;
	}
	
	void Renderer::init()
	{
		// initialize openGL
		ogl.init();
		
		// rendering settings
		this->FOV   = Config::get("frustum.fov", 61.0f);
		this->znear = Config::get("frustum.znear", 0.5f);
		this->zfar  = Config::get("frustum.zfar", 64.0f);
		
		// perspective projection
		matproj.perspective(this->FOV, ogl.SA, this->znear, this->zfar);
		
		// GL_COMPRESSED_RGBA setting
		//glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
		// GL_GENERATE_MIPMAP setting
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
		// perspective-correct interpolation setting
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		// buffer cleared color
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0);
		// (initial) depth settings
		glClearDepth(1.0);
		glDepthRange(0.0, 1.0);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		
		// alpha stencil test
		glAlphaFunc(GL_NOTEQUAL, 0.0);
		//glEnable(GL_ALPHA_TEST);
		
		// culling & shading
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT, GL_FILL);
		
		// blend function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// point sprites
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
		glTexEnvi( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );
		
		// texturing
		glEnable(GL_TEXTURE_2D);
		// seamless cubemaps globally
		//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		
		if (OpenGL::checkError())
		{
			logger.write(LERR, "@Renderman(): Some openGL state wasn't accepted! Exiting.");
			throw "Renderman::init(): General openGL error";
		}
		
		// initialize shader manager
		shaderman.init();
		
		// initialize texture manager
		textureman.init();
		
	}
	
	#include "render_titlescreen.cpp"
	#include "render_gamescreen.cpp"
	
	void Renderer::render(double time_d_factor, Gameman& gameman)
	{
		gamestate_t gamestate = gameman.getState();
		
		if (gamestate != GS_PAUSED)
		{
			// increment frame counters
			this->framerad += PI / 128.0 * time_d_factor;
			if (this->framerad >= 2 * PI) this->framerad -= 2 * PI;
			
			this->frametick += time_d_factor;
		}
		
		// clear buffers
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		// view matrix
		matview.identity();
		matview.translate(0.0, 0.0, -18.0);
		
		// MOVEME
		shaderman.bind(STANDARD_SHADER);
		shaderman.sendProjection(matproj);
		shaderman.sendView(matview);
		
		switch (gamestate)
		{
		case GS_INTRO:
			renderTitlescreen(gameman);
			break;
		case GS_TRANSITION:
			renderTransition(gameman);
			break;
		case GS_RUNNING:
			renderScene(gameman);
			break;
		case GS_PAUSED:
			renderScene(gameman);
			renderPause();
			break;
			
		default:
			throw "Renderer::render(): This gamestate is not implemented yet!";
		}
		
		// bind fullscreen texture, and copy screen
		textureman.bind(0, T_FULLSCREEN);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, ogl.SW, ogl.SH);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		// screen-space postprocessing shader
		shaderman.bind(FULLSCREEN_SHADER);
		shaderman.sendFrame(this->frametick);
		
		double mixlevel = 0.0;
		
		if (gamestate == GS_INTRO)
		{
			mixlevel = toolbox::min(1.0, this->frametick * 0.0007);
			mixlevel = 1.0 - mixlevel * mixlevel;
		} else
		if (gamestate == GS_TRANSITION)
		{
			const double d = Gameman::TRANSITION_TICKS / 2;
			double t = gameman.getTransition();
			if (t < d)
			{	// linear mix in
				mixlevel = t / d;
			} else {
				// linear mix out
				mixlevel = (Gameman::TRANSITION_TICKS - t) / d;
			}
			
		}
		
		GLint u_mixlevel = shaderman.getUniform("mixlevel");
		if (u_mixlevel+1) shaderman.sendFloat(u_mixlevel, mixlevel);
		
		GLint u_waves = shaderman.getUniform("waves");
		if (u_waves+1) shaderman.sendFloat(u_waves, mixlevel * 0.5);
		
		// rasterize fullscreen quad
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		
		glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glVertex2f(1.0f, 1.0f);
			glVertex2f(0.0f, 1.0f);
		glEnd();
		
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		
		// flip burgers / buffers
		glfwSwapBuffers();
		
		if (OpenGL::checkError())
		{
			throw "Renderer::render(): OpenGL state error";
		}
		
	}
	
	void Renderer::renderTransition(Gameman& gameman)
	{
		const double d = Gameman::TRANSITION_TICKS / 2;
		if (gameman.getTransition() < d)
		{
			renderTitlescreen(gameman);
		}
		else
		{
			renderScene(gameman);
		}
	}
	
	void Renderer::focus(const vec3& pos)
	{
		camera.position = pos;
	}
	
}
