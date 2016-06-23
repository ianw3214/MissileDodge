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