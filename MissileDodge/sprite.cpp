#include "sprite.h"

// constructor with path
sprite::sprite(std::string path, SDL_Surface* gSurface) {

	// initialize the x and y coordinates if they are not specified
	this->x = 0;
	this->y = 0;

	// load the image from the path for the sprite
	img = IMG_Load(path.c_str());
	if (!img) {	// if the image failed to load
				// output the error
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

}

// constructor with path and positions
sprite::sprite(int inputX, int inputY, std::string path, SDL_Surface* gSurface) {

	// set the x and y of this sprite to the specified input
	this->x = inputX;
	this->y = inputY;

	// load the image from the path for the sprite
	img = IMG_Load(path.c_str());
	if (!img) {	// if the image failed to load
				// output the error
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

}

// getter/setter methods
int sprite::getX() { return this->x; }
int sprite::getY() { return this->y; }

// function to set the position of the image
bool sprite::drawImage(SDL_Surface* gSurface) {

	// success flag
	bool success = true;

	// rect struct to put coordinates in and pass to blit function
	SDL_Rect Rect = { this->x, this->y, 0, 0 };

	// if the function failed
	if (SDL_BlitSurface(img, NULL, gSurface, &Rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// return the success boolean
	return success;

}

