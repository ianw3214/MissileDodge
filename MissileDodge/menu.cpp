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

	// fade out as long as the user didnt quit
	if (flag != QUIT) {
		fade(1);
	}

	// clean up music resources
	Mix_FreeChunk(wave);

}

// getter function
state menu::getFlag() {
	return this->flag;
}

// intitialize menu elements
void menu::init() {

	// initialize sprites
	menuItems.push_back({ sprite(10, 400, "assets/TEXT/START.png"), sprite(10, 400, "assets/TEXT/START_SELECTED.png") });
	menuItems.push_back({ sprite(10, 450, "assets/TEXT/CONTROLS.png"), sprite(10,  450, "assets/TEXT/CONTROLS_SELECTED.png") });
	menuItems.push_back({ sprite(10, 500, "assets/TEXT/OPTIONS.png"), sprite(10, 500, "assets/TEXT/OPTIONS_SELECTED.png") });
	menuItems.push_back({ sprite(10, 550, "assets/TEXT/QUIT.png"), sprite(10, 550, "assets/TEXT/QUIT_SELECTED.png") });

	// initialize menu background
	menuBG = new sprite("assets/MENU_BG.png");
	// intiialize other menu elements
	title = new sprite(270, 20, "assets/TITLE.png");
	border = new sprite(0, 0, "assets/BORDER.png");
	controlSheet = new sprite(0, 0, "assets/TEXT/CONTROL_SHEET.png");
	returnText = new sprite(450, 585, "assets/TEXT/ESCAPE.png");

	// initialize menu variables
	this->selected = 0;
	this->flag = GAME;
	this->menuState = MAIN;
	this->quit = false;
	this->showText = true;

	// initialize random seed
	srand(time(nullptr));

	// start star creating timer
	stars = {};
	SDL_TimerID missileSpawnTimer = SDL_AddTimer(1000, createStar, this);
	SDL_TimerID textShowTimer = SDL_AddTimer(600, textTimer, this);

	// audio intialization
	wave = Mix_LoadWAV(music_menu);
	if (wave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
	if (Mix_PlayChannel(-1, wave, -1) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}

	return;

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
			case SDLK_ESCAPE:
				// if the user presses escape, go to default menu state
				menuState = MAIN;
				selected = 0;
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

	// render the text border
	border->render(gSurface);

	// render the stars
	for (int i = stars.size() - 1; i >= 0; i--) {
		if ( stars.at(i)->isDoneAnimation ) {
			stars.erase( stars.begin() + i );
		}
		else {
			stars.at(i)->render(gSurface);
		}
	}

	// render the right side of the screen depending on the state of the menu
	switch (menuState) {

	case MAIN: {

	} break;
	case CONTROLS: {
		// render the controls sprite if the user is in the controls option
		controlSheet->render(gSurface);
		if (showText) { returnText->render(gSurface); }
	} break;
	case OPTIONS: {
		if (showText) { returnText->render(gSurface); }
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

	// render the title
	title->render(gSurface);

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

// function that creates background stars
Uint32 menu::createStar(Uint32 time, void * ptr) {

	menu * temp = (menu*)ptr;

	star * tempStar = new star("assets/star_sheet.png");
	// add the new star to the stars vector
	temp->stars.push_back(tempStar);

	return time;

}

// function that flashes text on a timer
Uint32 menu::textTimer(Uint32 time, void * ptr) {

	menu * temp = (menu*)ptr;

	// change the state of show text boolean
	if (temp->showText) {
		temp->showText = false;
	}
	else {
		temp->showText = true;
	}

	return time;

}
