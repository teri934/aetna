#include "land.h"
#include "perlin.h"
#include "hsv_rgb.h"

#include <SDL.h>
#include <iostream>
#include <vector>


using namespace siv;

void LandGenerator::GenerateLand(SDL_Surface* screen) {
	unsigned int* pixels = (unsigned int*)screen->pixels;

	double frequency = 2; //0.1-64
	int octaves = 1; //1-16

	const int width = screen->w;
	const int height = screen->h;
	double fx = width / frequency;
	double fy = height / frequency;


	PerlinNoise perlin(1234);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			auto value = (floor)(perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves) * 10.) / 10.;

			vector<int> v = Converter::hsvToRgb(200, 100, value);
			pixels[x + y * width] =
				SDL_MapRGBA(screen->format, v[0], v[1], v[2], 255);
		}
	}
}