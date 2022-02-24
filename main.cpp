#include <SDL.h>
#include <iostream>
#include "land.h"
#include "world.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

			
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	//LandGenerator generator(screenSurface, renderer);
	//generator.GenerateLand();

			
	//Update the surface
	SDL_UpdateWindowSurface(window);

	//Wait ten seconds
	SDL_Delay( 10000 );



	SDL_FreeSurface(screenSurface);


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}