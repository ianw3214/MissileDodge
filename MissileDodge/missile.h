#pragma once

#include "sprite.h"
#include "gameVars.h"

#include <string>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>

class missile : public sprite {

public:
	// inherit constructors
	missile(std::string s, float t) : sprite(s) {
		// intialize missile
		init(0, 0, t);
	};
	missile(int x, int y, std::string s, float t) : sprite(x, y, s) {
		// intialize missile
		init(x, y, t);
	};
	// getter function
	int getSpeed();
	// class functions
	void update(SDL_Surface*, double);

private:

	int speed;
	void init(int, int, float);

};