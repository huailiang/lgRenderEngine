#ifndef __scene__
#define __scene__

#include "engine.h"
#include "utils.h"
#include "SDL_render.h"
#include <stdlib.h>

extern camera_t *main_camera;
extern object_t* g_man,*g_box;

void update_scene(float delta);
void render_scene(SDL_Renderer* renderer, device_t *device, float yaw, float pitch);
void draw_object(device_t *device, object_t* objects, int obj_cnt);
void init_scene(device_t* device);
void free_scene(void);


#endif /* __scene__ */
