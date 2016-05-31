#include "sprite.h"

// constructor with path
sprite::sprite(std::string path) {

	// intialize sprite at 0,0
	init(0, 0, path);

}

// constructor with path and positions
sprite::sprite(int inputX, int inputY, std::string path) {

	// initialize sprite at input poisition
	init(inputX, inputY, path);
	
}

// virtual destructor to make class polymorphic
sprite::~sprite(){ }

// getter/setter methods
int sprite::getX() { return this->rect.x; }
int sprite::getY() { return this->rect.y; }
types sprite::getType() { return this->type; }
SDL_Rect sprite::getRect() { return this->rect; }


// function that is called each frame by the game
void sprite::update(SDL_Surface* gSurface) {

	// default to drawing the sprite
	drawImage(gSurface);

	return;

}

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

// function to initialize loading a sprite
void sprite::init(int x, int y, std::string path) {

	// initialize the x and y coordinates if they are not specified
	this->rect.x = x;
	this->rect.y = y;

	// load the image from the path for the sprite
	img = IMG_Load(path.c_str());
	if (!img) {	// if the image failed to load
				// output the error
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	// initialize sprite type
	type = SPRITE;

	return;

}