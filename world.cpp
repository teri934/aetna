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
			float value = (float)perlin.accumulatedOctaveNoise2D_0_1(x/fx, y/fy, octaves);
			(*terrain)[y][x] = value;
		}
	}
}


void World::generateTextures() {

	for (size_t i = 0; i < paths.size(); i++)
	{
		SDL_Surface* picture = SDL_LoadBMP(paths[i].c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, picture);
		textures.push_back(move(texture));
	}
}

void World::generateDefaultBeings() {

	const float LOWLAND = 0.6f;
	const float HIGHLAND = 0.3f;
	const float LOW_PROB = SIZE * 0.00001f;
	const float HIGH_PROB = SIZE * 0.0002f;

	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			int value = rand() % SIZE;


			if (value < LOW_PROB && terrain[y][x] > 0.3f && terrain[y][x] < LOWLAND) {
				nature.push_back(make_unique<RedFlower>(Point(x, y), this));
				beings[y][x] = ListBeings::RED_FLOWER;
			}
			else if (value < LOW_PROB && terrain[y][x] > HIGHLAND) {
				animals.push_back(make_unique<Sheep>(Point(x, y), this));
				beings[y][x] = ListBeings::SHEEP;
			}
			else if (value < HIGH_PROB && terrain[y][x] > LOWLAND) {
				nature.push_back(make_unique<VioletFlower>(Point(x, y), this));
				beings[y][x] = ListBeings::VIOLET_FLOWER;
			}
			else
				beings[y][x] = ListBeings::EMPTY;

		}
	}
}

void World::RenderTerrain(unsigned char* target) {

	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{

			auto floor_value = (floor)(terrain[y][x] * 10.) / 10.;
			vector<int> colors = Converter::hsvToRgb(HUE / FULL_CIRCLE, 1, floor_value);
			size_t current_pixel = static_cast<size_t>(3) * (y * WIDTH + x);
			target[current_pixel + static_cast<uint8_t>(Color::R)] = colors[static_cast<uint8_t>(Color::R)];
			target[current_pixel + static_cast<uint8_t>(Color::G)] = colors[static_cast<uint8_t>(Color::G)];
			target[current_pixel + static_cast<uint8_t>(Color::B)] = colors[static_cast<uint8_t>(Color::B)];
		}
	}
}

void World::RenderBeings() {

	SDL_Rect rect;

	for (size_t i = 0; i < nature.size(); ++i)
	{
		rect.x = (int)nature[i]->position.x;
		rect.y = (int)nature[i]->position.y;
		rect.w = (int)nature[i]->GetSize().width;
		rect.h = (int)nature[i]->GetSize().height;

		auto ID = static_cast<uint8_t>(nature[i]->GetBeing());
		SDL_RenderCopy(renderer, textures[ID], NULL, &rect);
	}

	for (size_t i = 0; i < animals.size(); ++i)
	{
		rect.x = (int)animals[i]->position.x;
		rect.y = (int)animals[i]->position.y;
		rect.w = (int)animals[i]->GetSize().width;
		rect.h = (int)animals[i]->GetSize().height;

		auto ID = static_cast<uint8_t>(animals[i]->GetBeing());
		SDL_RenderCopy(renderer, textures[ID], NULL, &rect);
	}
}

void World::Simulate() {
	for (size_t i = 0; i < nature.size(); ++i)
		nature[i]->Simulate();

	for (size_t i = 0; i < animals.size(); ++i)
		animals[i]->Simulate();
}

