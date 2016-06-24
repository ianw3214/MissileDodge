/*	Missile Dodge Game
	- made with SDL
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "player.h"
#include "missile.h"
#include "game.h"
#include "menu.h"
#include "gameVars.h"

// function declarations
bool init(SDL_Window**, SDL_Surface**);
void close(SDL_Window*);


// entry point
int main(int argc, char* argv[]) {

	// integer to hold the state of the game
	int gameState = 0;
	
	// intialize randomization seed
	srand(time(nullptr));

	// SDL window to refer to
	SDL_Window* window = nullptr;

	// the surface contained by the window
	SDL_Surface * screenSurface = nullptr;

	// initialize the SDL window and screen surface
	init(&window, &screenSurface);

	// make a menu
	menu * mainMenu = new menu(window, screenSurface);

	// start a game if the user wants to play
	if (mainMenu->getFlag() == GAME) {

		// start a new game
		game * battle = new game(window, screenSurface);
		battle->startGame();

		// see what the player wants to do 
		while (battle->getFlag() != QUIT) {
			switch (battle->getFlag()) {
			case GAME:
				// start a new game if the flag is 0
				battle = new game(window, screenSurface);
				battle->startGame();
				break;
			}
		}

	}


	// call the SDL exit function
	close(window);

	return 0;

}


// handles initialization of SDL window and surface
bool init(SDL_Window** window, SDL_Surface** surface) {

	// Initialization flag
	bool success = false;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {	// if SDL failed to initialize
		// print the error to the console
		std::cout << "SDL could not initialize, SDL ERROR: " << SDL_GetError() << std::endl;
		success = false;				// set the initialization flag to false
	}
	else {								// SDL initialization was successful
		// create window
		*window = SDL_CreateWindow("Missile Dodge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == nullptr) {			// failed to create window
			// print the error to the console
			std::cout << "Window was not created!, SDL ERROR: " << SDL_GetError() << std::endl;
			success = false;			// set the initialization flag to false
		}
		else {							// window successfully created
			// initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags)) {
				// output the error
				std::cout << "SDL_Image could not initialize, SDL_image ERROR : " << IMG_GetError() << std::endl;
				// set the initialization flag to false
				success = false;
			}
			else {						// SDL_Image successfully loaded
				// get the window surface
				*surface = SDL_GetWindowSurface(*window);
			}
		}
	}

	// return the initialization flag
	return success;

}

// exit function to quit SDL
void close(SDL_Window* window) {

	// Destroy the window
	SDL_DestroyWindow(window);
	window = nullptr;

	// Quit SDL subsystems
	SDL_Quit();

}