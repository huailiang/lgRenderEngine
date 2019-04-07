#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _MSC_VER
#include<Windows.h>
#endif // _MSC_VER

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
	printf("start engine %lu \n", sizeof(SDL_Event));
    if (sdl_init())
	{
		bool quit = false;
		device_t device;
		device_init(&device);
        
        int kbhit = 0;
        int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
        int indicator = 0;

        init_texture();
        materials[material_cnt++] = (material_t){NULL, {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, 32.0f, 1.0f, 1.0f, 1, 1, NULL, -1, NULL, 2, NULL, -1, NULL, -1, NULL, -1, NULL, -1, NULL, -1};
        
        make_mesh_and_material_by_obj(&mesh_nan, &mesh_num_nan, &material_ids_nan, &material_ids_num_nan, "nanosuit");
        
        // 缓存
        uint *framebuffer = (uint*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint));
        float *zbuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));
        float *shadowbuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));
        pshadowbuffer = shadowbuffer;
        
        float c_yaw = 0.0f;
        float c_pitch = 0.0f;
        float c_movementspeed = 2.0f;
        float c_mouse_sensitivity = 0.7f;
        float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
        bool firstMouse = true;
        memset(screen_keys, 0, sizeof(int) * KEY_CNT);
        
        draw_light();
        init_maincamera();
        draw_groud();
        draw_boxs();

        device_set_framebuffer(&device, framebuffer);
        device_set_zbuffer(&device, zbuffer);
        device_set_shadowbuffer(&device, shadowbuffer);
        device_set_background(&device, 0x55555555);
        device_set_camera(&device, main_camera);
        transform_update(&device.transform);
        
        object_t *controlObj = g_box1;
        
		SDL_Event e;
		while (!quit)
		{
			Uint32 current = SDL_GetTicks();
			deltaTime = (current - lastFrame) * 0.001f;
			lastFrame = current;

#ifdef _MSC_VER
            printf("fps delta :%f %f\n", deltaTime, 1.0f / deltaTime);
			float wait = 1.0f / FPS;
			if (deltaTime < wait)
			{
				Sleep(1000.0f* (wait - deltaTime));
			}
#endif // #ifdef _MSC_VER

            while (SDL_PollEvent(&e) != 0)
            {
//                printf("checked key event: %d\n",e.type);
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
            
            // Clear screen
            SDL_SetRenderDrawColor(xRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(xRenderer);
            
            // shadowbuffer在这里设置是为了清空buffer
            device_set_shadowbuffer(&device, shadowbuffer);
            device_clear(&device);

            if(main_camera->dirty) camera_init_by_euler(main_camera, c_yaw, c_pitch);

            for(int i = 0; i < camera_count; i++)
            {
                camera_t *camera = &cameras[i];
                if(camera->main)
                {
                    device.cull = 1;
                    device_set_framebuffer(&device, framebuffer);
                    device_set_zbuffer(&device, zbuffer);
                    device_set_shadowbuffer(&device, NULL);
                }
                else
                {
                    device.cull = 2;
                    device_set_framebuffer(&device, NULL);
                    device_set_zbuffer(&device, NULL);
                    device_set_shadowbuffer(&device, shadowbuffer);
                }
                if(camera->dirty)
                {
                    camera_update(camera);
                    camera->dirty = false;
                }
                device_set_camera(&device, camera);
                transform_update(&device.transform);
                draw_object(&device, objects, object_count);
            }

            for(int y = 0; y < SCREEN_HEIGHT; y++)
            {
                for(int x = 0; x < SCREEN_WIDTH; x++)
                {
                    uint color = framebuffer[y * SCREEN_WIDTH + x];
                    SDL_SetRenderDrawColor(xRenderer, (0xff<<16 & color)>>16, (0xff<<8 & color)>>8, 0xff&color, (0xff<<24 & color)>>24);
//                    SDL_SetRenderDrawColor(xRenderer,x%100<=40?255:0,y%100<=70?255:0,0,SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawPoint(xRenderer, x, y);
                }
            }
            SDL_RenderPresent(xRenderer);
		}
        free_scene();
        free(framebuffer);
        free(zbuffer);
        free(shadowbuffer);
        
		sdl_close();
	}
	return 0;

}
