#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL.h>
#include "gfc_types.h"
#include "gfc_vector.h"
#include "gfc_text.h"

typedef struct Sprite_S
{
    int ref_count;
    TextLine filepath;
    SDL_Texture* texture;
    Uint32 frames_per_line;
    Uint32 frame_w, frame_h;
}Sprite;

void gf3d_sprite_init(Uint32 max);
Sprite* gf3d_sprite_load_model(char *filename);
void gf3d_sprite_draw_model(Sprite *model, Vector3D position);

Sprite* gf3d_sprite_load_all(
    char* filename,
    Sint32 frameWidth,
    Sint32 frameHeigh,
    Sint32 framesPerLine
);

void gf3d_sprite_draw(
    Sprite* sprite,
    Vector3D position,
    Vector3D* scale,
    Vector3D* scaleCenter,
    Vector3D* rotation,
    Vector2D* flip,
    Vector4D* colorShift,
    Uint32 frame);

void gf3d_sprite_free(Sprite* sprite);
void gf3d_sprite_clear_all();




#endif