#include "entity.h"
#include "world.h"
#include <stdlib.h>
#include <string.h>
#include "simple_json.h"
#include "gfc_types.h"
#include "simple_logger.h"

// draw, add entity, load, delete, run updates
/*typedef struct {


}World;
*/

World* world_load(char* filename) {
	World* w = NULL;
	SJson *json, *wjson;
	const char *modelName = NULL;
	w = gfc_allocate_array(sizeof(World), 1);
	if (w == NULL)
	{
		slog("fail to allocate world");
		return NULL;
	}
	json = sj_load(filename);
	if (!json)
	{
		slog("fail to load world");
		free(w);
		return NULL;
	}
	wjson = sj_object_get_value(json, "world");
	if (!wjson)
	{
		slog("fail to find world object");
		free(w);
		sj_free(json);
		return NULL;
	}
	modelName = sj_object_get_value(wjson, "model");
	if (modelName)
	{
		w->worldModel = gf3d_model_load((char *)modelName);
	}
	else {
		slog("world data have no model");
	}

}
void world_draw(World* world)
{
	if (!world)return;
	if (!world->worldModel)return;
	gf3d_model_draw(world->worldModel, Uint32 bufferFrame, VkCommandBuffer commandBuffer);
}
void world_delete(World* world)
{
	if (!world)return;
	gf3d_model_free(world->worldModel);
	free(world);
}






