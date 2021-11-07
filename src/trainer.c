#include "simple_logger.h"
#include "player.h"
#include "trainer.h"
#include "gfc_vector.h"

#include "gf3d_camera.h"
#include "gfc_matrix.h"

void trainer1_think(Entity *self);
void trainer1_update(Entity* self);
void trainer2_update(Entity* self);
void trainer2_think(Entity *self);




Entity *trainer1_spawn(Vector3D position)
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
	ent->think = trainer1_think;
	ent->update = trainer1_update;
	ent->rotation.x = -M_PI;
	vector3d_copy(ent->position, position);
	ent->model = gf3d_model_load("trainer"); // pink dino is trainer 1
	ent->name = 2;
	ent->attack = 10;
	return ent;
}

void trainer1_think(Entity *self) //collision for trainer battle
{
	int health = self->target->health;
	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			self->turn = 0;
			self->complete = 1;
			slog("Trainer hit ditto");
			self->target->turn = 1;
			self->target->complete = 0;
			if (self->health <= 0)
			{
				slog("You beat trainer" );
				self->dead = 1;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}

void trainer1_update(Entity *self)
{
		if (!self)return;
		gf3d_camera_set_position(self->position);
		gf3d_camera_set_rotation(self->rotation);
}
Entity *trainer2_spawn(Vector3D position) 
{
	Entity* ent;
	ent = gf3d_entity_new();
	if (!ent)
	{
		slog("failed to create entity for trainer2");
		return NULL;
	}
	ent->radius =10;
	ent->health = 100;
	ent->think = trainer2_think;
	ent->update = trainer2_update;
	ent->rotation.x = -M_PI;
	ent->model = gf3d_model_load("trainer2"); //blue dino is trainer 2
	vector3d_copy(ent->position, position);
	ent->name = 3;
	ent->attack = 100;
	return ent;
}
void trainer2_think(Entity *self) //collision for quiz game
{

	if (self->target != NULL)
	{
		if (self->turn == 1)
		{
			
			slog("What was ash's first pokemon?");
			slog("LEFT = Pikachu,           DOWN = Pidgeotto");
			
			self->turn = 0;
			self->complete = 1;
			
			self->target->turn = 1;
			self->target->complete = 0;
		
		
		
			if (self->health <= 0)
			{
				slog("Beat Trainer");
				
				self->dead = 1;
			}

		}
		if (self->dead == 1)
		{
			//pickup disapears
			gf3d_entity_free(self);
		}
	}
}

void trainer2_update(Entity* self)
{
	if (!self)return;
	gf3d_camera_set_position(self->position);
	gf3d_camera_set_rotation(self->rotation);
}

