#ifndef __scene__
#define __scene__

#include "engine.h"
#include "utils.h"
#include <stdlib.h>

extern vertex_t ground_mesh[6];
extern vertex_t box_mesh[36];
extern camera_t *main_camera;
extern object_t* ground;
extern object_t* g_box,*g_box1;
extern vertex_t* mesh_nan;
extern ulong mesh_num_nan;
extern int* material_ids_nan;
extern ulong material_ids_num_nan;


void init_texture(void);
void free_textures(void);
void init_materials(void);
void free_materials(void);
void draw_object(device_t *device, object_t* objects, int obj_cnt);
void draw_light(void);
void init_maincamera(void);
void draw_groud(void);
void draw_boxs(void);
void free_scene(void);


#endif /* __scene__ */
