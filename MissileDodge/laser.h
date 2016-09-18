#pragma once

#include "sprite.h"
#include "gameVars.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class laser : public sprite {

public:
	// inherit constructors
	laser(std::string s, bool* b) : sprite(s) {
		// initialize player
		init(0, 0, b);
	};
	laser(int x, int y, std::string s, bool* b) : sprite(x, y, s) {
		// initialize player
		init(x, y, b);
	};
	
	// getter/setter functions
	bool isFiring();
	bool isFinished();
	bool getDamagedPlayer();
	void setDamagedPlayerTrue();
	// override render function from sprite class
	bool render(SDL_Surface*);

private:

	// init function
	void init(int, int, bool*);

	// class variables
	bool firing;		// boolean that tells the game if the laser is firing or not
	bool finished;		// boolean that tells the game if the sprite is done playing
	bool damagedPlayer;
	bool * isPaused;

	// sprite sheet variables
	SDL_Rect SS_rect;	// keeps track of which part of the sprite sheet to copy
	int spriteFrame;	// keeps track of the current animation frame
	int pauseFrames;	// keeps track of how many frames the sprite has paused for
	SDL_TimerID spriteUpdateTimer;

	// timer for sprite state update 
	static Uint32 spriteUpdate(Uint32, void *);

};