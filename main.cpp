#include <SDL.h>
#include <iostream>
#include "land.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{

			screenSurface = SDL_GetWindowSurface(window);

			LandGenerator generator(screenSurface);
			generator.GenerateLand();

			//Fill the surface white
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );

			//Wait ten seconds
			SDL_Delay( 10000 );
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}