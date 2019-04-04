#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "tiny3D.h"
#include "scene.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* xWindow = NULL;
SDL_Renderer* xRenderer = NULL;


bool sdl_init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL counld not initialize! SDL ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear")) //Linear filtering 
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		xWindow = SDL_CreateWindow("LgSoftRenderEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (xWindow == NULL)
		{
			printf("windows could not be created!, sdl error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			xRenderer = SDL_CreateRenderer(xWindow, -1, SDL_RENDERER_ACCELERATED);
			if (xRenderer == NULL)
			{
				printf("sdl renderer create failed, sdl error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(xRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}


void sdl_close()
{
	SDL_DestroyRenderer(xRenderer);
	SDL_DestroyWindow(xWindow);
	xWindow = NULL;
	xRenderer = NULL;
	SDL_Quit();
}



int main(int argc, char *argv[])
{
	printf("start engine");
	sdl_init();
	sdl_close();
	return 1;
}
