
#include "utility/macros.h"
#include "components/sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

struct _sprite {
    SDL_Texture texture;
    int dpos_id;
    int dquad_id;
    bool active;
};

static Sprite SPRITES[SPRITE_POOL_SIZE];

static void Sprite_load();

void Sprite_init() {
    
}

int Sprite_new(char* filename, int dpos_id, int dquad_id) {
    
}

void Sprite_kill() {

}

void Sprite_update() {

}


