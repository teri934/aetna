#include "land.h"
#include "perlin.h"
#include "hsv_rgb.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>


using namespace siv;

void LandGenerator::GenerateLand() {
	
	pixels = (unsigned int*)screenSurface->pixels;

	PerlinNoise perlin(1234);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 500);

	for (size_t y = 0; y < HEIGHT; ++y)              //inicializacia hodnot v arr (plocha, flower, lake, volcano, sheep) podla nejakych kriterii
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			auto value = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);


			if (value < BORDER_LAKE) {

				auto random = dist(mt);

				if(random == Object::flower && value > BORDER_FLOWER)
					arr[y][x] = Field(value, 'f');
				else if(random == Object::volcano && value  < BORDER_VOLCANO)
					arr[y][x] = Field(value, 'v');
				else if(random == Object::sheep && value > BORDER_SHEEP && value < BORDER_FLOWER)
					arr[y][x] = Field(value, 's');
				else
					arr[y][x] = Field(value, '*');
			}
			else
				arr[y][x] = Field(value, 'l');
		}
	}

	LandPrinter printer;
	printer.PrintLand(*this, arr);

	//SDL_Texture* background = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);

	printer.PrintObjects(*this, arr, printer.FLOWER_PATH, 'f');  //ja som to mala doteraz takto, ze sa mi to vsetko renderuje na seba
	printer.PrintObjects(*this, arr, printer.VOLCANO_PATH, 'v'); //ale v pripade ze by som tymi objektami chcela hybat, tak ich potrebujem nejako vymazat
	                                                             //tak som myslela, ze nejako to dat do inej texture... ako s tym kodom pre ovce tam dole
	                                                             //ze ich chcem v tej dalsej vrstve zmazat, ked to odkomentujes a spustis, tak uvidis, ako sa tam kopia




	//SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);

	//std::random_device rd_sheep;
	//std::mt19937 mt_sheep(rd_sheep());
	//std::uniform_int_distribution<int> dist_sheep(-5, 5);
	//while (simulation) {

	//	printer.PrintObjects(*this, arr, printer.SHEEP_PATH, 's');
	//	MoveSheep(dist_sheep(mt_sheep), dist(mt_sheep));
	//}
}

void LandGenerator::MoveSheep(int shift_x, int shift_y) {  //ma simulovat pohyb, este nie je dokoncena
	for (size_t y = 0; y < HEIGHT; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			if (arr[y][x].sign == 's') {
				//arr[y][x].sign = '*';

				size_t new_y = (y + shift_y) % HEIGHT;
				size_t new_x = (x + shift_x) % WIDTH;

				if(arr[new_y][new_x].sign != 'l')
					arr[new_y][new_x].sign = 's';
			}

		}
	}
}

void LandPrinter::PrintLand(const LandGenerator& g, vector<vector<Field>>& arr) {  //funkcia, ktora podla hodnoty arr priradi farbu pixelu na okne
	                                                                               //ak tam bolo l, tak je to jazero, takze nezalezi na value
	const float full_circle = 360;
	const size_t green_color = 222;
	const size_t blue_color = 111;


	for (size_t y = 0; y < g.HEIGHT; ++y)
	{
		for (size_t x = 0; x < g.WIDTH; ++x)
		{
			if (arr[y][x].sign == 'l') {
				vector<int> v = Converter::hsvToRgb(green_color / full_circle, 1, 1);
				g.pixels[x + y * g.WIDTH] = SDL_MapRGBA(g.screenSurface->format, v[Color::red], v[Color::green], v[Color::blue], 255);
			}
			else {
				auto floor_value = (floor)(arr[y][x].value * 10.) / 10.;
				vector<int> v = Converter::hsvToRgb(blue_color / full_circle, 1, floor_value);
				g.pixels[x + y * g.WIDTH] = SDL_MapRGBA(g.screenSurface->format, v[Color::red], v[Color::green], v[Color::blue], 255);
			}
		}
	}
}


void LandPrinter::PrintObjects(const LandGenerator& g, vector<vector<Field>>& arr, const char* path, const char c) {  //nacita konkretny obrazok
	                                                                                                                  // a pozrie na suradnice, kde sa ma vyprintit
	auto* image = SDL_LoadBMP(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g.renderer, image);
	SDL_FreeSurface(image);

	for (size_t y = 0; y < g.HEIGHT; ++y)
	{
		for (size_t x = 0; x < g.WIDTH; ++x)
		{
			if (arr[y][x].sign == c) {
				PrintObject(x, y, texture, g);
			}
		}
	}
}

void LandPrinter::PrintObject(size_t& x, size_t& y, SDL_Texture* texture, const LandGenerator& g) {

	SDL_Rect rect;
	rect.x = (x - 16) % g.WIDTH;
	rect.y = (y - 16) % g.HEIGHT;
	rect.w = 33;
	rect.h = 33 / 1.77;

	SDL_RenderCopy(g.renderer, texture, NULL, &rect);
	SDL_RenderPresent(g.renderer);
}
