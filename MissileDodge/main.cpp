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
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "player.h"
#include "missile.h"

// function declarations
bool init(SDL_Window**, SDL_Surface**);
void close(SDL_Window*);
missile* spawnMissile(SDL_Surface*);

// screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
// vector containing the all sprites in the game
std::vector<sprite> sprites;
// vector containing the missiles in the game
std::vector<missile*> missiles;

int main(int argc, char* argv[]) {

	// intialize randomization seed
	srand(time(nullptr));

	// SDL window to refer to
	SDL_Window* window = nullptr;

	// the surface contained by the window
	SDL_Surface * screenSurface = nullptr;

	// initialize the SDL window and screen surface
	init(&window, &screenSurface);
	
	// add the sprites to the game and push them to the sprites list
	sprite background("assets/BG.png", screenSurface);
	sprites.push_back(background);
	sprite heart("assets/HEART.png", screenSurface);
	sprites.push_back(heart);

	// add a player character to the game
	player hero(200, 400, "assets/HERO.png", screenSurface);

	// main loop flag
	bool quit = false;		// true when user quits game
	SDL_Event e;			// SDL Event handler

	// missile spawn conter
	int spawnCounter = 50;

	// main game loop
	while (!quit) {

		// clear the screen at the beginning of each loop
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));

		// loop through the sprite vector and draw each one
		for (unsigned int i = 0; i < sprites.size(); i++) {
			// draw the sprite to the screen
			sprites[i].drawImage(screenSurface);
		}

		// spawn missiles
		if (spawnCounter == 0) {
			// add a new missile to the vector
			missiles.push_back(spawnMissile(screenSurface));
			// reset the spawn counter
			spawnCounter = 50;
		}
		// decrement the spawn counter
		spawnCounter--;

		// handle events on queue
		while (SDL_PollEvent(&e) != 0 ) {
			// if the user quits
			if (e.type == SDL_QUIT) {
				// set the quit flag to true
				quit = true;
			} else {
				// call the event handler for each sprite
				hero.eventHandler(e);
			}

		}
		
		// update the missiles and check for collisions between missiles and player
		for (unsigned int i = 0; i < missiles.size(); i++) {
			// call the missile update function
			missiles.at(i)->update(screenSurface);
			// if the hero is colliding with a missile
			if (SDL_HasIntersection(&(hero.getRect()), &(missiles.at(i)->getRect()))) {
				LOG("COLLISION");
			}
		}

		// update the hero
		hero.update(screenSurface);

		// update the screen
		SDL_UpdateWindowSurface(window);

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
		*window = SDL_CreateWindow("Missile Dodge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

// function that spawns a missile on the screen
missile* spawnMissile(SDL_Surface* screenSurface) {

	// variable to calculate offest for missile spawning
	int x_offset;

	// randomize the offset to a random number between the screen sizes
	x_offset = rand() % (SCREEN_WIDTH - 20) + 10;	// take margins into account

	// add a missile to the game
	missile * temp = new missile(x_offset, -20, "assets/MISSILE.png", screenSurface);

	// return the pointer
	return temp;

}