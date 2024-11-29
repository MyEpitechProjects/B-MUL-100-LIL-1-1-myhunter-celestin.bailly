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

void destroy_all(win_t *win)
{
    sfRenderWindow_destroy(win->window);
    sfSprite_destroy(win->bird);
    sfSprite_destroy(win->crosshair);
    sfSprite_destroy(win->crossgun);
    sfSprite_destroy(win->main_bg);
    sfSprite_destroy(win->ded);
    sfSprite_destroy(win->menu_bg);
    sfMusic_destroy(win->main_song);
    sfMusic_destroy(win->press_space);
    sfSoundBuffer_destroy(win->pew_buf);
    sfSound_destroy(win->pew);
    sfSoundBuffer_destroy(win->ah_buf);
    sfSound_destroy(win->ah);
    sfFont_destroy(win->font_honk);
    sfText_destroy(win->score_txt);
    sfText_destroy(win->ammo_txt);
    sfSprite_destroy(win->gameover_bg);
    sfMusic_destroy(win->gameover_song);
    sfClock_destroy(win->clock);
    sfText_destroy(win->fly_away);
}

sfSprite *create_sprite(char *filepath, double scaler[], int size[])
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfIntRect area = {0, 0, size[0], size[1]};
    sfVector2f scale = {scaler[0], scaler[1]};

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setTextureRect(sprite, area);
    sfSprite_setScale(sprite, scale);
    return sprite;
}

void anim_sprite(sfSprite * sprite, int frame_count)
{
    sfIntRect area = sfSprite_getTextureRect(sprite);

    area.left = (area.left + 35);
    if (area.left >= frame_count * 35)
        area.left = 0;
    sfSprite_setTextureRect(sprite, area);
}

void render_sprite(win_t *win, data_t *datas)
{
    if (datas->state == 2)
        sfRenderWindow_drawSprite(win->window, win->menu_bg, NULL);
    sfRenderWindow_display(win->window);
    if (sfSprite_getPosition(win->ded).y > 754 && datas->state == 1){
        sfSprite_setPosition(win->bird, (sfVector2f) {0, 360});
        sfSprite_setPosition(win->ded, (sfVector2f) {0, 360});
        sfClock_restart(win->clock);
        datas->state = 0;
    }
    if (datas->ded_frm == 0){
        anim_sprite(win->ded, 2);
    }
    datas->ded_frm = (datas->ded_frm + 1) % datas->animation_framerate;
    if (datas->bird_frm == 0)
        anim_sprite(win->bird, 3);
    datas->bird_frm = (datas->bird_frm + 1) % datas->animation_framerate;
    datas->duck_tick = datas->duck_tick + 1;
    datas->frame += 0.1;
}
