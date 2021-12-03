#pragma once

#ifndef LAND_H_
#define LAND_H_

#include <SDL.h>

class LandGenerator {
public:
	void GenerateLand(SDL_Surface* screenSurface);
};

#endif
