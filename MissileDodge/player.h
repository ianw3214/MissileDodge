#pragma once

#include "sprite.h"
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
	void update(SDL_Surface*);
	bool takeDamage(int);

private:
	int speed, health;
	bool leftDown, rightDown;
	const int PLAYER_WIDTH = 40;
	const int PLAYER_HEIGHT = 80;
	const int BASE_SPEED = 7;
	const int BASE_HEALTH = 3;
	// init function
	void init(int, int);
};