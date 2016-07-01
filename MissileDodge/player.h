#pragma once

#include "sprite.h"
#include "gameVars.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class player : public sprite {

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
	// class functions
	void eventHandler(SDL_Event);
	void update(SDL_Surface*, double);
	bool takeDamage(int);
	void setKeysNone();
	void heal(int);
	void boonHandler(boonTypes);
	void slowDown();

private:
	// variables to keep track of player stats
	unsigned int speed;
	int health;
	bool invincible;
	// variables to handle game logic
	bool leftDown, rightDown, spaceDown;
	int jumpCounter, yMove;
	int invincibleCounter;
	// init function
	void init(int, int);

	// timer functions for boon handling
	static Uint32 boon_invincible(Uint32, void *);
	static Uint32 boon_speed(Uint32, void *);
	static Uint32 condition_slow(Uint32, void *);

};