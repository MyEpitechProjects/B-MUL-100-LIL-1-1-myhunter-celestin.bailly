/*
** EPITECH PROJECT, 2024
** my_hunter
** File description:
** mh.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SFML/System.h>
#include "struct.h"
#include <math.h>
#include <unistd.h>

int is_touching(sfSprite *sprite, sfRenderWindow *window, win_t *win)
{
    int spx = sfSprite_getPosition(sprite).x;
    int spy = sfSprite_getPosition(sprite).y;
    int spw = sfSprite_getGlobalBounds(sprite).width;
    int sph = sfSprite_getGlobalBounds(sprite).height;
    int msx = (sfSprite_getPosition(win->crosshair).x +
        (sfSprite_getGlobalBounds(sprite).width / 2));
    int msy = (sfSprite_getPosition(win->crosshair).y +
        (sfSprite_getGlobalBounds(sprite).height / 2));
    int t1 = ((msx > spx) && (msx < (spx + spw)));
    int t2 = ((msy > spy) && (msy < (spy + sph)));

    return (t1 && t2);
}

int is_clicked(sfSprite *sprite, sfRenderWindow *window, win_t *win)
{
    return (sfMouse_isButtonPressed(sfMouseLeft)
        && is_touching(sprite, window, win));
}

static void replay(win_t *win, data_t *datas)
{
    sfMusic_stop(win->gameover_song);
    datas->score = 0;
    datas->state = 0;
    datas->duck_tick = 0;
    datas->tick_frame = 25;
    datas->base_speed = 1;
    datas->score = 0;
    datas->ammo = datas->max_ammo;
    datas->sped[0] = datas->base_speed;
    datas->sped[1] = datas->base_speed;
    datas->sped[2] = 0;
    datas->duck_time = 30;
    sfClock_restart(win->clock);
}

int manage_events(win_t *win, data_t *datas, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(win->window, event)) {
        if (event->type == sfEvtClosed) {
            shutdown(win, datas);
            return 1;
        }
        if (event->type == sfEvtMouseButtonPressed){
            mouse_pressed(win, datas);
        }
        if (event->type == sfEvtKeyPressed && event->key.code == sfKeySpace
            && datas->state != 0 && datas->state != 1){
            datas->state = 0;
            replay(win, datas);
            sfMusic_stop(win->press_space);
        }
    }
    return 0;
}

static void gameover(win_t *win, data_t *datas)
{
    sfMusic_stop(win->main_song);
    if (sfMusic_getStatus(win->gameover_song) == sfStopped
        && datas->state == 3)
        sfMusic_play(win->gameover_song);
    datas->state = 3;
}

static int loop(win_t *win, data_t *datas)
{
    if (manage_events(win, datas, &(win->event)))
        return 0;
    if (sfMusic_getStatus(win->main_song) == sfStopped &&
        (datas->state == 0 || datas->state == 1))
        sfMusic_play(win->main_song);
    sfRenderWindow_clear(win->window, sfGreen);
    window(win, datas);
    render_sprite(win, datas);
    if (datas->ammo < 1 || (sfSprite_getPosition(win->bird).x > 1280))
        gameover(win, datas);
    if (sfTime_asSeconds(sfClock_getElapsedTime(win->clock)) >
        datas->duck_time && datas->state == 0)
        datas->state = 4;
    return 1;
}

int win(void)
{
    win_t *win = malloc(sizeof(win_t));
    data_t *datas = malloc(sizeof(data_t));
    int d;

    if (win == NULL || datas == NULL)
        return 84;
    init(win, datas);
    sfMusic_play(win->press_space);
    while (sfRenderWindow_isOpen(win->window)){
        d = loop(win, datas);
        if (d == 0)
            return 0;
    }
    destroy_all(win);
    free(win);
    free(datas);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || (argv[1][0] != '-' || argv[1][1] != 'h'))
        return win();
    else if (argc > 1 && (argv[1][0] == '-' && argv[1][1] == 'h')){
        write(1, "My_hunter :\n", 12);
        write(1, "Control :\n", 11);
        write(1, "Mouse (to shoot the duck).\n", 28);
        write(1, "Space (To start/restart game).\n", 32);
        write(1, "Game Info :\n", 13);
        write(1, "The duck speed increase every time he die.\n", 44);
        write(1, "The duck flee time increase every time he die.\n", 48);
        write(1, "If you dont have ammo or the he fly away, you loose.\n", 54);
    }
    return 0;
}
