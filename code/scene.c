#include "scene.h"
#include<stdlib.h>


vertex_t ground_mesh[6] = {
    // pos						  //texcoord	 //color					 //normal
    {{-0.5f, 0.0f, -0.5f, 1.0f}, {0.0f,  8.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}},
    {{-0.5f, 0.0f,  0.5f, 1.0f}, {0.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f}, {8.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f}, {8.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}},
    {{0.5f,  0.0f, -0.5f, 1.0f}, {8.0f,  8.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}},
    {{-0.5f, 0.0f, -0.5f, 1.0f}, {0.0f,  8.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 0.0f}}
};

vertex_t box_mesh[36] = {
    // Positions                  // texcoord   //color						// normal
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  0.0f},{ 1.0f, 0.2f, 0.2f, 1.0f }, { 0.0f,  0.0f,-1.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 1.0f, 0.2f, 0.2f, 1.0f }, { 0.0f,  0.0f,-1.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f}, {1.0f,  1.0f}, { 1.0f, 0.2f, 0.2f, 1.0f }, {0.0f,  0.0f,-1.0f ,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f}, { 1.0f,  1.0f},{ 1.0f, 0.2f, 0.2f, 1.0f }, {0.0f,  0.0f,-1.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f, 1.0f}, {1.0f,  0.0f}, { 1.0f, 0.2f, 0.2f, 1.0f }, {0.0f,  0.0f,-1.0f ,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  0.0f},{ 1.0f, 0.2f, 0.2f, 1.0f }, { 0.0f,  0.0f,-1.0f,0.0f}},
    
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 1.0f, 0.2f, 1.0f }, { 0.0f,  0.0f, 1.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f, 1.0f},{ 1.0f,  0.0f}, { 0.2f, 1.0f, 0.2f, 1.0f }, {0.0f,  0.0f,  1.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},{ 1.0f,  1.0f}, { 0.2f, 1.0f, 0.2f, 1.0f },  {0.0f,  0.0f,  1.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},{ 1.0f,  1.0f}, { 0.2f, 1.0f, 0.2f, 1.0f },  {0.0f,  0.0f,  1.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 1.0f, 0.2f, 1.0f }, { 0.0f,  0.0f,  1.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 1.0f, 0.2f, 1.0f },  { 0.0f,  0.0f,  1.0f,0.0f}},
    
    {{-0.5f,  0.5f,  0.5f, 1.0f}, { 1.0f,  0.0f},{ 0.2f, 0.2f, 1.0f, 1.0f},  {-1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},{ 1.0f,  1.0f},{ 0.2f, 0.2f, 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 0.2f, 1.0f, 1.0f },  { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f, 1.0f},{ 0.0f,  1.0f},{ 0.2f, 0.2f, 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f, 1.0f},{ 0.0f,  0.0f},{ 0.2f, 0.2f, 1.0f, 1.0f},  { -1.0f,  0.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f,1.0f},{ 1.0f,  0.0f},{ 0.2f, 0.2f, 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f,0.0f}},
    
    {{0.5f,  0.5f,  0.5f,1.0f}, { 1.0f,  0.0f}, { 1.0f, 0.2f, 1.0f, 1.0f },  {1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f},{ 0.0f,  0.0f}, { 1.0f, 0.2f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f}, { 1.0f, 0.2f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f}, { 1.0f, 0.2f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f,1.0f},{ 1.0f,  1.0f}, { 1.0f, 0.2f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f,1.0f},{ 1.0f,  0.0f}, { 1.0f, 0.2f, 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f,0.0f}},
    
    {{-0.5f, -0.5f, -0.5f,1.0f},{  0.0f,  1.0f},{ 1.0f, 1.0f, 0.2f, 1.0f },  {  0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f, -0.5f,1.0f}, { 1.0f,  1.0f},{ 1.0f, 1.0f, 0.2f, 1.0f },  { 0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f}, { 1.0f,  0.0f}, { 1.0f, 1.0f, 0.2f, 1.0f }, { 0.0f, -1.0f,  0.0f,0.0f}},
    {{0.5f, -0.5f,  0.5f,1.0f}, { 1.0f,  0.0f},{ 1.0f, 1.0f, 0.2f, 1.0f },  { 0.0f, -1.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f,  0.5f,1.0f},{ 0.0f,  0.0f},{ 1.0f, 1.0f, 0.2f, 1.0f }, {  0.0f, -1.0f,  0.0f,0.0f}},
    {{-0.5f, -0.5f, -0.5f,1.0f},{ 0.0f,  1.0f},{ 1.0f, 1.0f, 0.2f, 1.0f },  {  0.0f, -1.0f,  0.0f,0.0f}},
    
    {{-0.5f,  0.5f, -0.5f, 1.0f}, {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f,  0.5f, 1.0f},  {0.0f,  0.0f},{ 0.2f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},  {1.0f,  0.0f},{ 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f,  0.5f, 1.0f},  {1.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.5f, -0.5f, 1.0f},  {1.0f,  1.0f},{ 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.5f, -0.5f, 1.0f},  {0.0f,  1.0f},{ 0.2f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f,  0.0f,0.0f}}
};

uint* framebuffer;
float* zbuffer;
float* shadowbuffer;
camera_t* main_camera;
object_t* ground;
object_t* g_box,*g_box1;
vertex_t* mesh_man;
ulong mesh_num_man;
int* material_ids_man;
ulong material_ids_num_man;


void init_texture()
{
	int width = 256, height = 256;
	texture_t* texture = &textures[texture_count++];
	uint* bits = (uint*)malloc(sizeof(uint)* width * height);
	int i, j;
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
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
	generate_mipmaps(texture, 1.01f);
	make_texture_by_png("mabu", true);
	make_texture_by_png("dimian", true);
}

void free_textures()
{
	for (int i = 0; i < texture_count; i++)
	{
		texture_t *texture = &textures[i];
		for (uint j = 0; j < texture->datas_len; j++)
		{
			uint *data = texture->datas[j];
			free(data);
		}
		free(texture->datas);
		texture->datas = NULL;
	}
}

void init_materials()
{
	materials[material_cnt++] = (material_t) { NULL, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, 32.0f, 1.0f, 1.0f, 1, 1, NULL, -1, NULL, 2, NULL, -1, NULL, -1, NULL, -1, NULL, -1, NULL, -1 };
	make_mesh_and_material_by_obj(&mesh_man, &mesh_num_man, &material_ids_man, &material_ids_num_man, "nanosuit");
}

void free_materials()
{
	for (int i = 0; i < material_cnt; i++)
	{
		free_material(&materials[i]);
	}
}

void init_buffers(device_t *device)
{
	framebuffer = (uint*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint));
	zbuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));
	shadowbuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));
	pshadowbuffer = shadowbuffer;

	device_set_framebuffer(device, framebuffer);
	device_set_zbuffer(device, zbuffer);
	device_set_shadowbuffer(device, shadowbuffer);
	device_set_background(device, 0x55555555);
	device_set_camera(device, main_camera);
	transform_update(&(device->transform));
}

void free_buffers()
{
	free(framebuffer);
	free(zbuffer);
	free(shadowbuffer);
}

void render_scene(SDL_Renderer* renderer, device_t *device,float yaw, float pitch)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	device_clear(device);
	if (main_camera->dirty) camera_init_by_euler(main_camera, yaw, pitch);

	for (int i = 0; i < camera_count; i++)
	{
		camera_t *camera = &cameras[i];
		if (camera->main)
		{
			device->cull = 1;
			device_set_framebuffer(device, framebuffer);
			device_set_zbuffer(device, zbuffer);
			device_set_shadowbuffer(device, NULL);
		}
		else
		{
			device->cull = 2;
			device_set_framebuffer(device, NULL);
			device_set_zbuffer(device, NULL);
			device_set_shadowbuffer(device, shadowbuffer);
		}
		if (camera->dirty)
		{
			camera_update(camera);
			camera->dirty = false;
		}
		device_set_camera(device, camera);
		transform_update(&device->transform);
		draw_object(device, objects, object_count);
	}

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			uint color = framebuffer[y * SCREEN_WIDTH + x];
			SDL_SetRenderDrawColor(renderer, (0xff << 16 & color) >> 16, (0xff << 8 & color) >> 8, 0xff & color, (0xff << 24 & color) >> 24);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

void draw_object(device_t *device, object_t* objects, int obj_cnt)
{
	for (int i = 0; i < obj_cnt; i++)
	{
		object_t *object = &objects[i];
		if (object->dirty)
		{
			matrix_set_rotate_translate_scale(&object->matrix, &object->axis, object->theta, &object->pos, &object->scale);
			object->dirty = false;
		}
		device->transform.model = object->matrix;
		transform_update(&device->transform);
        vertex_t *mesh = object->mesh;
        
        for (uint j = 0; j < object->mesh_num; j += 3)
        {
            if (object->material_ids == NULL)
                device->material = materials[0];
            else
                device->material = materials[object->material_ids[j / 3]];
            clip_polys(device, &mesh[i], &mesh[j + 1], &mesh[j + 2], false);
        }
	}
}

void init_light()
{
	dirLight = (dirlight_t) { {0.0f, -1.0f, 1.0f, 0.0f}, { 0.3f, 0.3f, 0.3f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f }, true };
	if (dirLight.shadow == true)
	{	 //shadow camera
		camera_t *camera = &cameras[camera_count];
		camera->pos = (vector_t) { 0.0f, 3.0f, -3.0f, 1.0f };
		camera->front = dirLight.dir;
		camera->worldup = (vector_t) { 0.0f, 1.0f, 0.0f, 0.0f };
		camera->fovy = 3.1415926 * 0.5f;
		camera->zn = 0.1f;
		camera->zf = 15.0f;
		camera->width = SCREEN_WIDTH;
		camera->height = SCREEN_HEIGHT;
		camera->aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
		camera->projection = orthographic;

		camera->left = -3.0f;
		camera->right = 3.0f;
		camera->bottom = -3.0f;
		camera->top = 3.0f;
		camera->dirty = true;
		camera_init_projection(camera);
		camera_count++;
	}

	pointLights[pointlight_cnt++] = (pointlight_t) { {0.0f, 6.0f, -1.0f, 1.0f}, 1.0f, 0.09f, 0.032f, { 0.6f, 0.6f, 0.6f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.7f, 0.7f, 0.7f, 1.0f }, false };
	pointLights[pointlight_cnt++] = (pointlight_t) { {0.0f, 6.0f, 2.0f, 1.0f}, 1.0f, 0.09f, 0.032f, { 0.6f, 0.6f, 0.6f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.6f, 0.6f, 0.6f, 1.0f }, false };
}

void init_maincamera()
{
    main_camera = &cameras[camera_count];
    main_camera->main = true;
    main_camera->pos = (vector_t){0.0f, 2.0f, -2.5f, 1.0f};
    main_camera->front = (vector_t){0.0f, 0.0f, 1.0f, 0.0f};
    main_camera->worldup = (vector_t){0.0f, 1.0f, 0.0f, 0.0f};
    main_camera->fovy = 3.1415926 * 0.5f;
    main_camera->zn = 0.1f;
    main_camera->zf = 500.0f;
    main_camera->width = SCREEN_WIDTH;
    main_camera->height = SCREEN_HEIGHT;
    main_camera->aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    main_camera->projection = perspective;
    main_camera->left = -1.0f;
    main_camera->right = 1.0f;
    main_camera->bottom = -1.0f;
    main_camera->top = 1.0f;
    camera_init_projection(main_camera);
    main_camera->dirty = true;
    camera_count++;
}

void init_groud()
{
    ground = &objects[object_count++];
    ground->pos = (point_t){0, 0, 0, 1};
    ground->scale = (vector_t){20, 1, 20, 0};
    ground->axis = (vector_t){0, 0, 0, 1};
    ground->theta = 0.0f;
    ground->mesh = ground_mesh;
    ground->mesh_num = 6;
    ground->material_ids = NULL;
    ground->texture_id = 1;
    ground->shadow = false;
    ground->dirty = true;
}

void init_boxs()
{
    g_box = &objects[object_count++];
    g_box->pos = (point_t){-1, 0, 0, 1};
    g_box->scale = (vector_t){0.1, 0.1, 0.1, 0};
    g_box->axis = (vector_t){0, 1, 0, 1};
    g_box->theta = 0.0f;
    g_box->mesh = mesh_man;
    g_box->mesh_num = mesh_num_man;
    g_box->material_ids = material_ids_man;
    g_box->texture_id = 1;
    g_box->shadow = true;
    g_box->dirty = true;
    
    g_box1 = &objects[object_count++];
    g_box1->pos = (point_t){0, 2, -1, 1};
    g_box1->scale = (vector_t){0.5, 0.5, 0.5, 0};
    g_box1->axis = (vector_t){1, 0, 1, 1};
    g_box1->theta = 0.0f;
    g_box1->mesh = box_mesh;
    g_box1->mesh_num = 36;
    g_box1->material_ids = NULL;
    g_box1->texture_id = 0;
    g_box1->shadow = false;
    g_box1->dirty = true;
}

void free_scene()
{
    free(mesh_man);
    free(material_ids_man);
    free_materials();
    free_textures();
	free_buffers();
}
