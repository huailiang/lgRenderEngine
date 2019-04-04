#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "tiny3D.h"

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

void init_texture()
{
	int width = 256, height = 256;
	texture_t* texture = &textures[texture_count++];
	uint* bits = (uint*)malloc(sizeof(uint)* width * height);
	int i, j;
	for (j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			int x = i / 32, y = j / 32;
			bits[j*width + i] = ((x + y) & 1) ? 0xffffffff : 0xff3fbcef;
		}
	}
	texture->datas_len = 1;
	texture->datas = (uint**)malloc(1 * sizeof(uint*));
	texture->datas[0] = bits;
	texture->width = width;
	texture->height = height;
	texture->use_mipmap = true;
	/*generate_mipmaps(texture, 1.01f);

	make_texture_by_png("mabu", true);
	make_texture_by_png("dimian", true);*/
}

int main(int argc, char *argv[])
{
	printf("start engine");
	sdl_init();
	SDL_Delay(3000);
	sdl_close();
	return 1;
}
