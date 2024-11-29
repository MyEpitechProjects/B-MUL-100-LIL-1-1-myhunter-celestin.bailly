/*
** EPITECH PROJECT, 2024
** my_hunter
** File description:
** sprite_move.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"
#include <math.h>

static void set_pos(win_t *win, int sped[], int drd[], int rd)
{
    if (rd == 1){
        sfSprite_move(win->bird, (sfVector2f) {sped[0] + (cos(drd[0])
            * drd[1]), sped[1] + ((cos(drd[0] * -1)) * drd[1])});
        sfSprite_move(win->ded, (sfVector2f) {sped[0] + (cos(drd[0])
            * drd[1]), sped[1] + ((cos(drd[0] * -1)) * drd[1])});
    }
    if (rd == 2){
        sfSprite_move(win->bird, (sfVector2f) {sped[0] + ((cos(drd[0])
        * -1)* drd[1]), sped[1] + (cos(drd[0]) * drd[1])});
        sfSprite_move(win->ded, (sfVector2f) {sped[0] + ((cos(drd[0])
        * -1) * drd[1]), sped[1] + (cos(drd[0]) * drd[1])});
    }
    if (rd == 3){
        sfSprite_move(win->bird, (sfVector2f) {sped[0] + (cos(drd[0])
            * drd[1]), sped[1] + (cos(drd[0]) * drd[1])});
        sfSprite_move(win->ded, (sfVector2f) {sped[0] +
            (cos(drd[0]) * drd[1]), sped[1] + (cos(drd[0]) * drd[1])});
    }
}

void random_bird_pos(win_t *win, int sped[], int drd[])
{
    int rd;
    int var1 = (sped[0] + ((cos(drd[0]) * -1) * drd[1]));
    int var2 = (sped[1] + ((cos(drd[0]) * -1) * drd[1]));

    srand(drd[0]);
    rd = (rand() % 4);
    if (rd == 0){
        sfSprite_move(win->bird, (sfVector2f) {var1, var2});
        sfSprite_move(win->ded, (sfVector2f) {var1, var2});
    }
    set_pos(win, sped, drd, rd);
}

void set_sprite_position(win_t *win, data_t *datas, int sped[])
{
    int rd = datas->base_speed;
    float d = datas->frame;

    sfSprite_setPosition(win->crosshair, (sfVector2f) {
        sfMouse_getPositionRenderWindow(win->window).x - (34 / 2) +
        (cos(d) * 15), sfMouse_getPositionRenderWindow(win->window).y
        + (sin(d) * 15)});
    sfSprite_setPosition(win->crossgun, (sfVector2f) {
        (sfMouse_getPositionRenderWindow(win->window).x - (34 / 2) +
        (cos(d) * 15)), sfMouse_getPositionRenderWindow(win->window).y
        + (sin(d) * 15)});
    if (datas->state == 0){
        random_bird_pos(win, sped, (int[]) {d, rd});
    } else if (datas->state == 4){
        sfSprite_move(win->bird, (sfVector2f) {datas->base_speed * 2, 0});
        sfSprite_move(win->ded, (sfVector2f) {datas->base_speed * 2, 0});
    }
    if (sfSprite_getPosition(win->crossgun).y < 0)
        sfSprite_setPosition(win->crossgun, (sfVector2f) {
        sfSprite_getPosition(win->crossgun).x, (sin(d) * rd)});
}

void fix_bird(sfSprite *sprite, sfRenderWindow *window, int *tab, int bsped)
{
    int spx = sfSprite_getPosition(sprite).x;
    int spy = (sfSprite_getPosition(sprite).y +
        sfSprite_getGlobalBounds(sprite).height);

    if (spx > 900)
        tab[0] = -bsped;
    else if (spx < 100)
        tab[0] = bsped;
    if (spy > 500)
        tab[1] = -bsped;
    else if (spy < 50)
        tab[1] = bsped;
}

void get_new_posfix(int *val)
{
    if (val[0] == 5 || val[0] == 6 || val[0] == 7)
        val[1] = -1;
    if (val[0] == 3 || val[0] == 4 || val[0] == 5)
        val[2] = -1;
    if (val[3] > 1280 && (val[0] == 3 || val[0] == 1 || val[0] == 2))
        val[1] = -1;
    else if (val[3] < 100 && (val[1] == -1))
        val[1] = 1;
    if (val[4] > 720 && (val[0] == 0 || val[0] == 1 || val[0] == 7))
        val[2] = -1;
    else if (val[4] < 100 && (val[2] == -1))
        val[2] = 1;
}

void randomize_bird(sfSprite *sprite, sfRenderWindow *window,
    int *tab, int bsped)
{
    int val[] = {0, 1, 1, sfSprite_getPosition(sprite).x,
        (sfSprite_getPosition(sprite).y +
        sfSprite_getGlobalBounds(sprite).height)};

    srand(time(NULL));
    val[0] = rand() % 8;
    get_new_posfix(val);
    if (val[0] == 0 || val[0] == 4){
        tab[0] = 0;
        tab[1] = bsped * val[2];
    }
    if (val[0] == 1 || val[0] == 3 || val[0] == 5 || val[0] == 7){
        tab[0] = bsped * val[1];
        tab[1] = bsped * val[2];
    }
    if (val[0] == 6 || val[0] == 2){
        tab[0] = bsped * val[1];
        tab[1] = 0;
    }
}
