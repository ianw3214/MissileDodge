#include "game.h"

// constructor
game::game(SDL_Window* iWindow, SDL_Surface* iSurface) {

	// set the class window and surface pointers
	this->gWindow = iWindow;
	this->gSurface = iSurface;

	// call the initialization function
	init();

}

// getter function for flag
state game::getFlag() {
	return this->flag;
}

// function that runs the game
void game::startGame() {

	// fade in transition
	fade(0);

	// countdown into the game
	countDown();

	// initialize the time variables
	cTime = SDL_GetTicks();
	lTime = cTime;

	// start the boon spawning timer
	SDL_TimerID boonSpawnTimer = SDL_AddTimer(1000, boonTimer, this);
	// start the difficulty increase timer
	SDL_TimerID difficultyIncreaseTimer = SDL_AddTimer(constants::BASE_DIFFICULTY_TIME, difficultyTimer, this);
	// start the missile spawning timer
	SDL_TimerID missileSpawnTimer = SDL_AddTimer(constants::BASE_SPAWN_TIME, missileSpawner, this);

	// start the game loop
	while (!quit) {	// keep looping as long as the player doesn't quit

		// set the current time
		cTime = SDL_GetTicks();

		// if the game is paused
		if (pause) {
			// update the pause menu to the screen
			menuUpdate();
		}
		else {
			// pass the difference in time to the game loop function
			gameLoop(static_cast<double>(cTime - lTime) / 1000);
		}

		// render the images
		renderSprites();

		// render the menu if it is paused
		if (pause) {
			menuRender();
		}

		// update the screen surface
		SDL_UpdateWindowSurface(gWindow);

		// set the last time to this time to calculate difference
		lTime = cTime;

	}

	// if the game was quit because the player died, show the death menu
	if (gameOver) {
		// fade out into the death menu
		fade(1);
		gameOverMenu * gMenu = new gameOverMenu(gWindow, gSurface);
		this->flag = gMenu->getFlag();
	}

	// remove the timer once the game finishes
	SDL_RemoveTimer(boonSpawnTimer);
	SDL_RemoveTimer(difficultyIncreaseTimer);
	SDL_RemoveTimer(missileSpawnTimer);
	hero->waitTimer();

	return;

}

// function that handles central game logic
void game::gameLoop(double delta) {

	// clear the screen at the beginning of each loop
	SDL_FillRect(gSurface, nullptr, SDL_MapRGB(gSurface->format, 255, 255, 255));

	// handle events on queue
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			quit = true;
		}
		// if the user pressed the escape key
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			// enter the pause menu
			pause = true;
			// clear the players input keys
			hero->setKeysNone();
		}
		else {
			// call the event handler for sprites if the game is not paused
			hero->eventHandler(e);
		}
	}

	// handle collisions
	handleCollision();

	// update game sprites
	updateSprites(delta);

	return;

}

// initialization function
void game::init() {

	// initialize variables
	this->score = 0;
	this->quit = false;
	this->pause = false;
	this->gameOver = false;
	this->difficultyScale = 1;
	this->spawnModifier = 1.0;
	this->speedModifier = 1.0;

	// add a background and push it to the sprite vector
	sprite * background = new sprite("assets/BG.png");
	sprites.push_back(background);

	// initialize menu text
	menuItems.push_back({ sprite(300, 200, "assets/TEXT/RESUME.png"), sprite(300, 200, "assets/TEXT/RESUME_SELECTED.png") });
	menuItems.push_back({ sprite(300, 250, "assets/TEXT/QUIT.png"), sprite(300, 250, "assets/TEXT/QUIT_SELECTED.png") });

	// initialize number text
	numSprites.push_back(sprite("assets/TEXT/0.png"));
	numSprites.push_back(sprite("assets/TEXT/1.png"));
	numSprites.push_back(sprite("assets/TEXT/2.png"));
	numSprites.push_back(sprite("assets/TEXT/3.png"));
	numSprites.push_back(sprite("assets/TEXT/4.png"));
	numSprites.push_back(sprite("assets/TEXT/5.png"));
	numSprites.push_back(sprite("assets/TEXT/6.png"));
	numSprites.push_back(sprite("assets/TEXT/7.png"));
	numSprites.push_back(sprite("assets/TEXT/8.png"));
	numSprites.push_back(sprite("assets/TEXT/9.png"));

	// add a hero to the game
	hero = new player(200, (constants::GROUND_LEVEL-playerConstants::HEIGHT), "assets/HERO_SS.png");

	// default flag to quit
	this->flag = QUIT;

	return;

}

// function to handle sprite logic and update graphics each frame
void game::updateSprites(double delta) {

	// loop through the sprites vector and update each one
	for (unsigned int i = sprites.size(); i > 0; i--) {
		// draw the sprite to the screen
		if (sprites[i-1] != nullptr) {	// make sure the pointer isn't null
			// call different update functions for each sprite
			switch (sprites[i-1]->getType()) {
			case SPRITE:{
				// default update function for normal sprite
				sprites[i-1]->update(gSurface, delta);
			} break;
			case MISSILE:{
				// dynamic cast from sprite to missile class
				missile * temp = dynamic_cast<missile*>(sprites[i-1]);

				// remove the missile if it hits the ground
				if (temp->getY() > (constants::GROUND_LEVEL-missileConstants::HEIGHT)) {
					sprites.erase(sprites.begin() + i - 1);
					// add to the score
					score += constants::BASE_SCORE;
				} else {
					// call the missile update function if the missile hasn't hit the ground
					temp->update(gSurface, delta);
				}

			} break;
			case BOON: {
				// dynamic cast from sprite to boon class
				boon * temp = dynamic_cast<boon*>(sprites[i - 1]);

				// remove the boon if it hits the ground
				if (temp->getY() > (constants::GROUND_LEVEL - missileConstants::HEIGHT)) {
					sprites.erase(sprites.begin() + i - 1);
					// add to the score
					score += constants::BASE_SCORE;
				}
				else {
					// call the missile update function if the missile hasn't hit the ground
					temp->update(delta);
				}

			} break;

			}
		}
	}
	
	// update the hero
	hero->update(gSurface, delta);

	return;

}

// function to handle sprite renderting
void game::renderSprites() {

	// loop through the sprites vector and render each one
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites[i]->render(gSurface);
	}

	// render the hearts according to player health
	switch (hero->getHealth()) {
	case 1:{
		sprite temp(20, 20, "assets/HEALTH1.png");
		temp.render(gSurface);
	}	break;
	case 2: {
		sprite temp(20, 20, "assets/HEALTH2.png");
		temp.render(gSurface);
	}	break;
	case 3: {
		sprite temp(20, 20, "assets/HEALTH3.png");
		temp.render(gSurface);
	}	break;
	}

	// render the points with numbers onto the screen
	std::string scoreString = std::to_string(score);
	// loop through numbers and print them
	for (unsigned int i = 0; i < scoreString.size(); i++) {
		sprite temp("assets/TEXT/0.png");
		switch (scoreString[i]) {
		case '0':
			temp = numSprites.at(0);
			break;
		case '1':
			temp = numSprites.at(1);
			break;
		case '2':
			temp = numSprites.at(2);
			break;
		case '3':
			temp = numSprites.at(3);
			break;
		case '4':
			temp = numSprites.at(4);
			break;
		case '5':
			temp = numSprites.at(5);
			break;
		case '6':
			temp = numSprites.at(6);
			break;
		case '7':
			temp = numSprites.at(7);
			break;
		case '8':
			temp = numSprites.at(8);
			break;
		case '9':
			temp = numSprites.at(9);
			break;
		}
		// set the position of the number
		temp.setPos(450 + i * 40, 20);
		// call the render function for the sprite
		temp.render(gSurface);
	}
	// render the hero
	hero->render(gSurface);

	return;

}

// function that handles collisions between the hero and missiles
void game::handleCollision() {

	// loop through all the sprites in the game
	for (unsigned int i = sprites.size(); i > 0; i--) {
		
		// check if the hero is colliding with the current sprite
		if (SDL_HasIntersection(&(hero->getRect()), &(sprites.at(i - 1)->getRect()))) {

			// go through all the different types of collisions
			switch (sprites[i - 1]->getType()) {
			case MISSILE: {
				missile * temp = dynamic_cast<missile*>(sprites[i - 1]);

				switch (temp->getMissileType()) {

				case GAS: {
					// call the slow down function when the hero is hit by a gas missile
					if (!hero->getSpeedBoost()) {		// make sure the hero is not in the middle of a speed boost
						hero->slowDown();
					}
				} break;
				// have the default behave like a normal missile
				case NORMAL: 
				default: {
					// apply damage to the player
					if (hero->takeDamage(1)) {
						// if the player is still alive, only earn half the points from that missile 
						score += 5;
					}	// the player is dead
					else {
						// set the game over flag to be true
						// go to the death menu when when the game is over
						this->gameOver = true;
						quit = true;
					}
				} break;

				}
				// remove the pointer from the vector
				sprites.erase(sprites.begin() + i - 1);

			} break;
			case BOON: {
				// call the boon handling function from the hero class according to the boon consumed
				boon * temp = dynamic_cast<boon*>(sprites[i - 1]);
				hero->boonHandler(dynamic_cast<boon*>(sprites[i - 1])->getBoonType());
				sprites.erase(sprites.begin() + i - 1);
			} break;
			}
		}		
		
	}

	return;

}

// countdown function to transition into the game
void game::countDown() {

	// loop through the countdown numbers
	for (int i = 3; i > 0; i--) {

		// render sprites under the numbers
		renderSprites();

		// create a new number sprite from the vector 
		sprite temp = numSprites.at(i);
		// set the position of the number to be the middle of the screen
		temp.setPos((constants::SCREEN_WIDTH/2-constants::FONT_WIDTH/2), 
					(constants::SCREEN_HEIGHT/2-constants::FONT_HEIGHT/2));

		// call the render function of the number
		temp.render(gSurface);

		// update the window surface
		SDL_UpdateWindowSurface(gWindow);

		// set a one second delay until the next number
		SDL_Delay(990);
	}

	// remove any keys pressed from event queue during countdown
	SDL_FlushEvent(SDL_KEYDOWN);

	return;

}

// update function
void game::menuUpdate() {

	// get the inputs from the user
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			this->quit = true;
		}
		// if the user presses a key
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				// if the user pressese a down button
			case SDLK_s:
			case SDLK_DOWN: {
				// if the current selected item is less than the total amount of items
				if (selected < (menuItems.size() - 1)) {
					// add one to selected
					selected++;
				}
			}break;
				// if the user presses an up button
			case SDLK_w:
			case SDLK_UP: {
				// if the current selected item is higher than 0
				if (selected > 0) {
					// minus one to selected
					selected--;
				}
			} break;
			case SDLK_RETURN:
			case SDLK_SPACE: {
				// call the select function when the user pressed a select key
				select();
			} break;
			case SDLK_ESCAPE: {				// return to the game if the user quits the menu
				pause = false;
				// reset the selected menu item
				selected = 0;
			} break;
			}
		}

	}

	return;

}

// function called upon user pressing enter
void game::select() {

	// if function runs to here then the game isn't over yet
	// see what item is currently selected
	switch (selected) {
	case 0:
		// resume the game and unpause
		this->pause = false;
		LOG(this->pause);
		// reset current time and last time
		cTime = SDL_GetTicks();
		lTime = cTime;
		break;
	case 1:
		// quit the game and dont go into battle
		quit = true;
		break;
	}

	return;

}

// function that renders menu text
void game::menuRender() {

	// loop through all the menu items
	for (unsigned int i = 0; i < menuItems.size(); i++) {
		// if the current loop is the selected item
		if (selected == i) {
			// render the selected sprite
			menuItems.at(i).hover.render(gSurface);
		}
		// if it is not the selected one
		else {
			// render the normal sprite
			menuItems.at(i).normal.render(gSurface);
		}
	}

	return;

}

// timer functions
Uint32 game::boonTimer(Uint32 interval, void * ptr) {

	game * cGame = (game*)ptr;
	
	// new randomization seed
	srand(time(0));

	// only spawn boons if the game is not paused
	if (!cGame->pause) {
		// have a 1 in 10 change to spawn boons every second
		int spawnKey = rand() % 10;
		if (spawnKey==5) {
			// randomly decide the type of boon to spawn
			int key = rand() % 3;
			// randomly decide the x coordinate
			int x_offset = rand() % (constants::SCREEN_WIDTH - 100);
			switch (key) {
			case 0: {
				// spawn a health pack 
				boon * healthPack = new boon(50 + x_offset, 0, "assets/HEALTHPACK.png", HEALTH);
				cGame->sprites.push_back(healthPack);
			} break;
			case 1: {
				// spawn an invincibility boost
				boon * invincible = new boon(50 + x_offset, 0, "assets/INVINCIBLE.png", INVINCIBLE);
				cGame->sprites.push_back(invincible);
			} break;
			case 2: {
				// spawn a speed boost
				boon * speed = new boon(10 + x_offset, 0, "assets/SPEED.png", SPEED);
				cGame->sprites.push_back(speed);
			} break;
			default: {
				LOG("THIS IS NOT SUPPOSED TO HAPPEN :(");
			} break;

			}

		}
	}

	return interval;

}

Uint32 game::difficultyTimer(Uint32 time, void * ptr) {

	/*	increase the difficulty of the game by increasing the difficulty scale
		changes the modifiers of missile speed and spawn rate to increase difficulty
		TODO: Add boss fights at certain difficulty scales to make game more challenging
		
	*/
		
	// get the pointer for the game 
	game * cGame = (game*)ptr;

	// change the difficulty only if the game isn't paused
	if (!cGame->pause) {
		cGame->difficultyScale++;

		// set the modifiers to match the difficulty level
		cGame->spawnModifier += static_cast<float>(1.0 / (1.5 * cGame->difficultyScale * cGame->difficultyScale));
		cGame->speedModifier += static_cast<float>(1.0 / (cGame->difficultyScale * cGame->difficultyScale));
	}

	// set the difficulty to increase again at the same interval
	return time;

}

Uint32 game::missileSpawner(Uint32 time, void *ptr) {

	// get the pointer for the game
	game * cGame = (game*)ptr;

	// only spawn missiles if the game isn't paused
	if (!cGame->pause) {
		// variable to calculate offest for missile spawning
		int x_offset;

		// randomize the offset to a random number between the screen sizes
		x_offset = rand() % (constants::SCREEN_WIDTH - 20) + 10;	// take margins into account

		missile * temp = new missile(x_offset, -20, "assets/MISSILE.png", cGame->speedModifier, NORMAL);

		// add the missile to the vector
		cGame->sprites.push_back(temp);

		// use a random number key to decide if a gas missile should be spawned
		int key = rand() % 10;

		// 1 in 10 chance to spawn a gas missile
		if (key == 0) {
			// same code as above except a change in missile type
			int x_offset = rand() % (constants::SCREEN_WIDTH - 20) + 10;
			missile * temp = new missile(x_offset, -20, "assets/GASMISSILE.png", cGame->speedModifier, GAS);
			cGame->sprites.push_back(temp);
		}

	}

	// spawn another missile at the same interval
	return time;

}

// fade in / fade out functions that takes a parameter of 0 or 1 for in / out
void game::fade(int key) {

	// time variables to help fade in function stay within a time frame
	unsigned int bTick, cTick;
	unsigned int time = constants::BASE_FADE_TIME;

	// black image to cover the screen with
	SDL_Surface * temp;
	temp = IMG_Load("assets/BLACK.png");
	if (!temp) {	// if the image failed to load
					// output the error
		std::cout << "Failed to load image, SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	// update the alpha values depending on the difference in time elapsed
	bTick = SDL_GetTicks();
	cTick = bTick;
	while ((cTick - bTick) < time) {

		// render the base menu first
		renderSprites();

		// set the alpha depenidng on time elapsed
		// if key is 0, fade in; if key is 1, fade out
		if (key == 0) {
			SDL_SetSurfaceAlphaMod(temp, 255 - ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (key == 1) {
			SDL_SetSurfaceAlphaMod(temp, ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (SDL_BlitSurface(temp, nullptr, gSurface, nullptr) < 0) {
			// output the error
			std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		}

		SDL_UpdateWindowSurface(gWindow);

		// update the current tick value
		cTick = SDL_GetTicks();
	}

	return;

}
