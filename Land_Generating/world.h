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

	double frequency = 8; //0.1-64
	int octaves = 4; //1-16
	double fx;
	double fy;
	const float FULL_CIRCLE = 360;
	const int MULTI = 10;
	const size_t HUE_TERRAIN = 111;
	const size_t HUE_EXPLOSION = 55;

	SDL_Rect menu;
	int stepMenu;
	int paddingMenu;
	Size sizeMenu;

	SDL_Renderer* renderer;

	const vector<string> paths = { "images/violet_flower_mini.bmp", "images/red_flower_mini.bmp", "images/sheep_mini.bmp", 
		                           "images/volcano_mini.bmp", "images/cross_mini.bmp", "images/menu.bmp"};
	vector<SDL_Texture*> textures;
	void generateTextures();

	vector<vector<float>> terrain;
	void generateTerrain(vector<vector<float>>* terrain);
	void generateDefaultBeings();
	void renderArray(vector<being_ptr>* arr);
	void checkVolcanos(unsigned int x, unsigned int y);
	void assignPixels(unsigned char* target, size_t y, size_t x, const size_t HUE, float value);


public:
	size_t HEIGHT;
	size_t WIDTH;
	Size WorldSize;
	bool Exploding = false;
	vector<vector<ListBeings>> Beings;
	vector<being_ptr> Nature;
	vector<being_ptr> Animals;
	vector<being_ptr> Volcanos;
	vector<being_ptr> Objects;
	vector<vector<bool>> ExplosionTerrain;

	World(size_t HEIGHT, size_t WIDTH, SDL_Renderer* renderer) : HEIGHT(HEIGHT), WIDTH(WIDTH), renderer(renderer){
		srand((unsigned int)time(NULL));

		WorldSize = Size((int)WIDTH, (int)HEIGHT);
		SIZE = WIDTH * HEIGHT;
		fx = WIDTH / frequency;
		fy = HEIGHT / frequency;

		ExplosionTerrain.resize(HEIGHT, vector<bool>(WIDTH));
		terrain.resize(HEIGHT, vector<float>(WIDTH));
		generateTerrain(&terrain);

		Beings.resize(HEIGHT, vector<ListBeings>(WIDTH));

		generateDefaultBeings();
		generateTextures();

		menu.w = (int)WIDTH / MULTI;
		menu.h = (int)HEIGHT >> 2;
		menu.x = 0;
		menu.y = (menu.h >> 1) - (menu.h >> 2);

		stepMenu = menu.h / (MULTI >> 1);
		paddingMenu = menu.h / 3;
		sizeMenu = Size(menu.w, stepMenu);
	}

	void RenderTerrain(unsigned char* target);
	void RenderExplosions(unsigned char* target);
	void RenderMenu();
	void RenderBeings();
	void Simulate();
	Point GetResultPosition(Being* being, const Point& direction);
	ListBeings GetResultBeing(Being* being, Point& direction);
	void EraseBeing(Being* being, vector<being_ptr>* arr, ListBeings newBeing);
	void LockAndRender(SDL_Texture* texture, bool exploding);
	void CheckClick(unsigned int x, unsigned int y);
	bool CheckExplodingVolcanos();
};

#endif

