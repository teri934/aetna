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

class World {
private:
	vector<vector<float>> terrain;
	void generateTerrain(vector<vector<float>>* terrain);
public:
	size_t HEIGHT;
	size_t WIDTH;
	World(size_t HEIGHT, size_t WIDTH) : HEIGHT(HEIGHT), WIDTH(WIDTH){
		terrain.resize(HEIGHT, vector<float>(WIDTH));

		generateTerrain(&terrain);
	}
};

#endif

