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
	size_t SIZE;

	double frequency = 6; //0.1-64
	int octaves = 2; //1-16
	double fx;
	double fy;

	SDL_Renderer* renderer;

	const vector<string> paths = { "images/flower_mini.bmp", "images/sheep_mini.bmp", "images/volcano_mini.bmp" };
	vector<SDL_Texture*> textures;
	void generateTextures();

	vector<vector<float>> terrain;
	vector<being_ptr> beings;
	void generateTerrain(vector<vector<float>>* terrain);
	void generateDefaultBeings();
public:
	size_t HEIGHT;
	size_t WIDTH;
	World(size_t HEIGHT, size_t WIDTH, SDL_Renderer* renderer) : HEIGHT(HEIGHT), WIDTH(WIDTH), renderer(renderer){
		SIZE = WIDTH * HEIGHT;
		fx = WIDTH / frequency;
		fy = HEIGHT / frequency;

		terrain.resize(HEIGHT, vector<float>(WIDTH));
		generateTerrain(&terrain);

		generateDefaultBeings();
		generateTextures();
	}

	void RenderTerrain(unsigned char* target);
	void RenderBeings();
};

#endif

