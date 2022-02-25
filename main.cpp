#include <SDL.h>
#include <iostream>
#include "world.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const unsigned int frame = 500;

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	//Create window
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	texture = SDL_CreateTexture
	(
		renderer,
		SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);

	//SDL_Surface* icons = SDL_LoadBMP("palettes/tm_icons.bmp");
	//SDL_Texture* tm_icons = SDL_CreateTextureFromSurface(renderer, icons);
	//SDL_FreeSurface(icons);

	World world = World(SCREEN_HEIGHT, SCREEN_WIDTH, renderer);;
	unsigned int current, last = 0;

	bool cycle = true;
	while (cycle) {
		SDL_Event event;
		current = SDL_GetTicks();

		if (current - last > frame)
		{
			unsigned char* pixels = nullptr;
			int pitch = 0;

			//world.Step();

			SDL_LockTexture
			(
				texture,
				NULL,
				reinterpret_cast<void**>(&pixels),
				&pitch
			);
			world.RenderTerrain(pixels);
			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_UnlockTexture(texture);

			world.RenderBeings();
			SDL_RenderPresent(renderer);

			last = current;
		}
	}


	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );

	return 0;
}