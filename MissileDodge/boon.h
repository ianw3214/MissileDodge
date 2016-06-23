#pragma once

#include "sprite.h"
#include "gameVars.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class boon : public sprite{

public:
	// inherit constructors
	boon(std::string s, boonTypes b) : sprite(s) {
		// intialize missile
		init(0, 0, b);
	};
	boon(int x, int y, std::string s, boonTypes b) : sprite(x, y, s) {
		// intialize missile
		init(x, y, b);
	};
	boonTypes getBoonType();
private:

	void init(int, int, boonTypes);
	boonTypes boonType;

};