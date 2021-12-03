#include "land.h"
#include "perlin.h"
#include "hsv_rgb.h"

#include <SDL.h>
#include <iostream>
#include <vector>


using namespace siv;

void LandGenerator::GenerateLand() {
	
	pixels = (unsigned int*)screenSurface->pixels;

	PerlinNoise perlin(1234);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			auto value = (floor)(perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves) * 10.) / 10.;

			vector<int> v = Converter::hsvToRgb(200, 100, value);
			pixels[x + y * width] =
				SDL_MapRGBA(screenSurface->format, v[0], v[1], v[2], 255);
		}
	}

	LandPrinter::PrintLand(*this, arr);
}

void LandPrinter::PrintLand(const LandGenerator& g, vector<vector<unsigned int>>& arr) {
	
	for (size_t y = 0; y < g.height; ++y)
	{
		for (size_t x = 0; x < g.width; ++x)
		{
			g.pixels[x + y * g.width] = arr[y][x];
		}
	}
}
