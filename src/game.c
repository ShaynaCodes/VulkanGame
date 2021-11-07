#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"

#include "entity.h"
#include "ditto.h"
#include "player.h"
#include "world.h"
#include "pickup.h"
#include "trainer.h"

int main(int argc, char* argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 0;
    const Uint8* keys;
    Entity* fly;
    Entity* speed;
    Entity* legend;
    Entity* heal;
    Entity* radius;
    Entity* trainer1;
    Entity* trainer2;
    Entity* trainer3;
    Entity* trainer4;
    Entity* trainer5;
    Entity* player;
    World* w;


    for (a = 1; a < argc; a++)
    {
        if (strcmp(argv[a], "-disable_validate") == 0)
        {
            validate = 0;
        }
    }

    init_logger("gf3d.log");
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51, 0.75, 1, 1),//background color
        0,                      //fullscreen
        validate                //validation
    );
    slog_sync();

    entity_system_init(1024);

    w = world_load("config/world.json");

    for (a = 0; a < 1; a++) {trainer1= trainer1_spawn(vector3d( 19, 0, 10)); trainer2 =trainer1_spawn(vector3d(70, -40, 10)); trainer3=trainer1_spawn(vector3d(-70, 20, 10)); }//trainer 1 spawn
    for (a = 0; a < 2; a++) {trainer4= trainer2_spawn(vector3d( -60, -70, 10)); trainer5= trainer2_spawn(vector3d(70, -70, 10));}//trainer 2 spawn
   
    for (a = 0; a < 1; a++) {speed =speed_spawn(vector3d(0, -50, 10));}  //speed pick up BLUE
    for (a = 0; a < 1; a++) { legend= legendary_spawn(vector3d(10 - 50, 80, 10));} //legendary pick up YELLOW
    for (a = 0; a < 1; a++) {heal= heal_spawn(vector3d(80 , 70, 10)); } // heal pick up HEAL
    for (a = 0; a < 1; a++) { radius=radius_spawn(vector3d(-50, -70, 10)); } // radius pick up RED
  
    // main game loop
    slog_sync();
    gf3d_camera_set_scale(vector3d(10, 10, 10));

    slog("gf3d main loop begin");
   player =player_new(vector3d(0, 100, 10));

   if (player->target == NULL)
   {
       player->target = trainer1, trainer2, trainer3, trainer4, trainer5,speed, legend,heal,radius;
       trainer1->target = player;
       trainer2->target = player;
       trainer3->target = player;
       trainer4->target = player;
       trainer5->target = player;
       speed->target = player;
       legend->target = player;
       heal->target = player;
       radius->target = player;

   }
    while (!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        entity_think_all();
        entity_update_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

           world_draw(w);
        entity_draw_all();

        gf3d_vgraphics_render_end();

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition

    }

      world_delete(w);

    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}