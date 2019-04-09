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

void free_materials() 
{
	for (int i = 0; i < material_cnt; i++) 
	{
		free_material(&materials[i]);
	}
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
			// 切换材质组
			if (object->material_ids == NULL)
				device->material = materials[0];
			else
				device->material = materials[object->material_ids[i / 3]];
			clip_polys(device, &mesh[i], &mesh[i + 1], &mesh[i + 2], false);
		}
	}
}

int screen_keys[512];	
float deltaTime = 0.0f;
Uint32 lastFrame = 0;

int main(int argc, char * argv[])
{
	bool sdl_ret = sdl_init();
	if (sdl_init())
	{
		bool quit = false;

		device_t device;
		device_init(&device);
		int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
		int indicator = 0;
		int kbhit = 0;

		init_texture();
		materials[material_cnt++] = (material_t) { NULL, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, 32.0f, 1.0f, 1.0f, 1, 1, NULL, -1, NULL, 2, NULL, -1, NULL, -1, NULL, -1, NULL, -1, NULL, -1 };

		vertex_t *mesh_nan;
		unsigned long mesh_num_nan;
		int *material_ids_nan;
		unsigned long material_ids_num_nan;
		make_mesh_and_material_by_obj(&mesh_nan, &mesh_num_nan, &material_ids_nan, &material_ids_num_nan, "nanosuit");

		// 缓存
		IUINT32 *framebuffer = (IUINT32*)malloc(REAL_WIDTH * REAL_HEIGHT * sizeof(IUINT32));
		float *zbuffer = (float*)malloc(REAL_HEIGHT * REAL_WIDTH * sizeof(float));
		float *shadowbuffer = (float*)malloc(REAL_HEIGHT * REAL_WIDTH * sizeof(float));
		pshadowbuffer = shadowbuffer;

		float c_yaw = 0.0f;
		float c_pitch = 0.0f;
		float c_movementspeed = 2.0f;
		float c_mouse_sensitivity = 0.7f;
		float c_lastX = SCREEN_WIDTH >> 1, c_lastY = SCREEN_HEIGHT >> 1;
		bool firstMouse = true;

		memset(screen_keys, 0, sizeof(int) * 512);

		dirLight = (dirlight_t) { {0.0f, 0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, false };
		dirLight = (dirlight_t) { {0.0f, -1.0f, 1.0f, 0.0f}, { 0.3f, 0.3f, 0.3f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f }, true };
		if (dirLight.shadow == true)
		{
			// 影子摄像机
			camera_t *camera = &cameras[camera_count];
			camera->pos = (vector_t) { 0.0f, 3.0f, -3.0f, 1.0f };
			camera->front = dirLight.dir;
			camera->worldup = (vector_t) { 0.0f, 1.0f, 0.0f, 0.0f };
			camera->fovy = 3.1415926 * 0.5f;
			camera->zn = 0.1f;
			camera->zf = 15.0f;
			camera->width = REAL_WIDTH;
			camera->height = REAL_HEIGHT;
			camera->aspect = (float)REAL_WIDTH / (float)REAL_HEIGHT;
			camera->projection = orthographic;

			camera->left = -3.0f;
			camera->right = 3.0f;
			camera->bottom = -3.0f;
			camera->top = 3.0f;
			camera->dirty = true;
			camera_init_projection(camera);
			camera_count++;
		}

		init_maincamera();
	

		device_set_framebuffer(&device, framebuffer);
		device_set_zbuffer(&device, zbuffer);
		device_set_shadowbuffer(&device, shadowbuffer);
		device_set_background(&device, 0x55555555);
		device_set_camera(&device, main_camera);
		transform_update(&device.transform);

		init_groud();

		// box
		object_t *box = &objects[object_count++];
		box->pos = (point_t) { -1, 0, 0, 1 };
		box->scale = (vector_t) { 0.1, 0.1, 0.1, 0 };
		box->axis = (vector_t) { 0, 1, 0, 1 };
		box->theta = 0.0f;
		box->mesh = mesh_nan;
		box->mesh_num = mesh_num_nan;
		box->material_ids = material_ids_nan;
		box->texture_id = 1;
		box->shadow = true;
		box->dirty = true;

		// box
		object_t *box1 = &objects[object_count++];
		box1->pos = (point_t) { 0, 2, -1, 1 };
		box1->scale = (vector_t) { 0.5, 0.5, 0.5, 0 };
		box1->axis = (vector_t) { 1, 0, 1, 1 };
		box1->theta = 0.0f;
		box1->mesh = box_mesh;
		box1->mesh_num = 36;
		box1->material_ids = NULL;
		box1->texture_id = 0;
		box1->shadow = false;
		box1->dirty = true;

		object_t *controlObj = box1;
		SDL_Event e;

		while (!quit)
		{
			Uint32 currentFrame = SDL_GetTicks();
			deltaTime = (currentFrame - lastFrame) * 1.0f / 1000;
			lastFrame = currentFrame;
			printf("fps: %04.2f\n", deltaTime < 1e-2 ? 100.0f : 1.0f / deltaTime);
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				//User presses a key
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

			if (screen_keys[SDL_SCANCODE_W]) {
				float velocity = c_movementspeed * deltaTime;
				vector_t temp = main_camera->front;
				vector_scale(&temp, velocity);
				vector_add(&main_camera->pos, &main_camera->pos, &temp);
				main_camera->dirty = true;
			}
			if (screen_keys[SDL_SCANCODE_S]) {

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
				if (kbhit == 0) {
					kbhit = 1;
					if (++indicator >= 3) indicator = 0;
					device.render_state = states[indicator];
				}
			}
			else kbhit = 0;

			box->theta -= 0.04f;
			box->dirty = true;
			box1->theta += 0.04f;
			box1->dirty = true;

			// Clear screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			// shadowbuffer在这里设置是为了清空buffer
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
					IUINT32 color = framebuffer[y * REAL_WIDTH + x];
					SDL_SetRenderDrawColor(renderer, (0xff << 16 & color) >> 16, (0xff << 8 & color) >> 8, 0xff & color, (0xff << 24 & color) >> 24);
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}

			SDL_RenderPresent(renderer);
		}
		free(mesh_nan);
		free(material_ids_nan);
		free_materials();
		free_textures();
		free(framebuffer);
		free(zbuffer);
		free(shadowbuffer);
	}
	sdl_close();
	return 0;
}

