/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Moves the background
*/
#include "my_runner.h"

void anim_background(background_t *background)
{
    sfTime time = sfClock_getElapsedTime(background->clock);
    float elapsed_time = sfTime_asMilliseconds(time);

    if (elapsed_time >= background->move_delay) {
        sfClock_restart(background->clock);
        if (background->rect.left < 1920) {
            sfSprite_setTextureRect(background->sprite, background->rect);
            background->rect.left += 1;
        } else {
            sfSprite_setTextureRect(background->sprite, background->rect);
            background->rect.left = 0;
        }
    }
}

void anim_backgrounds(background_t **backgrounds, sfRenderWindow *window)
{
    anim_background(backgrounds[0]);
    anim_background(backgrounds[1]);
    anim_background(backgrounds[2]);
    anim_background(backgrounds[3]);
    sfRenderWindow_drawSprite(window, backgrounds[0]->sprite, NULL);
    sfRenderWindow_drawSprite(window, backgrounds[2]->sprite, NULL);
    sfRenderWindow_drawSprite(window, backgrounds[3]->sprite, NULL);
    sfRenderWindow_drawSprite(window, backgrounds[1]->sprite, NULL);
}
