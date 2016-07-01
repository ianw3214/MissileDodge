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
	missile(std::string s, float t, missileTypes mT = NORMAL) : sprite(s) {
		// intialize missile with a missile type
		init(0, 0, t, mT);
	};
	missile(int x, int y, std::string s, float t, missileTypes mT = NORMAL) : sprite(x, y, s) {
		// intialize missile with a missile type
		init(x, y, t, mT);
	};
	// getter function
	int getSpeed();
	missileTypes getMissileType();
	// class functions
	void update(SDL_Surface*, double);

private:

	int speed;
	void init(int, int, float, missileTypes mT);
	missileTypes missileType;

};