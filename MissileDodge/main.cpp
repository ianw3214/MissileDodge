/*	Missile Dodge Game
	- made with SDL
*/

#define DEBUG 1

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "sprite.h"

// function declarations
bool init(SDL_Window**, SDL_Surface**);

// screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

	// SDL window to refer to
	SDL_Window* window = NULL;

	// the surface contained by the window
	SDL_Surface * screenSurface = NULL;

	// initialize the SDL window and screen surface
	init(&window, &screenSurface);
	
	sprite background("assets/BG.png", screenSurface);
	sprite hero(200, 400, "assets/HERO.png", screenSurface);
	sprite missile(400, 40, "assets/MISSILE.png", screenSurface);
	sprite heart("assets/HEART.png", screenSurface);

	// main loop flag
	bool quit = false;		// true when user quits game
	SDL_Event e;			// SDL Event handler

	// TODO	
	// create an velocity tracker for the hero movement
	// set a speed constant for hero movement
	// set booleans to see if left/right keys are held down

	// main game loop
	while (!quit) {
		// handle events on queue
		while (SDL_PollEvent(&e) != 0 ) {
			// if the user quits
			if (e.type == SDL_QUIT) {
				// set the quit flag to true
				quit = true;
			}
			// if the user presses a key
			else if (e.type == SDL_KEYDOWN) {
				// cases for each key press
				switch (e.key.keysym.sym) {
				case SDLK_a:		// A key
				case SDLK_LEFT:		// left key
					LOG("LEFT DOWN")
					// set the left down boolean to true
					break;
				case SDLK_d:		// D key
				case SDLK_RIGHT:	// right key
					LOG("RIGHT DOWN")
					// set the right down boolean to true
					break;
				}
			}
			// if the user releases a key
			else if (e.type == SDL_KEYUP) {
				// cases for each key press
				switch (e.key.keysym.sym) {
				case SDLK_a:		// A key
				case SDLK_LEFT:		// left key
					LOG("LEFT UP")
					// set the left down boolean to false
					break;
				case SDLK_d:		// D key
				case SDLK_RIGHT:	// right key
					LOG("RIGHT UP")
					// set the right down boolean to false
					break;
				}
			}

			// update the hero velocity based on the key press booleans
			// if both keys are pressed then there is no movement

			// update the screen
			SDL_UpdateWindowSurface(window);
		}
	}

	// Destroy the window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

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
		*window = SDL_CreateWindow("Missile Dodge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL) {			// failed to create window
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