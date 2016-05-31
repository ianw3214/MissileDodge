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

// constants
constexpr int BASE_SCORE = 10;
constexpr int BASE_SPAWN_TIME = 50;


class game {

public:

	// constructor
	game(SDL_Window*, SDL_Surface*, int, int);
	// function to start the game
	void startGame();

private:

	// the screen and window to update the game onto
	SDL_Window * gWindow;
	SDL_Surface * gSurface;

	// game variables
	int score;		// int to keep track of points
	bool quit;		// flag to see if user wants to quit
	SDL_Event e;	// SDL event handler
	int missileSpawnCounter;	// integer to keep track of when to spawn missiles.
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	// game functions
	void init(int, int);
	void updateSprites();
	void spawnMissile();
	void handleCollision();
	void updateHearts();

	// game sprite storage
	std::vector<sprite*> sprites;
	player * hero;

};