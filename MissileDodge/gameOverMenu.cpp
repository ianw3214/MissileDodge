#include "gameOverMenu.h"

/*	TODO:
	- show high score in end screen
	- show time player stayed alive for
*/

// constructor
gameOverMenu::gameOverMenu(SDL_Window* iWindow, SDL_Surface* iSurface) {

	// set the window and surface
	this->gWindow = iWindow;
	this->gSurface = iSurface;

	// call the inittalize function
	init();

	// fade in to menu
	fade(0);

	// loop as long as the player doesn't quit
	while (!quit) {

		// clear the screen at the beginning of each loop
		SDL_FillRect(gSurface, nullptr, SDL_MapRGB(gSurface->format, 0, 0, 0));

		// call the update function
		update();

		// update the screen
		SDL_UpdateWindowSurface(gWindow);

	}

	// fade out as long as the user isn't going to quit
	if (menuState != QUIT) {
		fade(1);
	}

}

// getter function
state gameOverMenu::getFlag() {
	return this->menuState;
}

// intitialize menu elements
void gameOverMenu::init() {

	// initialize sprites
	sprite * normal = new sprite(10, 20, "assets/TEXT/START.png");
	sprite * hover = new sprite(10, 20, "assets/TEXT/START_SELECTED.png");
	menuItem start = { *normal, *hover };
	menuItems.push_back(start);

	normal = new sprite(10, 70, "assets/TEXT/MENU.png");
	hover = new sprite(10, 70, "assets/TEXT/MENU_SELECTED.png");
	menuItem menu = {*normal, *hover};
	menuItems.push_back(menu);

	normal = new sprite(10, 120, "assets/TEXT/QUIT.png");
	hover = new sprite(10, 120, "assets/TEXT/QUIT_SELECTED.png");
	menuItem quit = { *normal, *hover };
	menuItems.push_back(quit);

	// initialize menu background
	menuBG = new sprite("assets/MENU_BG.png");

	// initialize menu variables
	this->selected = 0;
	this->menuState = GAME;
	this->quit = false;

}

// update function
void gameOverMenu::update() {

	// get the inputs from the user
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			menuState = QUIT;
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

	render();

	return;

}

// function called upon user pressing enter
void gameOverMenu::select() {

	/*	- set flag depending on current selected
	- exit the menu loop if play or quit
	*/

	// see what item is currently selected
	switch (selected) {
	case 0:
		// start game by quitting and setting play flag to true
		menuState = GAME;
		quit = true;
		break;
	case 1:
		// quit the game and return to the main menu
		menuState = MENU;
		quit = true;
		break;
	case 2:
		// quit the game and dont go into battle
		menuState = QUIT;
		quit = true;
		break;
	}
	LOG(selected);
	return;

}

// function that renders all menu elements
void gameOverMenu::render() {
	// render the background
	menuBG->render(gSurface);

	// update the sprites
	for (unsigned int i = 0; i < menuItems.size(); i++) {
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

// fade in / fade out functions that takes a parameter of 0 or 1 for in / out
void gameOverMenu::fade(int key) {

	// time variables to help fade in function stay within a time frame
	unsigned int bTick, cTick;
	unsigned int time = constants::BASE_FADE_TIME;

	// black image to cover the screen with
	SDL_Surface * temp;
	temp = IMG_Load("assets/BLACK.png");
	if (!temp) {	// if the image failed to load
					// output the error
		std::cout << "Failed to load image, SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	// update the alpha values depending on the difference in time elapsed
	bTick = SDL_GetTicks();
	cTick = bTick;
	while ((cTick - bTick) < time) {

		// render the base menu first
		render();

		// set the alpha depenidng on time elapsed
		// if key is 0, fade in; if key is 1, fade out
		if (key == 0) {
			SDL_SetSurfaceAlphaMod(temp, 255 - ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (key == 1) {
			SDL_SetSurfaceAlphaMod(temp, ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (SDL_BlitSurface(temp, nullptr, gSurface, nullptr) < 0) {
			// output the error
			std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		}

		SDL_UpdateWindowSurface(gWindow);

		// update the current tick value
		cTick = SDL_GetTicks();
	}

	return;

}