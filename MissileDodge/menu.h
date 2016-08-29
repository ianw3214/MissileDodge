#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>

#include "sprite.h"
#include "gameVars.h"
#include "star.h"

class menu {

public:
	// constructor
	menu(SDL_Window*, SDL_Surface*);
	// getter function
	state getFlag();

protected:

	enum menuStates {
		MAIN,
		OPTIONS,
		CONTROLS
	};

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
	// menu background sprite
	sprite * menuBG;
	// other sprite elements for menu
	sprite * title;				// sprite to hold the title for the menu
	sprite * controlSheet;		// sprite to show controls when controls option is selected
	sprite * returnText;

	// initialize function
	void init();
	// update function
	void update();
	// function that renders the menu elements onto the screen
	void render();
	// function that determines logic upon select key press
	void select();

	// menu variables
	unsigned int selected;
	SDL_Event e;

	// used to determine what the player wants to do next
	state flag;
	// flag to determine the current state of the menu
	menuStates menuState;
	// boolean to determine when to quit the menu
	bool quit;

	// fade in / fade out functions
	void fade(int);

	// variables for creating background stars
	std::vector<star*> stars;
	static Uint32 createStar(Uint32, void *);

};