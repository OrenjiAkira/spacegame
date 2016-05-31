
#include "game.h"
#include "factory.h"
#include "action.h"
#include "config/conf.h"
#include "config/font.h"
#include "utility/direction.h"
#include "utility/vector.h"
#include "components/physics.h"
#include "components/drawpos.h"
#include "components/drawquad.h"
#include "components/sprite.h"
#include "components/textbox.h"
#include "components/timer.h"

#include <stdio.h>
#include <stdlib.h>

/* Load entity from conf */

void Factory_loadPlanet() {
    float m, r, x, y;
    int phys, dquad, dpos, sprite, planet;

    Conf_getPlanetValues(&m, &r, &x, &y);
    phys = Physics_new(m, r, x, y, 0, 0);
    dquad = DrawQuad_new(1408, 128, 128, 128);
    dpos = DrawPos_new(phys, 128, 128, 64, 64);
    sprite = Sprite_new("planetv2.png", dpos, dquad, 1);
    planet = Entity_new(phys, dquad, dpos, sprite, -1);
    Action_add(ACTION_ANIMATE, planet);
    printf("< PLANET ID #%d >\n", planet);
}

void Factory_loadPlayer1() {
    float m, r, x, y, vx, vy;
    int phys, dquad, dpos, sprite, textbox;
    char name[32];

    printf("%s\n", Conf_getString(CONF_SHIP1));
    Conf_getShipValues(0, name, &m, &r, &x, &y, &vx, &vy);
    phys = Physics_new(m, r, x, y, vx, vy);
    dquad = DrawQuad_new(768, 64, 64, 64);
    dpos = DrawPos_new(phys, 64, 64, 32, 32);
    sprite = Sprite_new("cat00.png", dpos, dquad, 1);
    dpos = DrawPos_new(phys, 0, 0, 0, 0);
    textbox = Textbox_new(name, dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);

    Game_setPlayer1( Entity_new(phys, dquad, dpos, sprite, textbox) );
    Action_add(ACTION_GRAVITY, Game_getPlayer1());
    Action_add(ACTION_COLLIDE, Game_getPlayer1());
    printf("< SHIP1 ID #%d >\n", Game_getPlayer1());
}

void Factory_loadPlayer2() {
    float m, r, x, y, vx, vy;
    int phys, dquad, dpos, sprite, textbox;
    char name[32];

    printf("%s\n", Conf_getString(CONF_SHIP2));
    Conf_getShipValues(1, name, &m, &r, &x, &y, &vx, &vy);
    phys = Physics_new(m, r, x, y, vx, vy);
    dquad = DrawQuad_new(768, 64, 64, 64);
    dpos = DrawPos_new(phys, 64, 64, 32, 32);
    sprite = Sprite_new("cat01.png", dpos, dquad, 1);
    dpos = DrawPos_new(phys, 0, 0, 0, 0);
    textbox = Textbox_new(name, dpos, TEXTALIGN_CENTER, FONTSIZE_SMALL, FONTCOLOR_WHITE);
    
    Game_setPlayer2( Entity_new(phys, dquad, dpos, sprite, textbox) );
    Action_add(ACTION_GRAVITY, Game_getPlayer2());
    Action_add(ACTION_COLLIDE, Game_getPlayer2());
    printf("< SHIP2 ID #%d >\n", Game_getPlayer2());
}

void Factory_loadBackground() {
    int dpos, sprite, bg;
    /* Background */
    dpos = DrawPos_new(-1, 800, 600, 400, 300);
    sprite = Sprite_new("background.png", dpos, -1, 0);
    bg = Entity_new(-1, -1, dpos, sprite, -1);
    printf("< BACKGROUND ID #%d >\n", bg);
}


/* New entity from game */

void Factory_newBullet(int origin_body, float m, float r, float lt) {
    Vector pos, aux;
    int phys, dquad, dpos, sprite;
    int dir, bullet;
        
    /* Calculando posição de disparo
    (aux é uma distância offset para
    não haver collisão imediata) */
    dir = Physics_getDirection(origin_body);
    Vector_copy(&aux, Direction_getVector(dir));
    Vector_mult(&aux, (r + 2.5));
    Vector_copy(&pos, Physics_getPos(origin_body));
    Vector_add(&pos, &aux);

    /* Calculando velocidade de disparo
    (aux aqui é a velocidade mesmo,
    apenas aproveitei a struct para
    economizar memória mesmo) */
    Vector_copy(&aux, Direction_getVector(dir));
    Vector_mult(&aux, SPEEDLIMIT);

    /* Criando entidade */
    phys = Physics_new(m, r, pos.x, pos.y, aux.x, aux.y);
    dquad = DrawQuad_new(48, 16, 16, 16);
    dpos = DrawPos_new(phys, 16, 16, 8, 8);
    sprite = Sprite_new("bullet.png", dpos, dquad, 1);
    bullet = Entity_new(phys, dquad, dpos, sprite, -1);

    /* Definindo tempo de vida da bullet */
    Entity_addTimer(bullet, TIMER_COUNTDOWN1, lt);

    /* Adicionando ações */
    Action_add(ACTION_AUTODIE, bullet);
    Action_add(ACTION_GRAVITY, bullet);
    Action_add(ACTION_COLLIDE, bullet);
    Action_add(ACTION_ANIMATE, bullet);
}

void Factory_newExplosion(int origin_body) {
    Vector pos;
    int dquad, dpos, sprite;
    int explosion;
    
    printf("[ NEW EXPLOSION ]\n");

    dpos = DrawPos_new(-1, 64, 64, 32, 32);
    Vector_copy(&pos, Physics_getPos(origin_body));
    DrawPos_setPos(dpos, &pos);

    dquad = DrawQuad_new(512, 64, 64, 64);
    sprite = Sprite_new("explosion.png", dpos, dquad, 1);

    explosion = Entity_new(-1, dquad, dpos, sprite, -1);

    Entity_addTimer(explosion, TIMER_COUNTDOWN1, 0.8); /* 8 frames */

    /* Adicionando ações */
    Action_add(ACTION_AUTODIE, explosion);
    Action_add(ACTION_ANIMATE, explosion);
}


