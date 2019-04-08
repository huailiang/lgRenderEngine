#ifndef __scene__
#define __scene__

#include "engine.h"
#include "utils.h"
#include "SDL_render.h"
#include <stdlib.h>

extern uint* framebuffer;
extern float* zbuffer;
extern float* shadowbuffer;
extern camera_t *main_camera;
extern object_t* ground;
extern object_t* g_box,*g_box1;
extern vertex_t* mesh_man;
extern ulong mesh_num_man;
extern int* material_ids_man;
extern ulong material_ids_num_man;


void init_texture(void);
void free_textures(void);
void init_materials(void);
void free_materials(void);
void init_buffers(device_t *device);
void free_buffers(void);
void render_scene(SDL_Renderer* renderer, device_t *device, float yaw, float pitch);
void draw_object(device_t *device, object_t* objects, int obj_cnt);
void draw_light(void);
void init_maincamera(void);
void draw_groud(void);
void draw_boxs(void);
void free_scene(void);


#endif /* __scene__ */
