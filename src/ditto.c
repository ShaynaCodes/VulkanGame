#include "simple_logger.h"
#include "ditto.h"


void ditto_think(Entity* self);

Entity* ditto_new(Vector3D position)
{
    Entity* ent = NULL;

    ent = gf3d_entity_new();
    if (!ent)
    {
        slog("There is no ditto");
        return NULL;
    }

    ent->model = gf3d_model_load("dino");
    ent->think = ditto_think;
    vector3d_copy(ent->position, position);
    return ent;
}


void ditto_think(Entity* self)
{
    if (!self)return;
        self->rotation.x += -0.002;
}