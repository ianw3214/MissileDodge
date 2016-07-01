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
void missile::init(int x, int y, float speedModifier, missileTypes mT) {
	
	// intialize sprite type
	type = MISSILE;

	// initialize missile type
	missileType = mT;

	// change missile graphics depending on missile type
	switch (missileType) {
	case GAS: {
		// initialize image, rect, and speed with random modifier with gas missile stats
		img = IMG_Load("assets/GASMISSILE.png");
		this->rect = { x, y, missileConstants::gasMissile::WIDTH, missileConstants::gasMissile::HEIGHT };
		this->speed = static_cast<int>(missileConstants::gasMissile::BASE_SPEED * speedModifier + std::rand() % 300);
	} break;
	case NORMAL: // have normal and default be the same so if an unknown input is entered it just outputs a normal missile
	default: {
		// initialize image, rect, and speed with random modifier
		img = IMG_Load("assets/MISSILE.png");
		this->rect = { x, y, missileConstants::WIDTH, missileConstants::HEIGHT };
		this->speed = static_cast<int>(missileConstants::BASE_SPEED * speedModifier + std::rand() % 300);
	} break;
	}
	// output if the image failes to load
	if (!img) {	
		std::cout << "Failed to load image, SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	return;

}