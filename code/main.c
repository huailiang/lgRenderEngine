#include "SDL.h"
#include "utils.h"
#include "engine.h"
#include <stdio.h>
#include "common.h"
#include "scene.h"

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
		window = SDL_CreateWindow("Liang Cross-platform Software Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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


void draw_object(device_t *device, object_t *objects, int obj_cnt) 
{
	for (int i = 0; i < obj_cnt; i++)
	{
		object_t *object = &objects[i];
		if (object->dirty == true) {
			matrix_set_rotate_translate_scale(&object->matrix, &object->axis, object->theta, &object->pos, &object->scale);
			object->dirty = false;
		}

		device->transform.model = object->matrix;
		transform_update(&device->transform);
		vertex_t *mesh = object->mesh;
		for (int i = 0; i < object->mesh_num; i += 3) 
		{
			if (object->material_ids == NULL)
				device->material = materials[0];
			else
				device->material = materials[object->material_ids[i / 3]];
			clip_polys(device, &mesh[i], &mesh[i + 1], &mesh[i + 2], false);
		}
	}
}

int screen_keys[KEY_CNT];
float deltaTime = 0.0f;
Uint32 lastFrame = 0;

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

		init_texture();
        init_materials();
		
        uint32 *framebuffer = (uint32*)malloc(REAL_WIDTH * REAL_HEIGHT * sizeof(uint32));
        float *zbuffer = (float*)malloc(REAL_HEIGHT * REAL_WIDTH * sizeof(float));
        float *shadowbuffer = (float*)malloc(REAL_HEIGHT * REAL_WIDTH * sizeof(float));
        pshadowbuffer = shadowbuffer;

		float c_yaw = 0.0f;
		float c_pitch = 0.0f;
		float c_movementspeed = 2.0f;
		float c_mouse_sensitivity = 0.7f;
		float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
		bool firstMouse = true;

		memset(screen_keys, 0, sizeof(int) * KEY_CNT);

        init_light();
		init_maincamera();
	
		device_set_framebuffer(&device, framebuffer);
		device_set_zbuffer(&device, zbuffer);
		device_set_shadowbuffer(&device, shadowbuffer);
		device_set_background(&device, 0x55555555);
		device_set_camera(&device, main_camera);
		transform_update(&device.transform);

		init_groud();
        init_boxs();
        
		object_t *controlObj = g_box1;
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
					if (firstMouse) {
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
				vector_t temp = { 0.0f, 1.0f, 0.0f, 0.0f };
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
				vector_t temp = { 0.0f, -1.0f, 0.0f, 0.0f };
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

			g_box->theta -= 0.04f;
			g_box->dirty = true;
			g_box1->theta += 0.04f;
			g_box1->dirty = true;
            
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            device_set_shadowbuffer(&device, shadowbuffer);
            device_clear(&device);

            if (main_camera->dirty) camera_init_by_euler(main_camera, 0/*c_yaw*/, 0/*c_pitch*/);

            for (int i = 0; i < camera_count; i++)
            {
                camera_t *camera = &cameras[i];
                if (camera->main == true)
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

                if (camera->dirty == true)
                {
                    camera_update(camera);
                    camera->dirty = false;
                }
                device_set_camera(&device, camera);
                transform_update(&device.transform);
                draw_object(&device, objects, object_count);
            }

            for (int y = 0; y < SCREEN_HEIGHT; y++)
            {
                for (int x = 0; x < SCREEN_WIDTH; x++)
                {
                    uint32 color = framebuffer[y * REAL_WIDTH + x];
                    SDL_SetRenderDrawColor(renderer, (0xff << 16 & color) >> 16, (0xff << 8 & color) >> 8, 0xff & color, (0xff << 24 & color) >> 24);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

            SDL_RenderPresent(renderer);
        }
        free_materials();
        free_textures();
    }
	sdl_close();
	return 0;
}

