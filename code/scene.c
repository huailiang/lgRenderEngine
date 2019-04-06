#include "scene.h"
#include<stdlib.h>


vertex_t ground_mesh[6] = {
    // Positions                  // Texture Coords  //color           //rhw // Normals
    {{-0.5f,  0.0f, -0.5f, 1.0f}, {0.0f,  8.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.0f,  0.5f, 1.0f},  {0.0f,  0.0f},{ 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f},  {8.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f,  0.5f, 1.0f},  {8.0f,  0.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{0.5f,  0.0f, -0.5f, 1.0f},  {8.0f,  8.0f}, { 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f,1.0f,  0.0f,0.0f}},
    {{-0.5f,  0.0f, -0.5f, 1.0f},  {0.0f,  8.0f},{ 0.2f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f,  0.0f,0.0f}}
};

vertex_t box_mesh[36] = {
    // Positions                  // Texture Coords  //color           //rhw // Normals
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

camera_t* main_camera;
object_t* ground;
object_t* g_box,*g_box1;
vertex_t* mesh_nan;
ulong mesh_num_nan;
int* material_ids_nan;
ulong material_ids_num_nan;


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

void free_materials()
{
	for (int i = 0; i < material_cnt; i++)
	{
		free_material(&materials[i]);
	}
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
		for (uint j = 0; j < object->mesh_num; i += 3)
		{
			if (object->material_ids == NULL)
				device->material = materials[0];
			else
				device->material = materials[object->material_ids[j / 3]];
			clip_polys(device, &mesh[i], &mesh[j + 1], &mesh[j + 2], false);
		}
	}
}

void draw_light()
{
    dirLight = (dirlight_t){{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, false};
    dirLight = (dirlight_t){{0.0f, -1.0f, 1.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {0.3f, 0.3f, 0.3f, 1.0f}, true};
    if(dirLight.shadow == true)
    {
        // 影子 摄像机
        camera_t *camera = &cameras[camera_count];
        camera->pos = (vector_t){0.0f, 3.0f, -3.0f, 1.0f};
        camera->front = dirLight.dir;
        camera->worldup = (vector_t){0.0f, 1.0f, 0.0f, 0.0f};
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
    
    pointLights[pointlight_cnt++] = (pointlight_t){{0.0f, 6.0f, -1.0f, 1.0f}, 1.0f, 0.09f, 0.032f, {0.6f, 0.6f, 0.6f, 1.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, false};
    pointLights[pointlight_cnt++] = (pointlight_t){{0.0f, 6.0f, 2.0f, 1.0f}, 1.0f, 0.09f, 0.032f, {0.6f, 0.6f, 0.6f, 1.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {0.6f, 0.6f, 0.6f, 1.0f}, false};
}

void init_main_camera()
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

void draw_groud()
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

void draw_boxs()
{
    g_box = &objects[object_count++];
    g_box->pos = (point_t){-1, 0, 0, 1};
    g_box->scale = (vector_t){0.1, 0.1, 0.1, 0};
    g_box->axis = (vector_t){0, 1, 0, 1};
    g_box->theta = 0.0f;
    g_box->mesh = mesh_nan;
    g_box->mesh_num = mesh_num_nan;
    g_box->material_ids = material_ids_nan;
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
    free(mesh_nan);
    free(material_ids_nan);
    free_materials();
    free_textures();
}
