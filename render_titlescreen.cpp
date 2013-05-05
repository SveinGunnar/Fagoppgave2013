/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Title-screen renderpath implementation
 * 
**/

void Renderer::renderTitleBackground(float x, float z, float scale)
{
	// background layers
	Background bg_sky(0.20);
	textureman.bind(0, T_SKYBG);
	bg_sky.render(x, z, scale);
	
	Background bg_front(0.25);
	textureman.bind(0, T_NORMALBG);
	bg_front.render(x, z, scale);
}

void Renderer::renderTitlescreen(Gameman& gameman)
{
	gamestate_t gamestate = gameman.getState();
	
	float x = this->frametick * 0.001;
	float z = -0.1;
	float bgscale = 22.0;
	
	// background fade-in
	const float RAMP_TIME = 800;
	
	if (this->frametick < RAMP_TIME)
	{
		float ramp = this->frametick / RAMP_TIME;
		ramp *= ramp;
		
		glColor4f(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0 - ramp);
	}
	else glColor4f(0.0, 0.0, 0.0, 0.0);
	
	// render background
	glEnable(GL_BLEND);
	
	renderTitleBackground(x, z, bgscale);
	
	glColor4f(0.0, 0.0, 0.0, 0.0);
	
	// title fade-in
	const float TITLE_IN = 300;
	const float TITLE_TIME = 600;
	const float INTROTEXT = 1200;
	
	if (this->frametick >= TITLE_IN)
	{
		float ramp = (this->frametick - TITLE_IN) / TITLE_TIME;
		if (ramp > 1.0) ramp = 1.0; // clamp
		else ramp *= ramp;
		
		// render titlescreen sprite
		vec3 spritepos(0.0, 24 - ramp * 20, 1.0);
		
		textureman.bind(0, T_TITLE);
		Sprite s(spritepos, SPRITE_CENTER_X | SPRITE_CENTER_Y);
		
		// render title sprite
		vec3 spritescale(12, 6, 0.0);
		s.render(spritescale);
		
		// render intro text, at intervals
		if (this->frametick >= INTROTEXT || gamestate == GS_TRANSITION)
		{
			const int INTERVAL = 32;
			int interval = (int)this->frametick / INTERVAL % INTERVAL;
			if (interval < INTERVAL / 2 || gamestate == GS_TRANSITION)
			{
				if (gamestate == GS_TRANSITION)
				{	// pull down intro text (fade-out-ish)
					double t = gameman.getTransition() / Gameman::TRANSITION_TICKS * 2.0;
					glColor4f(1.0, 1.0, 1.0, std::sqrt(t));
					spritepos = vec3(0.0, -4.0 - 16.0 * t, 1.0);
				}
				else
				{
					spritepos = vec3(0.0, -4.0, 1.0);
				}
				s = Sprite(spritepos, SPRITE_CENTER_X | SPRITE_CENTER_Y);
				
				textureman.bind(0, T_INTROTEXT);
				vec3 spritescale(10, 3.5, 0.0);
				s.render(spritescale);
				
				glColor4f(0.0, 0.0, 0.0, 0.0);
			}
		} // introtext
		
		// flat terrain
		shaderman.bind(TILESET_SHADER);
		shaderman.sendProjection(matproj);
		
		float camspeed = x * 2.0;
		
		Matrix transmat = matview;
		transmat.translate_xy(-camspeed, -20 + ramp * 8.0);
		
		shaderman.sendView(transmat);
		shaderman.sendFrame(this->frametick);
		
		textureman.bind(0, T_TILESET);
		
		// front terrain speed
		vec3 camera(camspeed, 0.0, 0.0);
		// create / regenerate terrain
		gameman.getGrid().update(camera, this->frametick);
		// render it
		gameman.getGrid().render();
		
	}
	
	glDisable(GL_BLEND);
	
}
