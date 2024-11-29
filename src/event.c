/*
** EPITECH PROJECT, 2024
** my_hunter
** File description:
** event.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"
#include <math.h>

void mouse_touch(win_t *win, data_t *datas)
{
    sfSound_play(win->ah);
    datas->score += 1;
    datas->state = 1;
    datas->base_speed += 1;
    datas->ammo += 10;
    datas->duck_time -= 2;
    if (datas->duck_time < 5)
        datas->duck_time = 5;
    if (datas->ammo > 100)
        datas->ammo = 100;
}

void mouse_pressed(win_t *win, data_t *datas)
{
    if (is_clicked(win->bird, win->window, win) && (datas->state == 0
        || datas->state == 4) && datas->ammo > 0)
        mouse_touch(win, datas);
    if (datas->state == 0 && datas->ammo > 0){
        datas->ammo -= !((datas->ammo - 1) < 0);
        sfSound_play(win->pew);
    }
}

void shutdown(win_t *win, data_t *datas)
{
    sfMusic_destroy(win->main_song);
    sfSound_destroy(win->pew);
    sfSoundBuffer_destroy(win->pew_buf);
    sfSound_destroy(win->ah);
    sfRenderWindow_close(win->window);
}
