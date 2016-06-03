#pragma once

// enumeration to store sprite type
enum types {
	SPRITE,
	MISSILE,
	PLAYER,
	HEART
};
// namespace that contains all the constants that the game needs
namespace constants {

	// game constants
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	constexpr int GRAVITY = 900;
	constexpr int GROUND_LEVEL = 400;

	// base score unit
	constexpr int BASE_SCORE = 10;
	// number to put in counter for missile spawning
	constexpr int BASE_SPAWN_TIME = 50;

}
// namespace for player constants
namespace playerConstants {
	// size of player
	constexpr int WIDTH = 40;
	constexpr int HEIGHT = 80;
	constexpr int BASE_SPEED = 500;
	constexpr int BASE_HEALTH = 3;
	// constants for jumping
	constexpr int BASE_JUMP_VELOCITY = 600;
	constexpr int BASE_JUMP_TIME = 30;
}
// namespace for missile constants
namespace missileConstants {
	// size of missile
	constexpr int WIDTH = 40;
	constexpr int HEIGHT = 80;
	constexpr int BASE_SPEED = 500;
}
