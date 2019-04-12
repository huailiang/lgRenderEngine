#include "SDL.h"
#include "utils.h"
#include "engine.h"
#include <stdio.h>
#include "common.h"
#include "scene.h"

int screen_keys[KEY_CNT];
float deltaTime = 0.0f;
Uint32 lastFrame = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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
		window = SDL_CreateWindow("lg Cross-platform SoftwareRender Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("windows could not be created!, sdl error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("sdl renderer create failed, sdl error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void sdl_close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}

int main(int argc, char * argv[])
{
	if (sdl_init())
	{
		bool quit = false;

		device_t device;
		device_init(&device);
		int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
		int indicator = 0;
		int kbhit = 0;
		float c_yaw = 0.0f;
		float c_pitch = 0.0f;
		float c_movementspeed = 2.0f;
		float c_mouse_sensitivity = 0.7f;
		float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
		bool firstMouse = true;
		memset(screen_keys, 0, sizeof(int) * KEY_CNT);

		init_scene(&device);
        
		object_t *controlObj = g_box;
		SDL_Event e;
		while (!quit)
		{
			Uint32 currentFrame = SDL_GetTicks();
			deltaTime = (currentFrame - lastFrame) * 1.0f / 1000;
			lastFrame = currentFrame;
			printf("fps: %04.2f\n", deltaTime < 1e-2 ? 100.0f : 1.0f / deltaTime);
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
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
					if (c_pitch > 89.0f) c_pitch = 89.0f;
					if (c_pitch < -89.0f) c_pitch = -89.0f;
					main_camera->dirty = true;
				}
			}
			if (screen_keys[SDL_SCANCODE_W])
            {
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = main_camera->front;
				vector_scale(&temp, velocity);
				vector_add(&main_camera->pos, &main_camera->pos, &temp);
				main_camera->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_S])
            {
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = main_camera->front;
				vector_scale(&temp, velocity);
				vector_sub(&main_camera->pos, &main_camera->pos, &temp);
				main_camera->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_A]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp;
				vector_crossproduct(&temp, &main_camera->front, &main_camera->worldup);
				vector_normalize(&temp);
				vector_scale(&temp, velocity);
				vector_add(&main_camera->pos, &main_camera->pos, &temp);
				main_camera->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_D]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp;
				vector_crossproduct(&temp, &main_camera->front, &main_camera->worldup);
				vector_normalize(&temp);
				vector_scale(&temp, velocity);
				vector_sub(&main_camera->pos, &main_camera->pos, &temp);
				main_camera->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_Q]) 
			{
				controlObj->theta -= 0.04f;
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_E]) 
			{
				controlObj->theta += 0.04f;
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_UP]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = { 0.0f, 0.0f, 1.0f, 0.0f };
				vector_scale(&temp, velocity);
				vector_add(&controlObj->pos, &controlObj->pos, &temp);
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_LEFT]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = { -1.0f, 0.0f, 0.0f, 0.0f };
				vector_scale(&temp, velocity);
				vector_add(&controlObj->pos, &controlObj->pos, &temp);
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_DOWN]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = { 0.0f, 0.0f, -1.0f, 0.0f };
				vector_scale(&temp, velocity);
				vector_add(&controlObj->pos, &controlObj->pos, &temp);
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_RIGHT]) 
			{
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = { 1.0f, 0.0f, 0.0f, 0.0f };
				vector_scale(&temp, velocity);
				vector_add(&controlObj->pos, &controlObj->pos, &temp);
				controlObj->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_SPACE]) 
			{
				if (kbhit == 0)
                {
					kbhit = 1;
					if (++indicator >= 3) indicator = 0;
					device.render_state = states[indicator];
				}
			}
			else kbhit = 0;

			update_scene(deltaTime);
			render_scene(renderer, &device, 0, 0);
        }
		free_scene();
    }
	sdl_close();
	return 0;
}

