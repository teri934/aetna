#include <cstdlib>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include "world.h"
#include "perlin.h"
#include "hsv_rgb.h"

using namespace siv;

void World::generateTerrain(vector<vector<float>>* terrain) {

	PerlinNoise perlin(1234);

	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			float value = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);
			(*terrain)[y][x] = value;
		}
	}
}

void World::Render(unsigned char* target) {
	const float full_circle = 360;
	const size_t green_color = 222;
	const size_t blue_color = 111;


	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{

			auto floor_value = (floor)(terrain[y][x] * 10.) / 10.;
			vector<int> colors = Converter::hsvToRgb(blue_color / full_circle, 1, floor_value);
			size_t current_pixel = static_cast<size_t>(3) * (y * WIDTH + x);
			target[current_pixel + static_cast<uint8_t>(Color::R)] = colors[static_cast<uint8_t>(Color::R)];
			target[current_pixel + static_cast<uint8_t>(Color::G)] = colors[static_cast<uint8_t>(Color::G)];
			target[current_pixel + static_cast<uint8_t>(Color::B)] = colors[static_cast<uint8_t>(Color::B)];
		}
	}
}