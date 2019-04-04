//
//  utils.h
//  lgEngine
//
//  Created by penghuailiang on 2019/04/04
//
//
#ifndef utils_h
#define utils_h

#include "tiny3D.h"

const char* getFilePath(const char* name, const char* type);
int generate_mipmaps(texture_t *texture, float gamma);
//int make_mesh_and_material_by_obj(vertex_t **mesh, unsigned long *mesh_num, int **material_ids, unsigned long *material_ids_num, const char *name);
int make_texture_by_png(const char *name, bool mipmap);

#endif /* utils_h */
