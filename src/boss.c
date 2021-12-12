#include "simple_logger.h"
#include "player.h"
#include "boss.h"
#include "gfc_vector.h"

#include "gf3d_camera.h"
#include "gfc_matrix.h"

void boss_think(Entity* self);
void boss_update(Entity* self);

Entity* boss_spawn(Vector3D position, int hp, int a1, int a2, int a3)
{
	Entity* ent = NULL;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for trainer1");
		return NULL;
	}
	ent->radius = 10;
	ent->health = 100;
	ent->think = boss_think;
	ent->update = boss_update;
	ent->rotation.x = -M_PI;
	vector3d_copy(ent->position, position);
	ent->model = gf3d_model_load("boss"); // pink dino is trainer 1
	ent->name = 15;
	ent->attack = 10;
	return ent;
}
void boss_think(Entity* self)
{
	if (self->target != NULL)
	{
		if (self->target != NULL)
		{
			if (self->turn == 1)
			{
				self->turn = 0;
				self->complete = 1;
				slog("Boss hit ditto");
				self->target->turn = 1;
				self->target->complete = 0;
				if (self->health <= 0)
				{
					slog("You beat boss");
					self->dead = 1;
					self->turn = 0;
					self->complete = 1;
				}

			}
			if (self->dead == 1)
			{
				//pickup disapears
				gf3d_entity_free(self);
				self->dead = 0;
			}
		}
	}
}

void boss_update(Entity* self)
{
	if (!self)return;
	gf3d_camera_set_position(self->position);
	gf3d_camera_set_rotation(self->rotation);
}