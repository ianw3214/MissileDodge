#pragma once

#define DEBUG 1

#include <vector>
#include "sprite.h"

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif

// enumeration for game state
enum state {
	MENU,
	GAME,
	QUIT
};
// enumeration to store sprite type
enum types {
	SPRITE,
	MISSILE,
	PLAYER,
	HEART,
	BOON
};
// enumeration to seperate the types of boons
enum boonTypes {
	HEALTH,
	INVINCIBLE,
	SPEED
};
// namespace that contains all the constants that the game needs
namespace constants {

	// game constants
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	constexpr int GRAVITY = 1200;
	constexpr int GROUND_LEVEL = 450;

	constexpr int FONT_HEIGHT = 60;
	constexpr int FONT_WIDTH = 40;

	// base score unit
	constexpr int BASE_SCORE = 10;
	// number to put in counter for spawning objects
	constexpr int BASE_SPAWN_TIME = 50;
	// number to put in counter for difficulty scaling
	constexpr int BASE_DIFFICULTY_TIME = 2000;

}
// namespace for player constants
namespace playerConstants {
	// size of player
	constexpr int WIDTH = 60;
	constexpr int HEIGHT = 80;
	constexpr int BASE_SPEED = 500;
	constexpr int BASE_HEALTH = 3;
	// constants for jumping
	constexpr int BASE_JUMP_VELOCITY = 600;
	constexpr int BASE_JUMP_COOLDOWN = 60;
}
// namespace for missile constants
namespace missileConstants {
	// size of missile
	constexpr int WIDTH = 24;
	constexpr int HEIGHT = 80;
	// speed of missile that calculations are based off of
	constexpr int BASE_SPEED = 500;
}
// namespace for boon constants
namespace boonConstants {
	// size of boon sprite
	constexpr int WIDTH = 40;
	constexpr int HEIGHT = 40;

	// boon duration in milliseconds
	constexpr Uint32 DURATION = 3000;

	// other constants
	constexpr int BOON_SPEED = 200;
	constexpr int BASE_HEAL = 2;
	constexpr float BASE_SPEED_MULTIPLIER = 1.8f;
}