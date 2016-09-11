#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <typeinfo>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>

#include "sprite.h"
#include "player.h"
#include "missile.h"
#include "boon.h"
#include "gameOverMenu.h"
#include "gameVars.h"

class game {

public:
	
	// constructor
	game(SDL_Window*, SDL_Surface*);
	// function to start the game
	void startGame();
	// game loop function
	void gameLoop(double);
	// function to get the resultant flag of the game
	state getFlag();

private:

	// structure to store different text for menus
	struct menuItem {
		sprite normal;
		sprite hover;
	};

	// the screen and window to update the game onto
	SDL_Window * gWindow;
	SDL_Surface * gSurface;

	// vector that holds the number sprites
	std::vector<sprite> numSprites;

	// vector to hold the items in the pause menu
	std::vector<menuItem> menuItems;
	void menuUpdate();			// update function for the pause menu
	void select();				// function that triggers when enter or space is hit on pause menu
	void menuRender();			// function that renders menu elements when paused
	unsigned int selected;		// integer to hold current menu selection

	// game variables
	bool gameOver;
	int difficultyScale;
	float spawnModifier;
	float speedModifier;
	int score;		
	bool pause, quit;			// flag to see if the game should be stopped or exited
	SDL_Event e;				// SDL event handler
	Uint32 cTime, lTime;		// integers to keep track of time difference

	// game functions
	void init();			// initialization function
	void updateSprites(double);	// sprite logic update function
	void renderSprites();	// sprite render function
	void handleCollision();	// collision detection function
	void countDown();		// function to transition into gameplay

	// game sprite storage
	std::vector<sprite*> sprites;
	player * hero;

	// variable to store the flag to return to determine the state of game
	state flag;

	// timer functions
	static Uint32 boonTimer(Uint32, void *);
	static Uint32 difficultyTimer(Uint32, void *);
	static Uint32 missileSpawner(Uint32, void *);

	// fade in / fade out functions
	void fade(int);

	// music variables
	Mix_Chunk *wave;

};