#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf3d_model.h"
typedef struct Entity_S
{
	Uint8		_inuse;
	Model		*model;
	Vector3D	position;
	Vector3D	velocity;
	Vector3D	acceleration;
	Vector3D	rotation;
	Vector3D	scale;
	//void (think*)(struct Entity_S* self);
	//void (update*)(struct Entity_S* self);
	float health;
	float maxhealth;


	float level;
	void* data;
}Entity;

void entity_system_init(Uint32 entity_max);
Entity *gf3d_entity_new();
void gf3d_entity_free(Entity* self);

//Entity *gf3d_entity_new();


#endif
