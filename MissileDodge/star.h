#pragma once

#include "sprite.h"
#include "gameVars.h"

#include <string>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>

class star : public sprite {

public:
	// constructor
	star(std::string);
	// render function for the star
	bool render(SDL_Surface*);
	// flag that values to true if animation is done
	bool isDoneAnimation;
private:
	// integer to keep track of animation state of star
	int animState;
	// initialize function
	void init();
	// rect to keep track of current animation state
	SDL_Rect ss_star;

	// constant variables
	const int TILE_HEIGHT = 10;
	const int TILE_WIDTH = 10;

	// timer for sprite state update 
	SDL_TimerID spriteUpdateTimer;
	static Uint32 spriteUpdate(Uint32, void *);

};