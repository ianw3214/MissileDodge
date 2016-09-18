#include "missile.h"

// getter function
int missile::getSpeed() { return this->speed; }
missileTypes missile::getMissileType() { return this->missileType; }

// function that updates the missile every frame
void missile::update(SDL_Surface* gSurface, double delta) {
	
	// move the missile down and apply the modifier
	this->rect.y += static_cast<int>(speed * delta);

	return;

}

// function to initialize values for the missile
void missile::init(int x, int y, float speedModifier, bool * paused, missileTypes mT) {
	
	// intialize sprite type
	type = MISSILE;

	// initialize missile type
	missileType = mT;

	// initialize missile variables
	this->spriteFrame = 0;
	// have a pointer to the game pause variable to know if the sprite sheet should update
	this->gamePaused = paused;

	// change missile graphics depending on missile type
	switch (missileType) {
	case GAS: {
		// initialize image, rect, and speed with random modifier with gas missile stats
		img = IMG_Load("assets/GASMISSILE.png");
		this->rect = { x, y, missileConstants::gasMissile::WIDTH, missileConstants::gasMissile::HEIGHT };
		this->speed = static_cast<int>(missileConstants::gasMissile::BASE_SPEED * speedModifier + std::rand() % 300);
		SS_rect.w = missileConstants::gasMissile::WIDTH;
		SS_rect.h = missileConstants::gasMissile::HEIGHT;
	} break;
	case NORMAL: // have normal and default be the same so if an unknown input is entered it just outputs a normal missile
	default: {
		// initialize image, rect, and speed with random modifier
		img = IMG_Load("assets/MISSILE_SS.png");
		this->rect = { x, y, missileConstants::WIDTH, missileConstants::HEIGHT };
		this->speed = static_cast<int>(missileConstants::BASE_SPEED * speedModifier + std::rand() % 300);
		SS_rect.w = missileConstants::WIDTH;
		SS_rect.h = missileConstants::HEIGHT;
	} break;
	}

	// output if the image failes to load
	if (!img) {	
		std::cout << "Failed to load image, SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	// start sprite update timer
	spriteUpdateTimer = SDL_AddTimer(300, spriteUpdate, this);

	return;

}

// override the render function from sprite class
bool missile::render(SDL_Surface * gSurface) {

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

Uint32 missile::spriteUpdate(Uint32 interval, void * ptr) {
	// get a reference to the player
	missile * temp = (missile*)ptr;

	// only update the sprite if the game is paused
	if (!*(temp->gamePaused)) {

		// increase one to the sprite frame
		temp->spriteFrame++;

		// set the animation frame depending on the state of the hero
		switch (temp->missileType) {
		case NORMAL: {
			// reset the sprite loop if it is at the end of the sprite sheet
			if (temp->spriteFrame >= missileConstants::MAX_FRAMES) {
				temp->spriteFrame = 0;
			}
			temp->SS_rect.x = missileConstants::WIDTH * temp->spriteFrame;
			temp->SS_rect.y = 0;
		} break;
		case GAS: {
			// reset the sprite loop if it is at the end of the sprite sheet
			if (temp->spriteFrame >= missileConstants::gasMissile::MAX_FRAMES) {
				temp->spriteFrame = 0;
			}
			temp->SS_rect.x = 0;
			temp->SS_rect.y = 0;
		} break;
		}

	}
	
	// update again at the same interval
	return interval;
}