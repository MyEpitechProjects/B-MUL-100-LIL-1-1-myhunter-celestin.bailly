/*
** EPITECH PROJECT, 2024
** my_hunter
** File description:
** update.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"
#include <math.h>

int calc_int_size(int val)
{
    int num = 0;

    if (val == 0)
        return 1;
    while (val > 0){
        val = val / 10;
        num += 1;
    }
    return num;
}

void create_string_score(win_t *win, data_t *datas)
{
    char base[] = "Score : ";
    int tmp_sz;

    datas->score_txt = malloc(sizeof(char) * (9 +
        calc_int_size(datas->score)));
    if (datas->ammo_txt == NULL)
        return;
    for (int i = 0; base[i] != '\0'; i++)
        datas->score_txt[i] = base[i];
    for (int i = 0; i < calc_int_size(datas->score); i++){
        tmp_sz = datas->score;
        for (int i2 = 1; i2 < (calc_int_size(datas->score) - i); i2++)
            tmp_sz = tmp_sz / 10;
        datas->score_txt[8 + i] = (char) ((tmp_sz % 10) + 48);
    }
    datas->score_txt[8 + (calc_int_size(datas->score))] = '\0';
}

void create_string_ammo(win_t *win, data_t *datas)
{
    char base[] = "Ammo : ";
    char base2[] = " | 100";
    int tmp_sz;

    datas->ammo_txt = malloc(sizeof(char) * (15 + calc_int_size(datas->ammo)));
    if (datas->ammo_txt == NULL)
        return;
    for (int i = 0; base[i] != '\0'; i++)
        datas->ammo_txt[i] = base[i];
    for (int i = 0; i < calc_int_size(datas->ammo); i++){
        tmp_sz = datas->ammo;
        for (int i2 = 1; i2 < (calc_int_size(datas->ammo) - i); i2++)
            tmp_sz = tmp_sz / 10;
        datas->ammo_txt[7 + i] = (char) ((tmp_sz % 10) + 48);
    }
    for (int i = 0; base2[i] != '\0'; i++)
        datas->ammo_txt[(7 + (calc_int_size(datas->ammo)) + i)] = base2[i];
    datas->ammo_txt[13 + (calc_int_size(datas->ammo))] = '\0';
}

static void handle_text(win_t *win, data_t *datas)
{
    sfRenderWindow_drawSprite(win->window, win->main_bg, NULL);
    create_string_score(win, datas);
    sfText_setString(win->score_txt, datas->score_txt);
    sfRenderWindow_drawText(win->window, win->score_txt, NULL);
    create_string_ammo(win, datas);
    sfText_setString(win->ammo_txt, datas->ammo_txt);
    sfRenderWindow_drawText(win->window, win->ammo_txt, NULL);
    sfText_setString(win->fly_away, "");
    if (datas->state == 4)
        sfText_setString(win->fly_away, "The duck is flying away");
    sfRenderWindow_drawText(win->window, win->fly_away, NULL);
    if (datas->ammo_txt != NULL){
        free(datas->ammo_txt);
        free(datas->score_txt);
    }
}

static void handle_dead_duck(win_t *win, data_t *datas)
{
    datas->animation_framerate = 10;
    sfRenderWindow_drawSprite(win->window, win->ded, NULL);
    sfSprite_move(win->ded, (sfVector2f) {0, 4});
}

static void handle_cross(win_t *win, data_t *datas)
{
    sfRenderWindow_drawSprite(win->window, win->crosshair, NULL);
    sfRenderWindow_drawSprite(win->window, win->crossgun, NULL);
}

void window(win_t *win, data_t *datas)
{
    if (datas->state == 1 || datas->state == 0 || datas->state == 4){
        handle_text(win, datas);
    } else if (datas->state == 3){
        sfRenderWindow_drawSprite(win->window, win->gameover_bg, NULL);
    }
    if (datas->state == 0 || datas->state == 4){
        sfRenderWindow_drawSprite(win->window, win->bird, NULL);
        datas->animation_framerate = 100 / datas->base_speed;
    }
    if (datas->state == 1){
        handle_dead_duck(win, datas);
    }
    if (datas->duck_tick % datas->tick_frame == 0)
        randomize_bird(win->bird, win->window, datas->sped,
            datas->base_speed);
    fix_bird(win->bird, win->window, datas->sped, datas->base_speed);
    set_sprite_position(win, datas, datas->sped);
    if (datas->state == 1 || datas->state == 0 || datas->state == 4){
        handle_cross(win, datas);
    }
}
