#include "boon.h"

// initialize the values for the health pack
void boon::init(int x, int y, boonTypes b) {
	
	this->rect = {x, y, boonConstants::WIDTH, boonConstants::HEIGHT};
	type = BOON;
	boonType = b;

	return;

}
// getter function for boon type
boonTypes boon::getBoonType() { return this->boonType; }

// update function to move the boon every frame
void boon::update(double delta) {

	// move the boon down 
	setPos(rect.x, static_cast<int>(rect.y + boonConstants::BOON_SPEED*delta));

	return;

}