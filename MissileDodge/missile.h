#pragma once

#include "sprite.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class missile : public sprite {

public:
	// inherit constructors
	missile(std::string s, SDL_Surface* g) : sprite(s, g) {
		// intialize missile
		init(0,0);
	};
	missile(int x, int y, std::string s, SDL_Surface* g) : sprite(x, y, s, g) {
		// intialize missile
		init(x,y);
	};
	// class functions
	void update(SDL_Surface*);

private:

	int speed;
	void init(int, int);
	const int MISSILE_WIDTH = 40;
	const int MISSILE_HEIGHT = 80;

};