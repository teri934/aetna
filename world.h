#ifndef WORLD_H_
#define WORLD_H_

#include <SDL.h>
#include <cstring>
#include <vector>
#include<iostream>

#include "beings.h"
#include "perlin.h"
#include "hsv_rgb.h"

using namespace std;

enum class Color : Uint8 {
	R,
	G,
	B
};

class World {
private:
	double frequency = 4; //0.1-64
	int octaves = 2; //1-16
	double fx;
	double fy;

	vector<vector<float>> terrain;
	void generateTerrain(vector<vector<float>>* terrain);
public:
	size_t HEIGHT;
	size_t WIDTH;
	World(size_t HEIGHT, size_t WIDTH) : HEIGHT(HEIGHT), WIDTH(WIDTH){

		fx = WIDTH / frequency;
		fy = HEIGHT / frequency;

		terrain.resize(HEIGHT, vector<float>(WIDTH));
		generateTerrain(&terrain);
	}

	void Render(unsigned char* target);
};

#endif

