#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <typeinfo>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "player.h"
#include "missile.h"
#include "gameVars.h"

class game {

public:
	
	// constructor
	game(SDL_Window*, SDL_Surface*);
	// function to start the game
	void startGame();
	// game loop function
	void gameLoop(double);

private:

	// structure to store different text for menus
	struct menuItem {
		sprite normal;
		sprite hover;
	};

	// the screen and window to update the game onto
	SDL_Window * gWindow;
	SDL_Surface * gSurface;

	// vector that holds the countdown numbers
	std::vector<sprite> countDownNums;

	// vector to hold the items in the pause menu
	std::vector<menuItem> menuItems;
	void menuUpdate();			// update function for the pause menu
	void select();				// function that triggers when enter or space is hit on pause menu
	void menuRender();			// function that renders menu elements when paused
	int selected;				// integer to hold current menu selection

	// game variables
	int score;		// int to keep track of points
	bool pause, quit;		// flag to see if the game should be stopped or exited
	SDL_Event e;	// SDL event handler
	int missileSpawnCounter;	// integer to keep track of when to spawn missiles.
	Uint32 cTime, lTime;		// integers to keep track of time difference

	// game functions
	void init();			// initialization function
	void updateSprites(double);	// sprite logic update function
	void renderSprites();	// sprite render function
	void spawnMissile();	// missile spawning logic
	void handleCollision();	// collision detection function
	void countDown();		// function to transition into gameplay

	// game sprite storage
	std::vector<sprite*> sprites;
	player * hero;

};