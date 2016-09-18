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
	missile(std::string s, float t, bool* p, missileTypes mT = NORMAL) : sprite(s) {
		// intialize missile with a missile type
		init(0, 0, t, p, mT);
	};
	missile(int x, int y, std::string s, float t, bool* p, missileTypes mT = NORMAL) : sprite(x, y, s) {
		// intialize missile with a missile type
		init(x, y, t, p, mT);
	};
	// getter function
	int getSpeed();
	missileTypes getMissileType();
	// class functions
	void update(SDL_Surface*, double);
	// override render function from sprite class
	bool render(SDL_Surface*);

private:

	int speed;
	void init(int, int, float, bool*, missileTypes mT);
	missileTypes missileType;

	// sprite sheet variables
	SDL_Rect SS_rect;	// keeps track of which part of the sprite sheet to copy
	int spriteFrame;	// keeps track of the current animation state of the sprite
	SDL_TimerID spriteUpdateTimer;
	bool * gamePaused;

	// timer for sprite state update 
	static Uint32 spriteUpdate(Uint32, void *);

};