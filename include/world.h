#ifndef __WORLD_H__
#define __WORLD_H__

#include "entity.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"

// draw, add entity, load, delete, run updates
typedef struct {
	Model *worldModel;

}World;

void world_draw(World* world);
World* world_load(char* filename);






#endif
