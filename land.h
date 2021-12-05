#pragma once

#ifndef LAND_H_
#define LAND_H_

#include <SDL.h>
#include <cstring>
#include <vector>
#include<iostream>

class LandGenerator {
public:
	unsigned int* pixels = 0;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;

	const int width = 640;
	const int height = 480;

	double frequency = 2; //0.1-64
	int octaves = 1; //1-16

	double fx = width / frequency;
	double fy = height / frequency;


	LandGenerator(SDL_Surface* ss, SDL_Renderer* r) {
		screenSurface = ss;
		renderer = r;

		arr.resize(height, std::vector < double > (width));
	}
	void GenerateLand();

private:
	std::vector<std::vector<double>> arr;
};

class LandPrinter {
public:
	static void PrintLand(const LandGenerator& g, std::vector<std::vector<double>>& arr);
};

#endif
