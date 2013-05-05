/**
 * 
 * Platformer
 * 
 * Alf-Andre Walla, Svein Fagerheim
 * s181087			s181086
 * 
 * Controls:
 * Move: Left/Right arrows
 * Jump: Up-arrow
 * Start/pause: Enter
 * 
**/

#include "global.h"
#include "config.h"
#include <string>

#include "GL/glfw.h"
#include "renderman.h"
#include "soundman.h"
#include "gameman.h"
#include "input.h"

using namespace platformer;

// declarations
void mainloop(Renderer&, Gameman&, Soundman&);
Log logger("log.log");

int main(void)
{
	// start logging
	logger.write(LINFO, "Starting up...");
	
	// read config file
	const std::string configFile = "config.ini";
	if (!Config::load(configFile))
		logger.write(LWARN, "Could not find config file: " + configFile);
	
	// initialize renderer
	Renderer r;
	try
	{
		r.init();
	}
	catch (char const* errorstring)
	{
		logger.write(LERR, errorstring);
		logger.write(LERR, "Failed to initialize renderer... Exiting.");
		return 1;
	}
	
	// sound manager
	Soundman s;
	try
	{
		s.init();
	}
	catch (char const* errorstring)
	{
		logger.write(LERR, errorstring);
		logger.write(LERR, "Failed to initialize sound manager... Exiting.");
		return 1;
	}
	
	// input
	Input::init();
	
	// initialize game, starting with introduction screen
	Gameman g(GS_INTRO);
	
	// initial starting position for players
	vec3 startpos(100, 12, 0);
	r.focus(startpos);
	
	// add the first (and only) player
	Player one(startpos);
	g.addPlayer(one);
	
	// get stuck in main-loop
	mainloop(r, g, s);
	
	logger.write(LINFO, "Ending...");
	return 0;
}

void mainloop(Renderer& renderer, Gameman& gameman, Soundman& soundman)
{
	double dtime, t0, t1;
	t0 = t1 = glfwGetTime();
	
	const double render_ticks = 0.001; // 10ms granularity
	
	do
	{
		// variable delta-frame timing
		dtime = 1.0 + (t0 - (t1 + render_ticks)) / render_ticks;
		
		// rendering (sending the gamemanager as parameter 2)
		try
		{
			renderer.render(dtime, gameman);
		}
		catch (char const* errorstring)
		{
			logger.write(LERR, errorstring);
			logger.write(LERR, "Error during rendering, exiting...");
			break;
		}
		
		// world management & gameplay mechanics, etc.
		try
		{
			gameman.worldManager(dtime, soundman);
			
			// exit everything with exit gamestate
			if (gameman.getState() == GS_EXIT) break;
			
		}
		catch (char const* errorstring)
		{
			logger.write(LERR, errorstring);
			logger.write(LERR, "Error during execution of game mechanics, exiting...");
			break;
		}
		
		t1 = t0;
		t0 = glfwGetTime();
		
	} while (glfwGetWindowParam(GLFW_OPENED));
	
	// cleanup GLFW / threading (whenever that happens)
	glfwTerminate();
	//threadman.cleanup();
}
