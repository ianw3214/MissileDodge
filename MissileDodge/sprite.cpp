#include "sprite.h"

// constructor with path
sprite::sprite(std::string path, SDL_Surface* gSurface) {

	// initialize the x and y coordinates if they are not specified
	this->rect.x = 0;
	this->rect.y = 0;

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
	this->rect.x = inputX;
	this->rect.y = inputY;

	// load the image from the path for the sprite
	img = IMG_Load(path.c_str());
	if (!img) {	// if the image failed to load
				// output the error
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}
	
}

// getter/setter methods
int sprite::getX() { return this->rect.x; }
int sprite::getY() { return this->rect.y; }
SDL_Rect sprite::getRect() { return this->rect; }

// function to set the position of the image
bool sprite::drawImage(SDL_Surface* gSurface) {

	// success flag
	bool success = true;

	// if the function failed
	if (SDL_BlitSurface(img, nullptr, gSurface, &rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// return the success boolean
	return success;

}

