#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gameVars.h"

class sprite {

public:

	// constructors
	sprite(std::string);
	sprite(int, int, std::string);
	virtual ~sprite();

	// getter/setter functions
	int getX();
	int getY();
	types getType();
	SDL_Rect getRect();

	// sprite class functions
	void update(SDL_Surface*);
	bool drawImage(SDL_Surface*);

protected:

	// the rect for sprite collisions and image bliting
	SDL_Rect rect;

	// type of sprite
	types type;

private:

	// SDL surface to contain image of sprite
	SDL_Surface * img;

	// initialize function
	void init(int, int, std::string);

};