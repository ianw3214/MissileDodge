#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class sprite {

public:
	// constructors
	sprite(std::string, SDL_Surface*);
	sprite(int, int, std::string, SDL_Surface*);
	// getter/setter functions
	int getX();
	int getY();
	// sprite class functions
	bool drawImage(SDL_Surface*);

protected:
	// position integers
	int x;
	int y;

private:
	// SDL surface to contain image of sprite
	SDL_Surface * img;
	
};