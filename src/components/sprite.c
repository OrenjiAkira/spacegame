
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

static int LAYERS[LAYER_COUNT][SPRITE_POOL_SIZE];

static SDL_Texture* Sprite_loadTexture(char* filename) {
    char path_to_image[128];
    SDL_Surface* temp_srf;
    SDL_Texture* texture;

    path_to_image[0] = '\0';
    strcat(path_to_image, Path_toSprites());
    strcat(path_to_image, filename);

    temp_srf = IMG_Load(path_to_image);
    if (temp_srf == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path_to_image, IMG_GetError() );
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface( Window_getRenderer(), temp_srf );
    if (texture == NULL) {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path_to_image, SDL_GetError() );
        return NULL;
    }

    SDL_FreeSurface(temp_srf);
    return texture;
}

static void Sprite_addToLayer(int id, int layer) {
    int i;

    for (i = 0; i < SPRITE_POOL_SIZE; ++i) {
        if (LAYERS[layer][i] == -1) {
            LAYERS[layer][i] = id;
            return;
        }
    }
}

static void Sprite_removeFromLayer(int id) {
    int layer, i;

    for (layer = 0; layer < LAYER_COUNT; ++layer) {
        for (i = 0; i < SPRITE_POOL_SIZE; ++i) {
            if (LAYERS[layer][i] == id) {
                LAYERS[layer][i] = -1;
                return;
            }
        }
    }
}

static void Sprite_draw(int id) {
    if (SPRITES[id].active)
        SDL_RenderCopy(
            Window_getRenderer(),
            SPRITES[id].texture,
            DrawQuad_getQuad(SPRITES[id].dquad_id),
            DrawPos_getPos(SPRITES[id].dpos_id) );
}

void Sprite_init() {
    int id, l;
    int imgFlags = IMG_INIT_PNG;
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {
        for (l = 0; l < LAYER_COUNT; ++l) LAYERS[l][id] = -1;

        SPRITES[id].active = false;
        SPRITES[id].texture = NULL;
    }
}

int Sprite_new(char* filename, int dpos_id, int dquad_id, int layer) {
    int id;

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {
        if (!SPRITES[id].active) {
            SPRITES[id].texture = Sprite_loadTexture(filename);
            SPRITES[id].dpos_id = dpos_id;
            SPRITES[id].dquad_id = dquad_id;
            SPRITES[id].active = true;

            Sprite_addToLayer(id, layer);

            return id;
        }
    }
    pool_overflow(Sprite);
}

void Sprite_kill(int id) {
    if (!SPRITES[id].active) return;
    Sprite_removeFromLayer(id);
    SDL_DestroyTexture(SPRITES[id].texture);
    SPRITES[id].texture = NULL;
    SPRITES[id].active = false;
}

void Sprite_update() {
    SDL_Renderer *screen = Window_getRenderer();
    int i, layer;

    SDL_RenderClear( screen );
    for (layer = 0; layer < LAYER_COUNT; ++layer)
        for (i = 0; i < SPRITE_POOL_SIZE; ++i)
            if (LAYERS[layer][i] != -1)
                Sprite_draw(LAYERS[layer][i]);
}

void Sprite_close() {
    int id;

    for (id = 0; id < SPRITE_POOL_SIZE; ++id) {   
        Sprite_kill(id);
    }

    IMG_Quit();
}
