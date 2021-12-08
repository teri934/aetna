#pragma once

#ifndef LAND_H_
#define LAND_H_

#include <SDL.h>
#include <cstring>
#include <vector>
#include<iostream>

struct Field {
	double value;
	char sign;
};

enum Color {
	red,
	green,
	blue
};

enum Object {
	flower,
	volcano,
	sheep
};

class LandGenerator {
public:
	unsigned int* pixels = 0;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;

	const int WIDTH = 640;
	const int HEIGHT = 480;

	double frequency = 4; //0.1-64
	int octaves = 2; //1-16

	double fx = WIDTH / frequency;
	double fy = HEIGHT / frequency;

	const float BORDER_LAKE = 0.7;
	const float BORDER_FLOWER = 0.6;
	const float BORDER_SHEEP = 0.5;
	const float BORDER_VOLCANO = 0.15;


	LandGenerator(SDL_Surface* ss, SDL_Renderer* r) {
		screenSurface = ss;
		renderer = r;

		arr.resize(HEIGHT, std::vector<Field>(WIDTH));

	}
	void GenerateLand();

private:
	std::vector<std::vector<Field>> arr;
};


class LandPrinter {
public:
	void PrintLand(const LandGenerator& g, std::vector<std::vector<Field>>& arr);
	void PrintObjects(const LandGenerator& g, std::vector<std::vector<Field>>& arr, const char* path, const char c);
	void PrintObject(size_t& x, size_t& y, SDL_Texture* texture, const LandGenerator& g);

	const char* FLOWER_PATH = "images / flower_mini.bmp";
	const char* VOLCANO_PATH = "images/volcano_mini.bmp";
	const char* SHEEP_PATH = "images/sheep_mini.bmp";
};

#endif
