#include "laser.h"

// getter/setter functions
bool laser::isFiring() { return firing; }
bool laser::isFinished() { return finished; }
bool laser::getDamagedPlayer() { return damagedPlayer; }
void laser::setDamagedPlayerTrue() { damagedPlayer = true; }

// initialize the laser object
void laser::init(int x, int y, bool * paused) {

	// initialize class variables
	this->firing = false;
	this->spriteFrame = 0;
	this->pauseFrames = 0;
	this->damagedPlayer = false;
	this->finished = false;
	this->isPaused = paused;

	// initialize player rect
	this->rect = {x, y, laserConstants::WIDTH, laserConstants::HEIGHT};

	// initialize copy rect dimensions
	SS_rect.w = laserConstants::WIDTH;
	SS_rect.h = laserConstants::HEIGHT;

	// initialize sprite type
	this->type = LASER;

	// start sprite update timer
	spriteUpdateTimer = SDL_AddTimer(70, spriteUpdate, this);

	return;

}

// override the render function from sprite class
bool laser::render(SDL_Surface * gSurface) {

	// success flag
	bool success = true;

	// if the function failed
	if (SDL_BlitSurface(img, &SS_rect, gSurface, &rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// return the success boolean
	return success;

}

Uint32 laser::spriteUpdate(Uint32 interval, void * ptr) {

	// get a reference to the player
	laser * temp = (laser*)ptr;

	// only update the sprite if the game isn't paused
	if (!*(temp->isPaused)) {

		// pause at the pause frames
		if (temp->spriteFrame == laserConstants::PAUSE_FRAME_1 - 1 || temp->spriteFrame == laserConstants::PAUSE_FRAME_2 - 1
			|| temp->spriteFrame == laserConstants::PAUSE_FRAME_3 - 1) {
			temp->pauseFrames++;
			// keep on playing the animation if the frame has been paused 10 times
			if (temp->pauseFrames > 20) {
				temp->spriteFrame++;
			}
			// skip the rest of the code if the sprite should be paused
			return interval;
		}

		// change firing to true if the frame has been reached
		if (temp->spriteFrame > laserConstants::PAUSE_FRAME_2) {
			temp->firing = true;
		}

		// keep playing the animations
		temp->spriteFrame++;

		// exit the timer if the animation finished playing
		if (temp->spriteFrame >= laserConstants::MAX_FRAMES) {
			temp->finished = true;
			return 0;
		}

		// update the copy rect object
		temp->SS_rect.y = laserConstants::HEIGHT * temp->spriteFrame;
	}
	
	// update again at the same interval
	return interval;
}
