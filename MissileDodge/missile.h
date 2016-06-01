#pragma once

#include "sprite.h"
#include "gameVars.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class missile : public sprite {

public:
	// inherit constructors
	missile(std::string s) : sprite(s) {
		// intialize missile
		init(0,0);
	};
	missile(int x, int y, std::string s) : sprite(x, y, s) {
		// intialize missile
		init(x,y);
	};
	// class functions
	void update(SDL_Surface*);

private:

	int speed;
	void init(int, int);

};