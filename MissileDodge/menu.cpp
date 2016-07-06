#include "menu.h"

// constructor
menu::menu(SDL_Window* iWindow, SDL_Surface* iSurface) {

	// set the window and surface
	this->gWindow = iWindow;
	this->gSurface = iSurface;

	// call the inittalize function
	init();

	// fade in to the menu
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

	// fade out to next game state
	fade(1);

}

// getter function
state menu::getFlag() {
	return this->flag;
}

// intitialize menu elements
void menu::init() {

	// initialize sprites
	menuItems.push_back({ sprite(10, 20, "assets/TEXT/START.png"), sprite(10, 20, "assets/TEXT/START_SELECTED.png") });
	menuItems.push_back({ sprite(10, 70, "assets/TEXT/CONTROLS.png"), sprite(10,  70, "assets/TEXT/CONTROLS_SELECTED.png") });
	menuItems.push_back({ sprite(10, 120, "assets/TEXT/OPTIONS.png"), sprite(10, 120, "assets/TEXT/OPTIONS_SELECTED.png") });
	menuItems.push_back({ sprite(10, 170, "assets/TEXT/QUIT.png"), sprite(10, 170, "assets/TEXT/QUIT_SELECTED.png") });

	// initialize menu background
	menuBG = new sprite("assets/MENU_BG.png");
	// intiialize other menu elements
	controlSheet = new sprite(400, 50, "assets/TEXT/CONTROL_SHEET.png");

	// initialize menu variables
	this->selected = 0;
	this->flag = GAME;
	this->menuState = MAIN;
	this->quit = false;

}

// update function
void menu::update() {

	// get the inputs from the user
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			flag = QUIT;
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

	// call the render function to show the sprites
	render();

	return;

}

// function that renders elements from the menu to the screen
void menu::render() {

	// render the background
	menuBG->render(gSurface);

	// render the right side of the screen depending on the state of the menu
	switch (menuState) {

	case MAIN: {

	} break;
	case CONTROLS: {
		controlSheet->render(gSurface);
	} break;
	case OPTIONS: {

	} break;

	}

	// render the menu options
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
		flag = GAME;
		quit = true;
		break;
	case 1:
		// go to the control page of the menu
		menuState = CONTROLS;
		break;
	case 2:
		// go to the options page of the menu
		menuState = OPTIONS;
		break;
	case 3:
		// quit the game and dont go into battle
		flag = QUIT;
		quit = true;
		break;
	}

	return;

}

// fade in / fade out functions that takes a parameter of 0 or 1 for in / out
void menu::fade(int key) {

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
