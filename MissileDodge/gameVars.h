#pragma once

#define DEBUG 0

#include <vector>
#include "sprite.h"

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif

// define the path to all music files
#define music_menu "assets/MUSIC/MENU.wav"
#define music_game "assets/MUSIC/GAME.wav"

#define sfx_menu_change "assets/MUSIC/MENU_CHANGE.wav"

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
	BOON,
	LASER
};
// enumeration to seperate the types of boons
enum boonTypes {
	HEALTH,
	INVINCIBLE,
	SPEED
};
// enumeration to keep track of types of missiles
enum missileTypes {
	NORMAL,
	// gas poisons the player to move slower
	GAS
};

// namespace that contains all the constants that the game needs
namespace constants {

	// game constants
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	constexpr int GRAVITY = 1200;
	constexpr int GROUND_LEVEL = 500;

	constexpr int FONT_HEIGHT = 60;
	constexpr int FONT_WIDTH = 40;

	// base score unit
	constexpr int BASE_SCORE = 10;
	// number to put in counter for spawning objects
	constexpr int BASE_SPAWN_TIME = 900;
	// number to put in counter for difficulty scaling
	constexpr int BASE_DIFFICULTY_TIME = 5000;
	 
	// time in milliseconds for fading transitions
	constexpr unsigned int BASE_FADE_TIME = 500;

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
	constexpr int BASE_JUMP_COOLDOWN = 700;
}
// namespace for missile constants
namespace missileConstants {
	// size of missile
	constexpr int WIDTH = 24;
	constexpr int HEIGHT = 80;
	// speed of missile that calculations are based off of
	constexpr int BASE_SPEED = 350;
	// the amount of sprites in the missile spritesheet
	constexpr int MAX_FRAMES = 4;

	// seperate namespace for different missile type
	namespace gasMissile {
		constexpr int WIDTH = 30;
		constexpr int HEIGHT = 60;
		constexpr int BASE_SPEED = 300;
		constexpr float SPEED_MULTIPLIER = 0.4f;
		constexpr int DURATION = 3000;
		constexpr int MAX_FRAMES = 1;
	}
}
// namespace for boon constants
namespace boonConstants {
	// size of boon sprite
	constexpr int WIDTH = 40;
	constexpr int HEIGHT = 40;

	// boon duration in milliseconds
	constexpr Uint32 DURATION = 5000;

	// other constants
	constexpr int BOON_SPEED = 200;
	constexpr int BASE_HEAL = 2;
	constexpr int SPEED_BOOST = 900;
}
// namespace for laser constants
namespace laserConstants {
	// size of laser tiles
	constexpr int WIDTH = 800;
	constexpr int HEIGHT = 80;

	// frames to pause at
	constexpr int PAUSE_FRAME_1 = 5;
	constexpr int PAUSE_FRAME_2 = 10;
	constexpr int PAUSE_FRAME_3 = 16;
	constexpr int MAX_FRAMES = 16;
}