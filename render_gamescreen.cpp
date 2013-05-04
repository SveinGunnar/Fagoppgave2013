/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * In-game renderpath implementation
 * 
**/

void Renderer::renderGameBackground(float cx, vec3& position, float scale)
{
	// background layers
	glEnable(GL_TEXTURE_2D);
	
	Background bg_sky(0.20);
	textureman.bind(0, T_PILLARBG);
	bg_sky.render(cx, position, scale);
	
	Background bg_front(0.25);
	textureman.bind(0, T_NORMALBG);
	bg_front.render(cx, position, scale);
}

void Renderer::renderScene(Gameman& gameman)
{
	// focus camera on (all) players
	std::vector<Player> players = gameman.getPlayers();
	camera.focus(players, 0.95);
	if (camera.position.y < 12.0) camera.position.y = 12.0;
	
	vec3 vcam(camera.position);
	float parallax = vcam.x * 0.1;
	float z = -1.0;
	float bgscale = 22.0;
	
	vec3 bgpos(0.0, -(vcam.y - 12.0) * 0.5, z);
	
	// render background
	glEnable(GL_BLEND);
	
	renderGameBackground(parallax, bgpos, bgscale);
	
	Matrix transmat = matview;
	transmat.translate_xy(-vcam.x, -vcam.y);
	
	// terrain shader
	shaderman.bind(TILESET_SHADER);
	shaderman.sendProjection(matproj);
	shaderman.sendView(transmat);
	shaderman.sendFrame(this->frametick);
	
	textureman.bind(0, T_TILESET);
	
	// render grid
	gameman.getGrid().update(vcam, this->frametick);
	gameman.getGrid().render();
	
	// render players
	shaderman.bind(PLAYER_SHADER);
	shaderman.sendProjection(matproj);
	shaderman.sendView(transmat);
	
	textureman.bind(0, T_MARIO);
	
	gameman.renderPlayers();
	
	// render units
	gameman.renderUnits();
	
	glDisable(GL_BLEND);
}

void Renderer::renderPause()
{
	// render pause sprite
}
