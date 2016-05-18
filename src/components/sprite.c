
#include "window.h"
#include "config/path.h"
#include "utility/macros.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

struct _sprite {
    SDL_Texture *texture;
    int dpos_id;
    int dquad_id;
    bool active;
};

static Sprite SPRITES[SPRITE_POOL_SIZE];

static SDL_Texture* Sprite_loadTexture(char* filename) {
    char path_to_image[128];
    SDL_Surface* temp_srf;
    SDL_Texture* texture;

    path_to_image[0] = '\0';
    strcat(path_to_image, Path_toSprites());
    strcat(path_to_image, filename);

    if ( (temp_srf = IMG_Load(path_to_image)) != NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path_to_image, IMG_GetError() );

    if ((texture = SDL_CreateTextureFromSurface( Window_getRenderer(), temp_srf )) != NULL)
        printf( "Unable to create texture from %s! SDL Error: %s\n", path_to_image, SDL_GetError() );

    SDL_FreeSurface(temp_srf);
    return texture;
}

void Sprite_init() {
    int id;
    int imgFlags = IMG_INIT_PNG;
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {   
        SPRITES[id].active = false;
        SPRITES[id].texture = NULL;
    }
}

int Sprite_new(char* filename, int dpos_id, int dquad_id) {
    int id;

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {
        if (!SPRITES[id].active) {
            SPRITES[id].texture = Sprite_loadTexture(filename);
            SPRITES[id].dpos_id = dpos_id;
            SPRITES[id].dquad_id = dquad_id;
            SPRITES[id].active = true;

            return id;
        }
    }
    pool_overflow(Sprite);
}

void Sprite_kill(int id) {
    if (!SPRITES[id].active) return;
    SDL_DestroyTexture(SPRITES[id].texture);
    SPRITES[id].texture = NULL;
    SPRITES[id].active = false;
}

void Sprite_update() {
    SDL_Renderer *screen = Window_getRenderer();
    int id;

    SDL_RenderClear( screen );

    for (id = 0; id < SPRITE_POOL_SIZE; ++id)
        if (SPRITES[id].active)
            SDL_RenderCopy(
                screen,
                SPRITES[id].texture,
                DrawPos_getPos(SPRITES[id].dpos_id),
                DrawQuad_getQuad(SPRITES[id].dquad_id) );

    SDL_RenderPresent( screen );
}

void Sprite_close() {
    int id;

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {   
        Sprite_kill(id);
    }

    IMG_Quit();
}
