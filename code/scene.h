#ifndef scene_h
#define scene_h

#include "engine.h"
#include "utils.h"
#include <stdlib.h>

extern vertex_t ground_mesh[6];

extern vertex_t box_mesh[36];

void init_texture(void);

void free_textures(void);

void free_materails(void);

void draw_object(device_t *device, object_t* objects, int obj_cnt);


#endif /* scene_h */
