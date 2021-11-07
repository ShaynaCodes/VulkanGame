#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"


void player_think(Entity* self);
void player_update(Entity* self);
int p_health;
Entity* player_new(Vector3D position)
{
    Entity* ent = NULL;

    ent = gf3d_entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

   // ent->model = gf3d_model_load("dino");
    ent->think = player_think;
    ent->update = player_update;
    ent->radius = 10;
    ent->turn = 1;
    ent->complete = 1;
    ent->name = 1;
    ent->pickup = 0;
    ent->health = 100;
    ent->attack = 10;
    ent->attack2 = 100;
    ent->mspeed = 0;
    ent->lengendary = 0;
    vector3d_copy(ent->position, position);
    ent->rotation.x = -M_PI;
    return ent;
}


void player_think(Entity* self)
{
    Vector3D forward;
    Vector3D right;
    Vector3D up;
    const Uint8* keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward, 0.1 + self->mspeed);
    vector3d_set_magnitude(&right, 0.1 + self->mspeed);
    vector3d_set_magnitude(&up, 0.1 + self->mspeed);

    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position, self->position, -right); //up

        //slog("moved up");
    }
    if (keys[SDL_SCANCODE_A])
    {
        vector3d_add(self->position, self->position, right); //down
       // slog("moved down");
    }
    if (keys[SDL_SCANCODE_W])
    {
        vector3d_add(self->position, self->position, forward); //right
       // slog("moved right");
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position, self->position, -forward ); //left
        //slog("moved left");
    }
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.10 + self->mspeed;
    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10 + self->mspeed;

    if (keys[SDL_SCANCODE_UP])self->rotation.x -= 0.0010;
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x += 0.0010;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0010 ;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0010 ;

    if (self->start == 1)
    {

        if (self->target != NULL)
        {
            if (self->target->name == 2)// interaction with trainers
            {
                if (self->turn == 1)
                {

                    if (keys[SDL_SCANCODE_UP])//attack1
                    {
                        p_health = self->health;
                        self->target->health -= self->attack;
                        slog("You hit trainer");
                        self->turn = 0;
                       // self->complete = 1;
                        self->target->turn = 1;
                      //  self->target->complete = 0;
                        
                        if (self->health <= 0)
                        {
                            slog("you lost");

                            self->dead = 1;
                        }
                    }
                    if (self->lengendary >= 1) //lengendary attack if you have a lengendary pickup
                    {
                        if (keys[SDL_SCANCODE_DOWN])//attack2
                        {
                            p_health = self->health;
                            self->target->health -= self->attack2;
                            self->turn = 0;
                          //  self->complete = 1;
                            self->target->turn = 1;
                        //    self->target->complete = 0;
                        }
                        if (self->health <= 0)
                        {
                            slog("you lost");

                            self->dead = 1;
                        }
                    }
                }
            }
            if (self->target->name == 3)// interaction with trainer2
            {
                if (self->turn == 1)
                {
                    if (keys[SDL_SCANCODE_UP])
                    {
                        self->turn = 0;
                      //  self->complete = 1;
                        self->target->turn = 1;
                     //   self->target->complete = 0;
                    }
                    if (keys[SDL_SCANCODE_LEFT])
                    {
                        p_health = self->health;
                        self->target->health -= self->attack2;
                        slog("correct");
                        self->turn = 0;
                      //  self->complete = 1;
                        self->target->turn = 1;
                       // self->target->complete = 0;
                    }
                    if (keys[SDL_SCANCODE_DOWN])
                    {
                        slog("You LOST");
                        self->health = 0;
                        if (self->health <= 0)
                        {
                            slog("you lost");

                            self->dead = 1;
                        }
                    }

                }
            }
            if (self->target->name == 4)// interaction with pick ups
            {
                if (self->turn == 1)
                {

                    if (keys[SDL_SCANCODE_UP])//collect
                    {
                        p_health = self->health;
                        self->target->health -= self->attack;
                        self->turn = 0;
                        self->complete = 1;
                        self->target->turn = 1;
                        self->target->complete = 0;
                        slog("you collected a pickup");

                    }
                }
            }
            if (self->target->dead == 1)
            {
                //switch target to another monster
                self->turn = 1;
                self->complete = 0;
                self->target->turn = 0;
                self->target->complete = 1;
            }
            if (self->dead == 1)
            {
               //end game
              //  gf3d_entity_free(self);
            }
        }
    }
}


void player_update(Entity* self)
{
     if (!self)return;
    gf3d_camera_set_position(self->position);
    gf3d_camera_set_rotation(self->rotation);
 
}
