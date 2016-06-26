#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "gameVars.h"

class menu {

public:
	// constructor
	menu(SDL_Window*, SDL_Surface*);
	// getter function
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

	// vector to hold the items in the menu
	std::vector<menuItem> menuItems;

	// initialize function
	void init();
	// update function
	void update();
	// function that determines logic upon select key press
	void select();

	// menu variables
	unsigned int selected;
	SDL_Event e;

	// used to determine what the player wants to do next
	state menuState;
	// boolean to determine when to quit the menu
	bool quit;

};