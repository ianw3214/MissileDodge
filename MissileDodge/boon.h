#pragma once

#include "sprite.h"
#include "gameVars.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class boon : public sprite{

public:
	// inherit constructors
	boon(std::string s) : sprite(s) {
		// intialize missile
		init(0, 0);
	};
	boon(int x, int y, std::string s) : sprite(x, y, s) {
		// intialize missile
		init(x, y);
	};
	boonTypes boonType;
private:

	void init(int, int);

};