/*	Missile Dodge Game
	- made with SDL
*/

#define DEBUG 0

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

// function declarations
bool init(SDL_Window**, SDL_Surface**);
bool addImage(SDL_Surface*, int, int, SDL_Surface*);
SDL_Surface * loadImage(std::string, SDL_Surface**);

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

	// load the images
	SDL_Surface* background = loadImage("assets/BG.png", &screenSurface);
	SDL_Surface* hero = loadImage("assets/HERO.png", &screenSurface);
	SDL_Surface* missile = loadImage("assets/MISSILE.png", &screenSurface);
	SDL_Surface* heart = loadImage("assets/HEART.png", &screenSurface);

	// add the images to the screen
	addImage(background, 0, 0, screenSurface);
	addImage(hero, 200, 400, screenSurface);
	addImage(missile, 400, 40, screenSurface);
	addImage(heart, 0, 0, screenSurface);

	// update the screen
	SDL_UpdateWindowSurface(window);

	system("PAUSE");

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

// function to add loaded image to screen
bool addImage(SDL_Surface* image, int xInit, int yInit, SDL_Surface* gSurface) {
	
	// success flag
	bool success = true;

	// rect struct to put coordinates in and pass to blit function
	SDL_Rect Rect = { xInit, yInit, 0, 0 };

	// if the function failed
	if (SDL_BlitSurface(image, NULL, gSurface, &Rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// return the success boolean
	return success;

}

// function to load image
SDL_Surface * loadImage(std::string path, SDL_Surface** gSurface) {

	// call the image load function
	SDL_Surface *image = IMG_Load(path.c_str());
	if (!image) {	// if the image failed to load
		// output the error
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	return image;
}