#pragma once

#include "sprite.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class player : public sprite {

public:
	// inherit constructors
	player(std::string s, SDL_Surface* g) : sprite(s, g) {
		// intialize speed
		speed = 7;
		// initialize player rect
		this->rect = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	};
	player(int x, int y, std::string s, SDL_Surface* g) : sprite(x, y, s, g) {
		// intialize speed
		speed = 7;
		// initialize player rect
		this->rect = { x, y, PLAYER_WIDTH, PLAYER_HEIGHT };
	};
	// class functions
	void eventHandler(SDL_Event);
	void update(SDL_Surface*);

private:
	int speed;
	bool leftDown, rightDown;
	const int PLAYER_WIDTH = 40;
	const int PLAYER_HEIGHT = 80;
};