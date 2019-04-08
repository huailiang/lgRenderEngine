#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "engine.h"
#include "scene.h"
#include "common.h"

int screen_keys[KEY_CNT];
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
		xWindow = SDL_CreateWindow("Liang Cross-platform Software Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	printf("start engine %lu \n", sizeof(SDL_Event));
    if (sdl_init())
	{
		bool quit = false;
		device_t device;
		device_init(&device);
        
        int kbhit = 0;
        int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
        int indicator = 0;

		float c_yaw = 0.0f;
		float c_pitch = 0.0f;
		float c_movementspeed = 2.0f;
		float c_mouse_sensitivity = 0.7f;
		float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
		bool firstMouse = true;
		memset(screen_keys, 0, sizeof(int) * KEY_CNT);

        init_texture();
		init_materials();
        draw_light();
        init_maincamera();
        draw_groud();
        draw_boxs();
		init_buffers(&device);
        
        object_t *controlObj = g_box1;
		SDL_Event e;
		while (!quit)
		{
			Uint32 current = SDL_GetTicks();
			deltaTime = (current - lastFrame) * 0.001f;
			lastFrame = current;

            printf("fps:%f\n", 1.0f / deltaTime);

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
                    main_camera->dirty=true;
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
                vector_t temp = {0.0f, 1.0f, 0.0f, 0.0f};
                vector_scale(&temp, velocity);
                vector_add(&controlObj->pos, &controlObj->pos, &temp);
                controlObj->dirty = true;
            }
            if (screen_keys[SDL_SCANCODE_LEFT])
            {
                float velocity = c_movementspeed * deltaTime;
                vector_t temp = {-1.0f, 0.0f, 0.0f, 0.0f};
                vector_scale(&temp, velocity);
                vector_add(&controlObj->pos, &controlObj->pos, &temp);
                controlObj->dirty = true;
            }
            if (screen_keys[SDL_SCANCODE_DOWN])
            {
                float velocity = c_movementspeed * deltaTime;
                vector_t temp = {0.0f, -1.0f, 0.0f, 0.0f};
                vector_scale(&temp, velocity);
                vector_add(&controlObj->pos, &controlObj->pos, &temp);
                controlObj->dirty = true;
            }
            if (screen_keys[SDL_SCANCODE_RIGHT])
            {
                float velocity = c_movementspeed * deltaTime;
                vector_t temp = {1.0f, 0.0f, 0.0f, 0.0f};
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
        
            // box auto rotate
            g_box->theta -= 0.04f;
            g_box->dirty = true;
            g_box1->theta += 0.04f;
            g_box1->dirty = true;
            
			render_scene(xRenderer, &device, c_yaw, c_pitch);
		}
        free_scene();
		sdl_close();
	}
	return 0;

}
