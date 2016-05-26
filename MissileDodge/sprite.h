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
	SDL_Rect getRect();
	// sprite class functions
	bool drawImage(SDL_Surface*);

protected:
	// the rect for sprite collisions and image bliting
	SDL_Rect rect;

private:
	// SDL surface to contain image of sprite
	SDL_Surface * img;
};