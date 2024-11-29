/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
**  struct.h
*/

#ifndef LIBMY_H_
    #define LIBMY_H_
typedef struct win {
    sfRenderWindow *window;
    sfSprite *bird;
    sfSprite *crosshair;
    sfSprite *crossgun;
    sfSprite *main_bg;
    sfSprite *ded;
    sfSprite *menu_bg;
    sfEvent event;
    sfMusic *main_song;
    sfMusic *press_space;
    sfSoundBuffer *pew_buf;
    sfSound *pew;
    sfSoundBuffer *ah_buf;
    sfSound *ah;
    sfFont *font_honk;
    sfText *score_txt;
    sfText *ammo_txt;
    sfSprite *gameover_bg;
    sfMusic *gameover_song;
    sfClock *clock;
    sfText *fly_away;
} win_t;

typedef struct data {
    int bird_frm;
    int ded_frm;
    int animation_framerate;
    int duck_tick;
    int tick_frame;
    int click_protect;
    int state;
    int base_speed;
    double frame;
    int sped[3];
    int score;
    int ammo;
    int max_ammo;
    char *score_txt;
    char *ammo_txt;
    int duck_time;
} data_t;

void init(win_t *win, data_t *datas);
sfSprite *create_sprite ( char *filepath, double scaler[], int size[]);
void anim_sprite(sfSprite * sprite, int frame_count);
void set_Sprite_position(win_t *win, data_t *datas, int sped[]);
void fix_bird(sfSprite *sprite, sfRenderWindow *window, int *tab, int bsped);
void randomize_bird(sfSprite *sprite, sfRenderWindow *window, int *tab, int bsped);
void render_sprite(win_t *win, data_t *datas);
void window(win_t *win, data_t *datas);
int is_clicked(sfSprite *sprite, sfRenderWindow *window, win_t *win);
void shutdown(win_t *win, data_t *datas);
void mouse_pressed(win_t *win, data_t *datas);
void mouse_touch(win_t *win, data_t *datas);
void destroy_all(win_t *win);
void set_sprite_position(win_t *win, data_t *datas, int sped[]);


#endif
