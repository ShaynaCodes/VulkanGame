#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf3d_model.h"
#include "gfc_types.h"
#include "gfc_types.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"
#include "simple_logger.h"


typedef enum
{
	ES_Idle = 0,
	ES_Dying = 1,
	ES_Dead = 2
}EntityState;
typedef struct Entity_S
{
	Uint8		_inuse;
	Model		*model;
	Matrix4		modelMat;
	Vector3D	position;
	Vector3D	velocity;
	Vector3D	acceleration;
	Vector3D	rotation;
	Vector3D	scale;
	EntityState state;
	int dead; 
	int objectives; // number of objectives
	int keys; // number of keys
	int Tkills; // number of trainer deafeated
	int Bkills; // number of boss kilss
	int name;
	int start;
	float mspeed;
	float health;
	int turn;
	int complete;
	int lengendary;
	float			radius;
	struct Entity_S* target;
	void (*think)(struct Entity_S* self);
	void (*update)(struct Entity_S* self);
	int attack;
	int attack2;
	int attack3;
	int legendary;
	float maxhealth;
	int pickup;
	int lvl;
	int fly;
	int xp;
	float level;
	void* data;
}Entity;

void entity_system_init(Uint32 entity_max);
Entity *gf3d_entity_new();
void gf3d_entity_free(Entity *self);
void entity_draw(Entity *self);
void entity_draw_all();
void entity_think(Entity *self);
void entity_think_all();
void entity_update_all();
void entity_manager_free();

//Entity *gf3d_entity_new();
int collision(Entity* self, Entity* ent);

#endif
