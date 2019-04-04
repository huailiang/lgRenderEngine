#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _MSC_VER
#include<Windows.h>
#endif // _MSC_VER



#include "SDL.h"
#include "tiny3D.h"
#include "scene.h"



const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const float fps = 30.0f;

int screen_keys[512];
float deltaTime = 0.0f;
Uint32 lastFrame = 0;

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
	printf("start engine %d ", sizeof(SDL_Event));
	if (sdl_init())
	{
		bool quit = false;
		bool firstMouse = true;
		float c_yaw = 0.0f;
		float c_pitch = 0.0f;
		float c_movementspeed = 2.0f;
		float c_mouse_sensitivity = 0.7f;
		float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
		device_t device;
		device_init(&device);
		int indicator = 0;
		int kbhit = 0;

		SDL_Event e;
		while (!quit)
		{
			Uint32 current = SDL_GetTicks();
			deltaTime = (current - lastFrame) * 0.001f;
			lastFrame = current;
			printf("fps delta :%f %f\n", deltaTime, 1.0f / deltaTime);
			

#ifdef _MSC_VER
			float wait = 1.0f / fps;
			if (deltaTime < wait)
			{
				Sleep(1000.0f* (wait - deltaTime));
			}
#endif // #ifdef _MSC_VER

			

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
					break;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					screen_keys[e.key.keysym.scancode] = 1;
				}
				else if (e.type == SDL_KEYUP)
				{
					screen_keys[e.key.keysym.scancode] = 0;
				}
				else if (e.type == SDL_MOUSEMOTION)
				{
					if (firstMouse)
					{
						c_lastX = e.motion.x;
						c_lastY = e.motion.y;
						firstMouse = false;
					}
					float xoffset = e.motion.x - c_lastX;
					float yoffset = e.motion.y - c_lastY;
					c_lastX = e.motion.x;
					c_lastY = e.motion.y;

					xoffset *= c_mouse_sensitivity;
					yoffset *= c_mouse_sensitivity;

					c_yaw += xoffset;
					c_pitch += yoffset;
					if (c_pitch > 89.0f)
						c_pitch = 89.0f;
					if (c_pitch < -89.0f)
						c_pitch = -89.0f;
				}
			}

			if (screen_keys[SDL_SCANCODE_W]) 
			{
				init_texture();
			}
			if (screen_keys[SDL_SCANCODE_S])
			{
			}
			if (screen_keys[SDL_SCANCODE_A])
			{
			}
			if (screen_keys[SDL_SCANCODE_D]) 
			{
			}
			if (screen_keys[SDL_SCANCODE_Q]) {}
			if (screen_keys[SDL_SCANCODE_E]) {}
			if (screen_keys[SDL_SCANCODE_UP]) {}
			if (screen_keys[SDL_SCANCODE_LEFT]){}
			if (screen_keys[SDL_SCANCODE_DOWN]){}
			if (screen_keys[SDL_SCANCODE_RIGHT]) {}
		}
		sdl_close();
	}
	return 0;

}
