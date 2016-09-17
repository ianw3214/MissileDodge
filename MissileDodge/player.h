#pragma once

#include "sprite.h"
#include "gameVars.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class player : public sprite {

	// enumeration to keep track of animation state of sprite
	enum spriteState { LEFT, RIGHT };	

public:
	// inherit constructors
	player(std::string s) : sprite(s) {
		// initialize player
		init(0, 0);
	};
	player(int x, int y, std::string s) : sprite(x, y, s) {
		// initialize player
		init(x, y);
	};

	// getter function
	int getHealth();
	bool getInvincibility();
	bool getSpeedBoost();

	// class functions
	void eventHandler(SDL_Event);
	void update(SDL_Surface*, double);
	bool takeDamage(int);
	void setKeysNone();
	void heal(int);
	void boonHandler(boonTypes);
	void slowDown();

	// override render function from sprite class
	bool render(SDL_Surface*);

	// function to wait for timer to finish at end
	void waitTimer();

private:

	// variables to keep track of player stats
	unsigned int speed;
	int health;
	bool invincible;
	// variables to handle game logic
	bool leftDown, rightDown, spaceDown;
	int yMove;
	int speedBoonCount, invincibleBoonCount;
	bool speedBoost;
	bool jumpCoolDown;	

	// init function
	void init(int, int);

	// sprite to handle player shadow
	sprite * shadow;

	// sprite sheet variables
	SDL_Rect SS_rect;	// keeps track of which part of the sprite sheet to copy
	spriteState cState;	// keeps track of the current animation state of the sprite
	SDL_TimerID spriteUpdateTimer;

	// timer functions for boon handling
	static Uint32 boon_invincible(Uint32, void *);
	static Uint32 boon_speed(Uint32, void *);
	static Uint32 condition_slow(Uint32, void *);

	// timer for jumping cooldown
	static Uint32 jump_cooldown(Uint32, void*);

	// timer for sprite state update 
	static Uint32 spriteUpdate(Uint32, void *);

};