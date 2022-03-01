#ifndef WORLD_H_
#define WORLD_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include "perlin.h"
#include "hsv_rgb.h"

#include "beings.h"

using namespace std;

enum class Color : Uint8 {
	R,
	G,
	B
};


class World {
private:
	size_t SIZE;

	double frequency = 5; //0.1-64
	int octaves = 2; //1-16
	double fx;
	double fy;
	const float FULL_CIRCLE = 360;
	const size_t HUE = 111;

	SDL_Renderer* renderer;

	const vector<string> paths = { "images/violet_flower_mini.bmp", "images/red_flower_mini.bmp", "images/sheep_mini.bmp", "images/volcano_mini.bmp" };
	vector<SDL_Texture*> textures;
	void generateTextures();

	vector<vector<float>> terrain;
	vector<being_ptr> nature;
	vector<being_ptr> animals;
	void generateTerrain(vector<vector<float>>* terrain);
	void generateDefaultBeings();
public:
	size_t HEIGHT;
	size_t WIDTH;
	Size WorldSize;
	vector<vector<ListBeings>> beings;

	World(size_t HEIGHT, size_t WIDTH, SDL_Renderer* renderer) : HEIGHT(HEIGHT), WIDTH(WIDTH), renderer(renderer){
		srand(time(NULL));

		WorldSize = Size(WIDTH, HEIGHT);
		SIZE = WIDTH * HEIGHT;
		fx = WIDTH / frequency;
		fy = HEIGHT / frequency;

		terrain.resize(HEIGHT, vector<float>(WIDTH));
		generateTerrain(&terrain);

		beings.resize(HEIGHT, vector<ListBeings>(WIDTH));

		generateDefaultBeings();
		generateTextures();
	}

	void RenderTerrain(unsigned char* target);
	void RenderBeings();
	void Simulate();
	Point GetResultPosition(Being* being, const Point& direction);
};

#endif

