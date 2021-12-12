#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"


void player_think(Entity* self);
void player_update(Entity* self);
int p_health;
int obj;
int up;
Entity* player_new(Vector3D position, int hp, int a1,int a2)
{
    Entity* ent = NULL;

    ent = gf3d_entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->think = player_think;
    ent->update = player_update;
    ent->radius = 10;
    ent->turn = 1;
    ent->complete = 1;
    ent->name = 1;
    ent->pickup = 0;
    ent->health = hp;
    ent->maxhealth = hp;
    ent->attack = a1;
    ent->attack2 = a2;
    ent->mspeed = .05;
    ent->lengendary = 0;
    ent->keys = 0;
    ent->Tkills = 0;
    ent->Bkills = 0;
    ent->objectives = obj;
    ent->fly = up;
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
    vector3d_set_magnitude(&forward, 0.01 + self->mspeed);
    vector3d_set_magnitude(&right, 0.01 + self->mspeed);
    vector3d_set_magnitude(&up, 0.01 + self->mspeed);

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
    //if(self->fly>= 1){
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.10 + self->mspeed;
    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10 + self->mspeed;
//}
    if (keys[SDL_SCANCODE_UP])self->rotation.x -= 0.0010;
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x += 0.0010;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0010 ;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0010 ;
  //  if (keys[SDL_SCANCODE_O])player_objectives(self);
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
                        if (self->target->health <= 0)
                        {
                           
                            self->Tkills++;
                            self->xp + 50;
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
                        if (self->target->health <= 0)
                        {

                            self->Tkills++;
                            self->xp + 50;
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
                        self->xp + 50;
                        self->Tkills++;
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
            if (self->target->name == 6)// interaction with pick ups
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
                        self->mspeed = .3;
                        slog("you collected a pickup");

                    }
                }
            }
            if (self->target->name == 15)// interaction with boss
            {
                if (self->turn == 1)
                {
                    if (keys[SDL_SCANCODE_UP])//attack1
                    {
                        p_health = self->health;
                      
                        self->target->health -= self->attack;
                        slog("You hit boss");
                        self->turn = 0;
                        // self->complete = 1;
                        self->target->turn = 1;
                        //  self->target->complete = 0;
                    }
                    if (keys[SDL_SCANCODE_DOWN])//attack2
                    {
                        p_health = self->health;
                        self->target->health -= self->attack2;
                        slog("You hit trainer");
                        self->turn = 0;
                        // self->complete = 1;
                        self->target->turn = 1;
                        //  self->target->complete = 0;
                    }
                    if (self->target->health <= 0)
                    {
                        slog("you beat the boss");
                        self->Bkills++;
                    }

                    }
            }
            if (self->target->name == 11)// interaction with fly
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
                        self->fly++;
                        slog("you collected a pickup");

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
            if (self->target->name == 9)// interaction with keys
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
                        self->keys++;
                        slog("you collected a key");

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
                self->Tkills++;
            }
            if (self->xp >= 50)
            {
                self->lvl++;
                self->attack += 20;
                self->attack2 += 20;
                self->maxhealth += 15;
                slog("leveled up");
                //self->xp = 0;
            } 
            if (self->keys >= 3)
            {
                self->objectives++;
               //  obj =self->objectives ;
                slog("You have completed an objective: Collected all keys");
                self->lvl++;
                self->attack += 20;
                self->attack2 += 20;
                self->maxhealth += 15;
                slog("leveled up");
                self->xp = 0;
                self->keys = 0;
            }
            if (self->Bkills >= 1)
            {
                self->objectives++;
               // obj = self->objectives;
                slog("You have completed an objective: Defeated Boss ");
                self->lvl++;
                self->attack += 20;
                self->attack2 += 20;
                self->maxhealth += 15;
                slog("leveled up");
                self->xp = 0;
                self->Bkills = 0;
            }
            if (self->Tkills >= 5)
            {
                self->objectives++;
               // obj = self->objectives;
                slog("You have completed an objective: Defeated all Trainers");
                self->lvl++;
                self->attack += 20;
                self->attack2 += 20;
                self->maxhealth += 15;
                slog("leveled up");
                self->xp = 0;
                self->Tkills = 0;
            }
            if (self->objectives >= 3)
            {
                slog("you beat the game by completing all objectives");
               

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
void player_objectives(Entity* self)
{
    //slog("Objectives Completed: " + ToString(obj));
}