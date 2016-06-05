#include "menu.h"

// constructor
menu::menu(SDL_Window* iWindow, SDL_Surface* iSurface) {

	// set the window and surface
	this->gWindow = iWindow;
	this->gSurface = iSurface;

	// call the inittalize function
	init();

	// loop as long as the player doesn't quit
	while (!quit) {

		// clear the screen at the beginning of each loop
		SDL_FillRect(gSurface, nullptr, SDL_MapRGB(gSurface->format, 0, 0, 0));
		
		// call the update function
		update();

		// update the screen
		SDL_UpdateWindowSurface(gWindow);

	}

}

// getter function
bool menu::getFlag() {
	return this->play;
}

// intitialize menu elements
void menu::init() {

	// initialize sprites
	sprite * normal = new sprite(300, 200, "assets/MENU/START.png");
	sprite * hover = new sprite(300, 200, "assets/MENU/START_SELECTED.png");
	menuItem start = { *normal, *hover};
	menuItems.push_back(start);

	normal = new sprite(300, 350, "assets/MENU/QUIT.png");
	hover = new sprite(300, 350, "assets/MENU/QUIT_SELECTED.png");
	menuItem quit = { *normal, *hover};
	menuItems.push_back(quit);

	// initialize menu variables
	this->selected = 0;
	this->quit = false;
	this->play = false;

}

// update function
void menu::update() {

	// get the inputs from the user
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			this->quit = true;
		}
		// if the user presses a key
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				// if the user pressese a down button
			case SDLK_s:
			case SDLK_DOWN:
				// if the current selected item is less than the total amount of items
				if (selected < (menuItems.size() - 1)) {
					// add one to selected
					selected++;
				}
				break;
				// if the user presses an up button
			case SDLK_w:
			case SDLK_UP:
				// if the current selected item is higher than 0
				if (selected > 0) {
					// minus one to selected
					selected--;
				}
				break;
			case SDLK_RETURN:
			case SDLK_SPACE:
				select();
				break;
			}
		}
		
	}

	// update the sprites
	for (int i = 0; i < menuItems.size(); i++) {
		// if the current loop is the selected item
		if (selected == i) {
			// render the selected sprite
			menuItems.at(i).hover.render(gSurface);
		}
		// if it is not the selected one
		else {
			// render the normal sprite
			menuItems.at(i).normal.render(gSurface);
		}
	}

	return;

}

// function called upon user pressing enter
void menu::select() {

	/*	- set flag depending on current selected
		- exit the menu loop if play or quit
	*/

	// see what item is currently selected
	switch (selected) {
	case 0:
		// start game by quitting and setting play flag to true
		this->play = true;
		quit = true;
		break;
	case 1:
		// quit the game and dont go into battle
		this->play = false;
		quit = true;
		break;
	}

	return;

}