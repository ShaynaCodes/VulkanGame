#include "simple_logger.h"
#include "player.h"
#include "pickup.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

void legendary_think(Entity *self);
void legendary_update(Entity* self);
void heal_think(Entity* self);
void radius_think(Entity* self);
void fly_think(Entity* self);
void speed_think(Entity* self);


//fly_spawn(Vector3D position);


Entity *legendary_spawn(Vector3D position)
{
	Entity* ent;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for legendary");
		return NULL;
	}
	ent->radius = 10;
	ent->health = 5;
	ent->think = legendary_think;
	ent->update = legendary_update;
	ent->rotation.x = -M_PI;
	ent->model = gf3d_model_load("dino");
	ent->name = 4;
	ent->attack = 0;
	return ent;
}

void legendary_think(Entity* self) //collision for pickup items
{
	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			self->turn = 0;
			self->complete = 1;

			self->target->turn = 1; 
			if (self->health <= 0)
			{
				slog("gain lengendary attack");
				self->dead = 1;
				self->target->lengendary++;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}
void legendary_update(Entity* self)
{

}
Entity *heal_spawn(Vector3D position)
{
	Entity* ent;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for heal");
		return NULL;
	}
	ent->radius = 10;
	ent->health = 5;
	ent->think = heal_think;
	ent->rotation.x = -M_PI;
	ent->model = gf3d_model_load("dino");
	ent->name = 4;
	ent->attack = 0;
	return ent;
}
void heal_think(Entity* self) //collision for heal items
{
	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			self->turn = 0;
			self->complete = 1;

			self->target->turn = 1;
			if (self->health <= 0)
			{
				slog("gain heal");
				self->dead = 1;
				self->target->health+ 50;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}
Entity* radius_spawn(Vector3D position)
{
	Entity* ent;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for radius");
		return NULL;
	}
	ent->radius = 10;
	ent->health = 5;
	ent->think = radius_think;
	ent->rotation.x = -M_PI;
	ent->model = gf3d_model_load("dino");
	ent->name = 4;
	ent->attack = 0;
	return ent;
}
void radius_think(Entity* self) //collision for heal items
{
	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			self->turn = 0;
			self->complete = 1;

			self->target->turn = 1;
			if (self->health <= 0)
			{
				slog("gain wider radius");
				self->dead = 1;
				self->target->radius + 50;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}
Entity* speed_spawn(Vector3D position)
{
	Entity* ent;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for speed");
		return NULL;
	}
	ent->radius = 10;
	ent->health = 5;
	ent->think = speed_think;
	ent->rotation.x = -M_PI;
	ent->model = gf3d_model_load("dino");
	ent->name = 4;
	ent->attack = 0;
	return ent;
}
void speed_think(Entity* self) //collision for speed items
{
	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			self->turn = 0;
			self->complete = 1;

			self->target->turn = 1;
			if (self->health <= 0)
			{
				slog("gain speed up");
				self->dead = 1;
				self->target->mspeed + 1;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}