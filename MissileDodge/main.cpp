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
// base score constant
const int BASE_SCORE = 10;
// vector containing the all sprites in the game
std::vector<sprite> sprites;
// vector containing the missiles in the game
std::vector<missile*> missiles;

int main(int argc, char* argv[]) {

	// integer to keep track of points
	int score=0;

	// intialize randomization seed
	srand(time(nullptr));

	// SDL window to refer to
	SDL_Window* window = nullptr;

	// the surface contained by the window
	SDL_Surface * screenSurface = nullptr;

	// initialize the SDL window and screen surface
	init(&window, &screenSurface);
	
	// add the sprites to the game and push them to the sprites list
	sprite background("assets/BG.png");
	sprites.push_back(background);

	// add a player character to the game
	player hero(200, 400, "assets/HERO.png");

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
		for (unsigned int i = missiles.size(); i > 0; i--) {
			// call the missile update function
			missiles.at(i-1)->update(screenSurface);
			// if the hero is colliding with a missile
			if (SDL_HasIntersection(&(hero.getRect()), &(missiles.at(i-1)->getRect()))) {
				// remove the pointer from the vector
				missiles.erase(missiles.end() - i);
				// apply damage to the player
				if (hero.takeDamage(1)) {	// the player is alive
					LOG(hero.getHealth());
				}
				// the player is dead
				else {
					LOG("PLAYER DEAD!");
				}
				// break the current for loop so the missile doesn't get checked any further
				break;
			}
			// if the missile hits the ground
			if (missiles.at(i - 1)->getY() > 450) {
				// remove the missile pointer from the vector
				missiles.erase(missiles.end() - i);
				// add to the score
				score += BASE_SCORE;
				LOG(score);
				// break the current for loop so the missile doesn't get checked any further
				break;
			}
		}

		// update the hero
		hero.update(screenSurface);

		// update the hearts on screen
		for (int i = 0; i < hero.getHealth(); i++) {
			// add a heart to the screen
			sprite heart((20+i * 45), 20, "assets/HEART.png");
			// draw the heart to the screen
			heart.drawImage(screenSurface);
		}

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
	missile * temp = new missile(x_offset, -20, "assets/MISSILE.png");

	// return the pointer
	return temp;

}