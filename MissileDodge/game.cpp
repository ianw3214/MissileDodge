#include "game.h"

// constructor
game::game(SDL_Window* iWindow, SDL_Surface* iSurface) {

	// set the class window and surface pointers
	this->gWindow = iWindow;
	this->gSurface = iSurface;

	// call the initialization function
	init();

}

// function that runs the game
void game::startGame() {

	// render the initial sprites and transition into battle
	renderSprites();
	countDown();

	// start the game loop
	while (!quit) {	// keep looping as long as the player doesn't quit

		// while the game isn't paused
		if (!pause) {

			// clear the screen at the beginning of each loop
			SDL_FillRect(gSurface, nullptr, SDL_MapRGB(gSurface->format, 255, 255, 255));

			// missile spawning function
			spawnMissile();

			// handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				// if the user quits
				if (e.type == SDL_QUIT) {
					// end the game
					quit = true;
				}
				else {
					// call the event handler for each sprite
					hero->eventHandler(e);
				}
			}

			// handle collisions
			handleCollision();

			// update game sprites
			updateSprites();

		}
		// if the game is paused
		else {
			// let the program sit and not do anything until the user quits or unpauses
			SDL_WaitEvent(&e);
			// if the user quits the game
			if (e.type == SDL_QUIT) {
				// end the game
				quit = true;
			}
		}

		// render the images
		renderSprites();

	}

	return;

}

// initialization function
void game::init() {

	// initialize variables
	this->score = 0;
	this->quit = false;
	this->pause = false;
	this->missileSpawnCounter = constants::BASE_SPAWN_TIME;
	SCREEN_WIDTH = constants::SCREEN_WIDTH;
	SCREEN_HEIGHT = constants::SCREEN_HEIGHT;

	// add a background and push it to the sprite vector
	sprite * background = new sprite("assets/BG.png");
	sprites.push_back(background);

	// add a hero to the game
	hero = new player(200, constants::GROUND_LEVEL, "assets/HERO.png");

}

// function to handle sprite logic and update graphics each frame
void game::updateSprites() {

	// loop through the sprites vector and update each one
	for (unsigned int i = 0; i < sprites.size(); i++) {
		// draw the sprite to the screen
		if (sprites[i] != nullptr) {	// make sure the pointer isn't null
			// call different update functions for each sprite
			switch (sprites[i]->getType()) {
			case SPRITE:
				// default update function for normal sprite
				sprites[i]->update(gSurface);
				break;
			case MISSILE:
				// dynamic cast from sprite to missile class
				missile * temp = dynamic_cast<missile*>(sprites[i]);
				// call the missile update function
				temp->update(gSurface);
				break;
			}
		}
	}

	// update the hero
	hero->update(gSurface);

	return;

}

// function to handle sprite renderting
void game::renderSprites() {

	// loop through the sprites vector and render each one
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites[i]->render(gSurface);
	}

	// render a visual for the players health
	for (int i = 0; i < hero->getHealth(); i++) {
		// add a heart to the screen
		sprite heart((20 + i * 45), 20, "assets/HEART.png");
		// draw the heart to the screen
		heart.render(gSurface);
	}

	// render the hero
	hero->render(gSurface);

	// update the screen surface
	SDL_UpdateWindowSurface(gWindow);

	return;

}

// function to handle missile spawning
void game::spawnMissile() {

	// spawn a missile if the counter reaches 0
	if (missileSpawnCounter == 0) {

		// variable to calculate offest for missile spawning
		int x_offset;

		// randomize the offset to a random number between the screen sizes
		x_offset = rand() % (SCREEN_WIDTH - 20) + 10;	// take margins into account

		// add a missile to the game
		missile * temp = new missile(x_offset, -20, "assets/MISSILE.png");

		// reset the spawn counter
		missileSpawnCounter = constants::BASE_SPAWN_TIME;

		// add the missile to the vector
		sprites.push_back(temp);

	}
	// decrement the spawn counter
	missileSpawnCounter--;

	return;

}

// function that handles collisions between the hero and missiles
void game::handleCollision() {

	// check for collisions between missiles and player
	for (unsigned int i = sprites.size(); i > 0; i--) {
		
		// check if the sprite is a missile
		if (sprites[i-1]->getType() == MISSILE) {

			// if the hero is colliding with a missile
			if (SDL_HasIntersection(&(hero->getRect()), &(sprites.at(i - 1)->getRect()))) {
				
				// remove the pointer from the vector
				sprites.erase(sprites.begin() + i - 1);
				// apply damage to the player
				if (hero->takeDamage(1)) {	// the player is alive
					// TEMPORARY DEBUG CODE
					std::cout << "HEALTH" << hero->getHealth() << std::endl;
				}
				// the player is dead
				else {
					// set the game over flag to be true
					pause = true;
				}
				// break the current for loop so the missile doesn't get checked any further
				break;
				
			}
			// if the missile hits the ground
			if (sprites.at(i - 1)->getY() > 450) {
				// remove the missile pointer from the vector
				sprites.erase(sprites.begin() + i - 1);
				// add to the score
				score += constants::BASE_SCORE;
				// TEMPORARY DEUBG CODE
				std::cout << score << std::endl;
				// break the current for loop so the missile doesn't get checked any further
				break;
			}
		}
		
	}

	return;

}

// countdown function to transition into the game
void game::countDown() {

	// loop through the countdown numbers
	for (int i = 3; i >= 1; i--) {

		std::cout << i << std::endl;
		// show the number and set a delay
		SDL_Delay(999);
	}

	return;

}