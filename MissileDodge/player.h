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
	// class functions
	void eventHandler(SDL_Event);
	void update(SDL_Surface*, double);
	bool takeDamage(int);
	void setKeysNone();

private:
	// integers to keep track of player stats
	int speed, health;
	// variables to handle game logic
	bool leftDown, rightDown, spaceDown;
	int jumpCounter, yMove;
	// init function
	void init(int, int);
};