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

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 5000);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			auto value = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);


			if (value < 0.7) {

				auto random = dist(mt);

				if(random == 1)
					arr[y][x] = Field(value, 'f');
				else
					arr[y][x] = Field(value, '*');
			}
			else
				arr[y][x] = Field(value, 'l');
		}
	}

	LandPrinter::PrintLand(*this, arr);
}

void LandPrinter::PrintLand(const LandGenerator& g, vector<vector<Field>>& arr) {

	for (size_t y = 0; y < g.height; ++y)
	{
		for (size_t x = 0; x < g.width; ++x)
		{
			if (arr[y][x].sign == 'l') {
				vector<int> v = Converter::hsvToRgb(222 / 360., 1, 1);
				g.pixels[x + y * g.width] = SDL_MapRGBA(g.screenSurface->format, v[0], v[1], v[2], 255);
			}
			else {
				auto floor_value = (floor)(arr[y][x].value * 10.) / 10.;
				vector<int> v = Converter::hsvToRgb(111 / 360., 1, floor_value);
				g.pixels[x + y * g.width] = SDL_MapRGBA(g.screenSurface->format, v[0], v[1], v[2], 255);
			}
		}
	}

	auto* image = SDL_LoadBMP("images/flower_mini.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g.renderer, image);
	SDL_FreeSurface(image);

	for (size_t y = 0; y < g.height; ++y)
	{
		for (size_t x = 0; x < g.width; ++x)
		{
			if (arr[y][x].sign == 'f') {
				SDL_Rect rect;
				rect.x = x;
				rect.y = y;
				rect.w = 50;
				rect.h = 50 / 1.77;

				//SDL_BlitSurface(image, NULL, screenSurface, &rect);
				SDL_RenderCopy(g.renderer, texture, NULL, &rect);
				SDL_RenderPresent(g.renderer);
			}
		}
	}

}
