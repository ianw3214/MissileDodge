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
		speed = 10;
	};
	player(int x, int y, std::string s, SDL_Surface* g) : sprite(x, y, s, g) {
		// intialize speed
		speed = 7;
	};
	// class functions
	void eventHandler(SDL_Event);
	void update(SDL_Surface*);

private:

	int speed;
	bool leftDown, rightDown;
};