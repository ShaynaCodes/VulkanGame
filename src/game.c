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
#include "sprite.h"
#include "gf3d_model.h"
#include "entity.h"
#include "gfc_audio.h"
#include "player.h"
#include "boss.h"
#include "world.h"
#include "simple_json.h"

int main(int argc, char* argv[])
{
    int done = 0;
    int done2 = 1;
    int done3 = 1;
    int a;
    Uint8 validate = 0;
    const Uint8* keys;
    Model* model = NULL;
    Sprite* mouse = NULL;
    int mousex, mousey;
    float mouseFrame = 0;
    World* w;
    Sprite* sprite;
    Sprite* sprite2;
    Mix_Music* music;
    int PlayerHP = 0;
    int PlayerA1 = 0;
    int PlayerA2 = 0;
    int BossHP = 0;
    int BossA1 = 0;
    int BossA2 = 0;
    int BossA3 = 0;
    int attack1;
    int attack2;
    int nhealth;
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
    Entity* boss;
    Entity* key;
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
   // model = gf3d_model_load_animated("dino_anim", 5,12);
    gfc_audio_init(256, 16, 4, 1, 1, 1);
    mouse = gf3d_sprite_load("images/pointer.png", 32, 32, 16);
    sprite = gf3d_sprite_load("images/gamemenu.png",1200,700,1000);
    sprite2 = gf3d_sprite_load("images/wing.png", 1200, 700, 1000);
    w = world_load("config/world.json");

    SJson* config = sj_load("config/player.json");
    SJson* config2 = sj_load("config/boss.json");

    if (!config)
    {
        slog("oh no");
    }
    else {
        slog("FILE FOUND");
        SJson* playerArray_config = sj_object_get_value(config, "Player");
        SJson* config_playerData;

        for (int x = 0; x < sj_array_get_count(playerArray_config); x++)
        {
            config_playerData = sj_array_get_nth(playerArray_config, x);
            sj_echo(config_playerData);

            SJson* Healthvalues = sj_object_get_value(config_playerData, "Health");
            sj_echo(Healthvalues);

            SJson* Attackvalues = sj_object_get_value(config_playerData, "Attack");
            sj_echo(Attackvalues);
            
            SJson* Attack2values = sj_object_get_value(config_playerData, "Attack2");
            sj_echo(Attack2values);


            sj_get_integer_value(Healthvalues, &PlayerHP);
            sj_get_integer_value(Attackvalues, &PlayerA1);
            sj_get_integer_value(Attack2values, &PlayerA2);

        }
    }
    
    if (!config2)
    {
        slog("oh no");
    }
    else {
        slog("FILE FOUND");
        SJson* bossArray_config = sj_object_get_value(config2, "Boss");
        SJson* config_bossData;

        for (int x = 0; x < sj_array_get_count(bossArray_config); x++)
        {
            config_bossData = sj_array_get_nth(bossArray_config, x);
            sj_echo(config_bossData);

            SJson* Healthvalues = sj_object_get_value(config_bossData, "Health");
            sj_echo(Healthvalues);

            SJson* Attackvalues = sj_object_get_value(config_bossData, "Attack");
            sj_echo(Attackvalues);

            SJson* Attack2values = sj_object_get_value(config_bossData, "Attack2");
            sj_echo(Attack2values);

            SJson* Attack3values = sj_object_get_value(config_bossData, "Attack3");
            sj_echo(Attack3values);


            sj_get_integer_value(Healthvalues, &BossHP);
            sj_get_integer_value(Attackvalues, &BossA1);
            sj_get_integer_value(Attack2values, &BossA2);
            sj_get_integer_value(Attack3values, &BossA3);

        }
    }
   // for (a = 0; a < 1; a++) { trainer1 = trainer1_spawn(vector3d(19, 0, 10)); trainer2 = trainer1_spawn(vector3d(70, -40, 10)); trainer3 = trainer1_spawn(vector3d(-70, 20, 10)); }//trainer 1 spawn
   // for (a = 0; a < 2; a++) { trainer4 = trainer2_spawn(vector3d(-60, -70, 10)); trainer5 = trainer2_spawn(vector3d(70, -70, 10)); }//trainer 2 spawn

    for (a = 0; a < 1; a++) { speed = speed_spawn(vector3d(0, -50, 10)); }  //speed pick up BLUE
    for (a = 0; a < 1; a++) { legend = legendary_spawn(vector3d(10 - 50, 80, 10)); } //legendary pick up YELLOW
    for (a = 0; a < 1; a++) { heal = heal_spawn(vector3d(80, 70, 10)); } // heal pick up HEAL
    for (a = 0; a < 1; a++) { radius = radius_spawn(vector3d(-50, -70, 10)); } // radius pick up RED
    for (a = 0; a < 1; a++) { fly = fly_spawn(vector3d(-50, -80, 10)); } // radius pick up RED
    for (a = 0; a < 1; a++) { key_spawn(vector3d(-50, 100, 10)); key_spawn(vector3d(-50, 0, 10)); key_spawn(vector3d(-50, 0, 10)); key_spawn(vector3d(-50, 0, 10)); key_spawn(vector3d(-50, 0, 10));} // radius pick up RED
    music = Mix_LoadMUS("music/pokemon.mp3");
    Mix_PlayMusic(music, -1);
    slog_sync();
    gf3d_camera_set_scale(vector3d(1, 1, 1));
    player = player_new(vector3d(0, 0, 20),PlayerHP,PlayerA1,PlayerA2);
  //  for (a = 0; a < 2; a++) { boss = boss_spawn(vector3d(100, 100, 100), BossHP, BossA1, BossA2, BossA3); }
    if (player->target == NULL)
    {
        player->target = trainer1, trainer2, trainer3, trainer4, trainer5, speed, legend, heal, radius,key;
        trainer1->target = player;
        trainer2->target = player;
        trainer3->target = player;
        trainer4->target = player;
        trainer5->target = player;
        speed->target = player;
        legend->target = player;
        heal->target = player;
        radius->target = player;
           boss->target = player;
           key->target = player;
    }
    
    
    
    // main game loop
    slog("gf3d main loop begin");
    while (!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        SDL_GetMouseState(&mousex, &mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        entity_think_all();
        entity_update_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

        //3D draws
      
      //  entity_draw_all();
        //2D draws
        gf3d_sprite_draw(sprite, vector2d(500,500), vector2d(1200, 700), 1000);
        gf3d_sprite_draw(mouse, vector2d(mousex, mousey), vector2d(1, 1), (Uint32)mouseFrame);
        gf3d_vgraphics_render_end();

        if (keys[SDL_SCANCODE_UP])
        {
            done = 1;
            done2 = 0;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            done = 1;
            done2 = 1;
        }
    }

    while (!done2)
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
        if (player->objectives >= 1) // 3 objective win statement
        {
            done2 = 1;
            done3 = 0;
        }
        if (keys[SDL_SCANCODE_ESCAPE])done2 = 1; // exit condition
    }
    while (!done3) // win game scene
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        SDL_GetMouseState(&mousex, &mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        entity_think_all();
        entity_update_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

        //3D draws

      //  entity_draw_all();
        //2D draws
        gf3d_sprite_draw(sprite2, vector2d(300, 300), vector2d(1200, 700), 1000);
        gf3d_sprite_draw(mouse, vector2d(mousex, mousey), vector2d(1, 1), (Uint32)mouseFrame);
        gf3d_vgraphics_render_end();

        if (keys[SDL_SCANCODE_ESCAPE])
        {
            done = 1;
            done2 = 1;
            done3 = 1;
        }


    }
    world_delete(w);
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}
