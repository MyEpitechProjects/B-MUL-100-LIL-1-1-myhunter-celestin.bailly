/*
** EPITECH PROJECT, 2024
** my_hunter
** File description:
** init.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"

void init_text(win_t *win)
{
    win->font_honk = sfFont_createFromFile("assets/font/font.ttf");
    win->score_txt = sfText_create();
    win->ammo_txt = sfText_create();
    win->fly_away = sfText_create();
    sfText_setFont(win->score_txt, win->font_honk);
    sfText_setFont(win->ammo_txt, win->font_honk);
    sfText_setFont(win->fly_away, win->font_honk);
    sfText_setCharacterSize(win->ammo_txt, 50);
    sfText_setCharacterSize(win->score_txt, 50);
    sfText_setCharacterSize(win->fly_away, 50);
    sfText_setPosition(win->score_txt, (sfVector2f){0, 660});
    sfText_setPosition(win->ammo_txt, (sfVector2f){0, 590});
    sfText_setPosition(win->fly_away, (sfVector2f){0, 0});
}

void init_default_data(data_t *datas)
{
    datas->bird_frm = 0;
    datas->ded_frm = 0;
    datas->score = 0;
    datas->animation_framerate = 10;
    datas->state = 2;
    datas->duck_tick = 0;
    datas->tick_frame = 25;
    datas->click_protect = 0;
    datas->base_speed = 1;
    datas->frame = 0;
    datas->score = 0;
    datas->max_ammo = 100;
    datas->ammo = datas->max_ammo;
    datas->sped[0] = datas->base_speed;
    datas->sped[1] = datas->base_speed;
    datas->sped[2] = 0;
    datas->duck_time = 30;
}

void init_audio(win_t *win)
{
    win->pew_buf = sfSoundBuffer_createFromFile("assets/audio/pew.wav");
    win->press_space = sfMusic_createFromFile("assets/audio/press_space.wav");
    win->ah_buf = sfSoundBuffer_createFromFile("assets/audio/ah.wav");
    win->main_song = sfMusic_createFromFile("assets/audio/killtheduck.wav");
    win->gameover_song = sfMusic_createFromFile("assets/audio/gameover.ogg");
    win->pew = sfSound_create();
    win->ah = sfSound_create();
    sfSound_setBuffer(win->pew, win->pew_buf);
    sfSound_setBuffer(win->ah, win->ah_buf);
}

void init_sprite(win_t *win)
{
    win->bird = create_sprite("assets/img/duck_fly.png",
        (double[]) {2, 2}, (int[]) {35, 35});
    win->crosshair = create_sprite("assets/img/cross.png",
        (double[]) {1, 1}, (int[]) {35, 35});
    win->ded = create_sprite("assets/img/duck_fall.png",
        (double[]) {2, 2}, (int[]) {35, 35});
    win->crossgun = create_sprite("assets/img/crossgun.png",
        (double[]) {2.9, 2.9}, (int[]) {287, 255});
    win->menu_bg = create_sprite("assets/img/menu_bg.png",
        (double[]) {1, 1}, (int[]) {1280, 720});
    win->main_bg = create_sprite("assets/img/main_bg.png",
        (double[]) {1, 1}, (int[]) {1280, 720});
    win->gameover_bg = create_sprite("assets/img/gameover_bg.png",
        (double[]) {1, 1}, (int[]) {1280, 720});
}

void init(win_t *win, data_t *datas)
{
    sfVideoMode mode = {1280, 720, 32};
    sfUint32 style = {sfClose};

    init_audio(win);
    init_default_data(datas);
    win->window = sfRenderWindow_create(mode, "Birds Hunter", style, 0);
    sfRenderWindow_setFramerateLimit(win->window, 60);
    sfRenderWindow_setMouseCursorVisible(win->window, sfFalse);
    win->clock = sfClock_create();
    init_sprite(win);
    init_text(win);
}
