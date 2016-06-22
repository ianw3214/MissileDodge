#include "boon.h"

// initialize the values for the health pack
void boon::init(int x, int y) {
	
	this->rect = {x, y, boonConstants::WIDTH, boonConstants::HEIGHT};
	type = BOON;
	boonType = HEALTH;

	return;

}