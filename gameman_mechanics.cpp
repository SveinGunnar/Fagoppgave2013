/**
 * Alf-Andre Walla
 * s181087
 * 
 * Game mechanics for players and units
 * 
**/

// handles player and unit states, integrates movement / physics
// player -> unit/world interaction

void Gameman::gameMechanics(double dt, Soundman& soundman)
{
	if (gamestate != GS_RUNNING) return;
	
	// iterate players
	for (int pi = 0; pi < players.size(); pi++)
	{
		Player& p = players[pi];
		
		// invincibility countdown
		if (p.invincible) p.invincible--;
		
		// movement testing
		vec3 testx(p.getSpeed().x, 0.0, 0.0);
		vec3 testy(0.0, p.getSpeed().y, 0.0);
		
		Physics::integrate(grid, p, testx);
		Physics::integrate(grid, p, testy);
		
		bool ground = Physics::testGround(grid, p);
		
		// check if player jumped, somehow
		if (p.grounded == true && ground == false)
		{
			if (testy.y > 0.0)
			{	// BANZAI
				soundman.playSound(S_PLAYER_JUMP);
			}
		}
		p.grounded = ground;
		
		if (p.grounded)
			p.friction(Physics::GROUND_FRICTION);
		else
			p.friction(Physics::AIR_FRICTION);
		
		// player rendering-frame
		p.setFrame();
		
	} // next player
	
	// iterate units
	for (int ui = 0; ui < units.size(); ui++)
	{
		Unit& u = units[ui];
		
		// TODO:
		// physics testing etc.
		// check closeness to player
		// if close & hostile/enemy
		//      if player is moving down, the unit takes daage
		//      else player takes damage
		// if close & mushroom/coin/...
		//      apply effect
		
	} // next unit
	
}
