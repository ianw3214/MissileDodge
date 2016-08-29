#include "star.h"

// constructor
star::star(std::string s) : sprite( s ) {
	// set the random number seed
	srand(time(nullptr));
	
	// call the initialize function
	init();
}

// initialization function
void star::init() {
	
	// intialize sprite rect
	this->rect = {rand()%constants::SCREEN_WIDTH, rand() % constants::SCREEN_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	std::cout << rand()%5 << std::endl;
	// initialize animation rect
	ss_star.w = TILE_WIDTH;
	ss_star.h = TILE_HEIGHT;

	// intialize keyframe number
	animState = 0;
	isDoneAnimation = false;

	// start sprite update timer
	spriteUpdateTimer = SDL_AddTimer(50, spriteUpdate, this);

}

bool star::render(SDL_Surface * gSurface) {

	// boolean that holds the state of success of function
	bool success = true;

	if (SDL_BlitSurface(img, &ss_star, gSurface, &rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// return the success state of function
	return success;

}

Uint32 star::spriteUpdate(Uint32 interval, void * ptr) {
	// get a reference to the player
	star * temp = (star*)ptr;

	// update the frame of the animation
	temp->ss_star.x = temp->animState * temp->TILE_WIDTH;

	// add 1 to animation frame
	temp->animState++;

	// change flag if animation is done
	if (temp->animState > 6) {
		temp->isDoneAnimation = true;
		return 0;
	}

	// update again at the same interval
	return interval;
}