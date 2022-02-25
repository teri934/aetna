#include <SDL.h>
#include <iostream>
#include "world.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const unsigned int frame = 200;

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
		SDL_PIXELFORMAT_BGR24,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);

	//SDL_Surface* icons = SDL_LoadBMP("palettes/tm_icons.bmp");
	//SDL_Texture* tm_icons = SDL_CreateTextureFromSurface(renderer, icons);
	//SDL_FreeSurface(icons);

	World world = World(SCREEN_HEIGHT, SCREEN_WIDTH);;
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
			world.Render(pixels);

			SDL_UnlockTexture(texture);

			//Mapping actors (numbered in linear manner) to texture atlas (8 rows, 8 columns).
			//sq88.x = (static_cast<int>(world.current_actor) * 8) % 64;
			//sq88.y = (static_cast<int>(world.current_actor) >> 3) * 8;

			SDL_RenderCopy(renderer, texture, NULL, NULL);
			//SDL_RenderCopy(renderer, tm_icons, &sq88, &icon_pos);
			SDL_RenderPresent(renderer);

			last = current;
		}
	}


	SDL_DestroyTexture(texture);
	//SDL_DestroyTexture(tm_icons);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );

	return 0;
}