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
			auto value = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);
			arr[y][x] = value;
		}
	}

	LandPrinter::PrintLand(*this, arr);
}

void LandPrinter::PrintLand(const LandGenerator& g, vector<vector<double>>& arr) {
	
	for (size_t y = 0; y < g.height; ++y)
	{
		for (size_t x = 0; x < g.width; ++x)
		{
			auto floor_value = (floor)(arr[y][x] * 10.) / 10.;
			vector<int> v = Converter::hsvToRgb(120 / 360., 1, floor_value);
			g.pixels[x + y * g.width] = SDL_MapRGBA(g.screenSurface->format, v[0], v[1], v[2], 255);
		}
	}
}
