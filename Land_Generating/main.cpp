#include <iostream>
#include "world.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const unsigned int frame = 100;

int main( int argc, char* args[] )
{
	float frequency;
	int octaves;

	string line;
	cout << "Choose frequency for the terrain in range 0.1 - 64 (default 8) or press enter:\n";
	try {
		getline(cin, line);
		frequency = stof(line);
	}
	catch (exception e) {
		frequency = 8;
	}

	std::cout << "Choose octaves for the terrain in range 1 - 16 (default 4) or press enter:\n";
	try {
		getline(cin, line);
		octaves = stoi(line);
	}
	catch (exception e) {
		octaves = 4;
	}



	SDL_Window* window = NULL;
	SDL_Renderer* renderer;
	SDL_Texture* texture_terrain;
	SDL_Texture* texture_explosions;

	//Create window
	window = SDL_CreateWindow( "Aetna", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);

	SDL_Surface* icon = SDL_LoadBMP("images/volcano_mini.bmp");
	SDL_SetWindowIcon(window, icon);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture_terrain = SDL_CreateTexture
	(
		renderer,
		SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
	texture_explosions = SDL_CreateTexture
	(
		renderer,
		SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);


	World world = World(SCREEN_HEIGHT, SCREEN_WIDTH, renderer, frequency, octaves);;
	unsigned int current, last = 0;
	world.LockAndRender(texture_terrain, false);

	//main program loop
	bool cycle = true;
	while (cycle) {
		SDL_Event event;
		current = SDL_GetTicks();

		if (current - last > frame)
		{
			world.Simulate();

			if (world.Exploding) {
				world.LockAndRender(texture_explosions, true);
				SDL_RenderCopy(renderer, texture_explosions, NULL, NULL);
			}
			else
				SDL_RenderCopy(renderer, texture_terrain, NULL, NULL);


			world.RenderBeings();
			world.RenderMenu();

			SDL_RenderPresent(renderer);

			last = current;
		}

		//events from user
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				cycle = false;
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					world.CheckUnclick(static_cast<uint32_t>(event.button.x), static_cast<uint32_t>(event.button.y));
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					world.CheckClick(static_cast<uint32_t>(event.button.x), static_cast<uint32_t>(event.button.y));
				}
				break;
			}
		}
	}


	SDL_DestroyTexture(texture_terrain);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );

	return 0;
}