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

	// countdown into the game
	countDown();

	// initialize the time variables
	cTime = SDL_GetTicks();
	lTime = cTime;

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

	return;

}

// function that handles central game logic
void game::gameLoop(double delta) {

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
		// if the user pressed the escape key
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			// enter the pause menu
			pause = true;
			// clear the players input keys
			hero->setKeysNone();
		}
		else {
			// call the event handler for each sprite
			hero->eventHandler(e);
		}
	}

	// handle collisions
	handleCollision();

	// update game sprites
	updateSprites(delta);

	// update difficulty
	if (difficultyCounter > 0) {
		difficultyCounter--;
	}
	else {
		LOG(diffucultyScale);
		difficultyCounter = constants::BASE_DIFFICULTY_TIME;
		diffucultyScale++;
		// set the modifiers to match the difficulty level
		spawnModifier += static_cast<float>(1.0 / (1.5 * diffucultyScale * diffucultyScale));
		speedModifier += static_cast<float>(1.0 / (diffucultyScale * diffucultyScale));
	}

	return;

}

// initialization function
void game::init() {

	// initialize random seed
	std::srand(static_cast<unsigned int>(std::time(0)));

	// initialize variables
	this->score = 0;
	this->quit = false;
	this->pause = false;
	this->missileSpawnCounter = constants::BASE_SPAWN_TIME;
	this->gameOver = false;
	this->diffucultyScale = 1;
	this->difficultyCounter = constants::BASE_DIFFICULTY_TIME;
	this->spawnModifier = 1.0;
	this->speedModifier = 1.0;

	// add a background and push it to the sprite vector
	sprite * background = new sprite("assets/BG.png");
	sprites.push_back(background);

	// initialize menu text
	sprite * normal = new sprite(300, 200, "assets/TEXT/RESUME.png");
	sprite * hover = new sprite(300, 200, "assets/TEXT/RESUME_SELECTED.png");
	menuItem resume = { *normal, *hover };
	menuItems.push_back(resume);

	normal = new sprite(300, 350, "assets/TEXT/QUIT.png");
	hover = new sprite(300, 350, "assets/TEXT/QUIT_SELECTED.png");
	menuItem quit = { *normal, *hover };
	menuItems.push_back(quit);

	// initialize countdown number text
	sprite * num = new sprite("assets/TEXT/0.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/1.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/2.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/3.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/4.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/5.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/6.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/7.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/8.png");
	numSprites.push_back(*num);
	num = new sprite("assets/TEXT/9.png");
	numSprites.push_back(*num);

	// ---------------------------------------------------TESTING CODE ---------------------------------------------------------
	boon * healthPack = new boon(400, constants::GROUND_LEVEL-boonConstants::HEIGHT, "assets/HEALTHPACK.png", HEALTH);
	sprites.push_back(healthPack);
	boon * invincible = new boon(500, constants::GROUND_LEVEL - boonConstants::HEIGHT, "assets/INVINCIBLE.png", INVINCIBLE);
	sprites.push_back(invincible);
	// -------------------------------------------------------------------------------------------------------------------------

	// add a hero to the game
	hero = new player(200, (constants::GROUND_LEVEL-playerConstants::HEIGHT), "assets/HERO.png");

	// default flag to quit
	this->flag = QUIT;

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

// function to handle missile spawning
void game::spawnMissile() {

	// spawn a missile if the counter reaches 0
	if (missileSpawnCounter == 0) {

		// variable to calculate offest for missile spawning
		int x_offset;

		// randomize the offset to a random number between the screen sizes
		x_offset = rand() % (constants::SCREEN_WIDTH - 20) + 10;	// take margins into account

		// add a missile to the game
		missile * temp = new missile(x_offset, -20, "assets/MISSILE.png", speedModifier);
		LOG(speedModifier);

		// reset the spawn counter
		missileSpawnCounter = static_cast<int>(constants::BASE_SPAWN_TIME / spawnModifier);
		// add the missile to the vector
		sprites.push_back(temp);

	}
	// decrement the spawn counter
	missileSpawnCounter--;

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
				// remove the pointer from the vector
				sprites.erase(sprites.begin() + i - 1);
				// apply damage to the player
				if (hero->takeDamage(1)) {
					// if the player is still alive, only earn half the points from that missile 
					score += 5;
				}
				// the player is dead
				else {
					// set the game over flag to be true
					gameOver = true;
					// reset the menu items
					menuItems.clear();
					// add the new ones for game over
					menuItems.push_back({ sprite(300, 200, "assets/TEXT/PLAY_AGAIN.png"), sprite(300, 200, "assets/TEXT/PLAY_AGAIN_SELECTED.png") });
					menuItems.push_back({ sprite(300, 350, "assets/TEXT/QUIT.png"), sprite(300, 350, "assets/TEXT/QUIT_SELECTED.png") });
					// pause the game
					pause = true;
				}

			} break;
			case BOON: {
				// ---------------------------------------------------TESTING CODE ---------------------------------------------------------
				if (sprites[i - 1]->getType() == BOON) {
					boon * temp = dynamic_cast<boon*>(sprites[i - 1]);
					if (temp->getBoonType() == HEALTH) {
						hero->heal(2);
						sprites.erase(sprites.begin() + i - 1);
					}
					if (temp->getBoonType() == INVINCIBLE) {
						hero->turnInvincible();
						sprites.erase(sprites.begin() + i - 1);
					}
				}
				// -------------------------------------------------------------------------------------------------------------------------
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
				// make sure that it isn't the game over menu to return to game
				if (!gameOver) {
					pause = false;
				}
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

	// if the menu is the gameover menu
	if (gameOver) {
		switch (selected) {
		case 0:		// PLAY AGAIN
			flag = GAME;
			// quit the game loop
			quit = true;
			break;
		case 1:		// QUIT GAME
			// quit the game
			quit = true;
			flag = QUIT;
			break;
		}

		// exit the function
		return;

	}

	// if function runs to here then the game isn't over yet
	// see what item is currently selected
	switch (selected) {
	case 0:
		// enter a countdown
		countDown();
		// resume the game and unpause
		this->pause = false;	
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