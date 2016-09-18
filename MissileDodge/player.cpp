#include "player.h"

// getter functions
int player::getHealth() { return this->health; }
bool player::getInvincibility() { return this->invincible; }
bool player::getSpeedBoost() { return this->speedBoost; }

//function that calls for every update
void player::eventHandler(SDL_Event e) {

	if (e.type == SDL_KEYDOWN) {
		// cases for each key press
		switch (e.key.keysym.sym) {
		case SDLK_a:		// A key
		case SDLK_LEFT:		// left key
			// set the left down boolean to true
			leftDown = true;
			break;
		case SDLK_d:		// D key
		case SDLK_RIGHT:	// right key
			// set the right down boolean to true
			rightDown = true;
			break;
		case SDLK_SPACE:
			// set the space down boolean to true
			spaceDown = true;
			break;
		}
	}
	// if the user releases a key
	else if (e.type == SDL_KEYUP) {
		// cases for each key press
		switch (e.key.keysym.sym) {
		case SDLK_a:		// A key
		case SDLK_LEFT:		// left key
			// set the left down boolean to false
			leftDown = false;
			break;
		case SDLK_d:		// D key
		case SDLK_RIGHT:	// right key
			// set the right down boolean to false
			rightDown = false;
			break;
		case SDLK_SPACE:
			// set the space down boolean to false
			spaceDown = false;
			break;
		}
	}

}

// function that updates the player every frame
void player::update(SDL_Surface* gSurface, double delta) {

	// add to the players x coordinates if keys are pressed
	if (leftDown && !rightDown) {
		// update animation state
		cState = LEFT;
		this->rect.x -= static_cast<int>(speed * delta);
		// make sure to leave a margin from the side
		if(rect.x < 10){
			this->rect.x = 10;
		}
	}
	if (rightDown && !leftDown) {
		// update animation state
		cState = RIGHT;
		this->rect.x += static_cast<int>(speed * delta);
		// leave a margin
		if (rect.x > (constants::SCREEN_WIDTH - playerConstants::WIDTH - 10)) {
			this->rect.x = constants::SCREEN_WIDTH - playerConstants::WIDTH - 10;
		}
	}
	
	// handle the jump for the player
	if (spaceDown) {
		// if there is no jumping cool down currently
		if (!jumpCoolDown) {
			// set the jumping cool down to true
			jumpCoolDown = true;
			// add the jumping velocity to the player 
			yMove = playerConstants::BASE_JUMP_VELOCITY;
			// start the timer to end the jumping cooldown
			SDL_TimerID missileSpawnTimer = SDL_AddTimer(playerConstants::BASE_JUMP_COOLDOWN, jump_cooldown, this);
		}
	}

	// update the y coordinates of the player
	this->rect.y -= static_cast<int>(yMove * delta);
	// make sure it doesn't go beneath the ground
	if (this->rect.y > (constants::GROUND_LEVEL-playerConstants::HEIGHT)) {
		// set the y to the ground level
		this->rect.y = constants::GROUND_LEVEL - playerConstants::HEIGHT;
		// set ymove to 0
	}
	// apply gravity
	yMove -= static_cast<int>(constants::GRAVITY * delta);

	// update shadow position
	if (cState == LEFT) {
		shadow->setPos(this->rect.x, (constants::GROUND_LEVEL-6));
	}
	else if (cState == RIGHT) {
		shadow->setPos((this->rect.x+8), (constants::GROUND_LEVEL-6));
	}

	return;

}

// function that handles damage, returns false upon death
bool player::takeDamage(int dmg) {

	// boolean to return death state
	bool alive = true;

	// take damage if the player isn't invincible
	if(!invincible){
		// apply the damage to the health
		this->health -= dmg;

		// test if the player is alive
		if (health <= 0) {
			alive = false;
		}
	}

	// true if alive, false if dead
	return alive;

}

// function to clear the key inputs of player
void player::setKeysNone() {
	this->leftDown = false;
	this->rightDown = false;
}

// function that restores player health
void player::heal(int inp) {

	// if the resultant health is higher than base health
	if (this->health + inp > playerConstants::BASE_HEALTH) {
		// set the health to the max
		this->health = playerConstants::BASE_HEALTH;
	}
	else {
		this->health += inp;
	}

	return;

}

// function that turns the player invincible and sets the counter off
void player::boonHandler(boonTypes type) {

	switch (type) {
	case HEALTH: {
		// call the heal function with a default of 2 health
		heal(boonConstants::BASE_HEAL);
	} break;

	case INVINCIBLE: {
		// turn the hero invincible and set a timer to revert to normal
		this->invincible = true;
		invincibleBoonCount++;
		SDL_TimerID temp = SDL_AddTimer( boonConstants::DURATION, boon_invincible, this);
	} break;

	case SPEED: {
		// turn the hero invincible and set a timer to revert to normal
		this->speed = boonConstants::SPEED_BOOST;
		speedBoost = true;
		speedBoonCount++;
		SDL_TimerID temp = SDL_AddTimer(boonConstants::DURATION, boon_speed, this);
	} break;

	}

	return;
}

// function that makes the player slower from a gas missile
void player::slowDown() {

	this->speed *= missileConstants::gasMissile::SPEED_MULTIPLIER;
	SDL_TimerID temp = SDL_AddTimer(missileConstants::gasMissile::DURATION, condition_slow, this);

	return;
	
}

// function to initialize values for the missile
void player::init(int x, int y) {

	// initialize player stats
	this->speed = playerConstants::BASE_SPEED;
	this->health = playerConstants::BASE_HEALTH;
	this->invincible = false;
	this->speedBoonCount = 0;			// counters to keep track of how many boons of each type are active simultaniously
	this->invincibleBoonCount = 0;
	this->speedBoost = false;
	this->jumpCoolDown = false;
	// initialize player rect
	this->rect = { x, y, playerConstants::WIDTH, playerConstants::HEIGHT };

	// initialize copy rectangles dimensions
	SS_rect.w = playerConstants::WIDTH;
	SS_rect.h = playerConstants::HEIGHT;
	// initialize state of player animation to left
	cState = LEFT;

	// initialize sprite type
	type = PLAYER;

	// initialize a shadow for the player
	shadow = new sprite(this->rect.x, (constants::GROUND_LEVEL-6), "assets/SHADOW.png");

	// start sprite update timer
	spriteUpdateTimer = SDL_AddTimer(30, spriteUpdate, this);

	return;

}

// override the render function from sprite class
bool player::render(SDL_Surface * gSurface) {

	// render the player shadow first to put it behind player
	shadow->render(gSurface);

	// success flag
	bool success = true;

	// if the function failed
	if (SDL_BlitSurface(img, &SS_rect, gSurface, &rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// render boons on top of player sprite
	if (invincible) {
		sprite * temp = new sprite(rect.x + 50, rect.y-10, "assets/INVINCIBLE_EFFECT.png");
		temp->render(gSurface);
	}
	if (speed > playerConstants::BASE_SPEED) {
		sprite * temp = new sprite(rect.x-5, rect.y-10, "assets/SPEED_EFFECT.png");
		temp->render(gSurface);
	}

	// return the success boolean
	return success;

}

// timer functions
Uint32 player::boon_invincible(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;

	// take 1 off the boon count and if it is 0 then stop the invincibility
	temp->invincibleBoonCount -= 1;
	if (temp->invincibleBoonCount == 0) {
		temp->invincible = false;
	}
	
	return 0;

}

Uint32 player::boon_speed(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;

	// take 1 off the boon count and if it is 0 then return to normal speed
	temp->speedBoonCount -= 1;
	if (temp->speedBoonCount == 0) {
		temp->speedBoost = false;
		temp->speed = playerConstants::BASE_SPEED;
	}

	return 0;

}

Uint32 player::condition_slow(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;
	temp->speed = playerConstants::BASE_SPEED;

	return 0;
}

// timer for jumping cooldown
Uint32 player::jump_cooldown(Uint32, void* ptr) {
	
	// get the reference of the player object
	player * temp = (player*)ptr;

	temp->jumpCoolDown = false;

	return 0;

}

Uint32 player::spriteUpdate(Uint32 interval, void * ptr) {
	// get a reference to the player
	player * temp = (player*)ptr;

	// set the animation frame depending on the state of the hero
	switch (temp->cState) {
	case LEFT: {
		temp->SS_rect.x = 0;
		temp->SS_rect.y = 0;
	} break;
	case RIGHT: {
		temp->SS_rect.x = playerConstants::WIDTH;
		temp->SS_rect.y = 0;
	} break;
	}

	// update again at the same interval
	return interval;
}

// wait for all the player timers to finish to avoid multithreading problems
void player::waitTimer() {

	// player animation state update timer
	SDL_RemoveTimer(spriteUpdateTimer);

	return;

}