/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Functions related to the object_t struct
*/
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "my_runner.h"

void select_texture_and_pos(int type, object_t *object, int x, int y)
{
    sfVector2f scale;

    if (type == 0) {
        object->texture = sfTexture_createFromFile("./ressources/ground_sprite.png", NULL);
        scale.x = 0.5;
        scale.y = 0.5;
        object->pos.x = x * 100;
        object->pos.y = y * 100;
    }
    else if (type == 3) {
        object->texture = sfTexture_createFromFile("./ressources/end_ship.png", NULL);
        object->pos.x = x * 100 - 125;
        object->pos.y = y * 100 - 275;
        scale.x = 1.0;
        scale.y = 1.0;
    } else {
        object->texture = sfTexture_createFromFile("./ressources/spike.png", NULL);
        scale.x = 0.3;
        scale.y = 0.3;
        object->pos.x = x * 100 + 28;
        object->pos.y = y * 100 + 25;
    }
    sfSprite_setScale(object->sprite, scale);
}

int create_object(object_t **object_head, int y, int x, char type)
{
    object_t *new_object = malloc(sizeof(object_t));

    if (new_object == NULL)
        return (84);
    new_object->sprite = sfSprite_create();
    new_object->type = type - '0';
    select_texture_and_pos(type - '0', new_object, x, y);
    sfSprite_setTexture(new_object->sprite, new_object->texture, sfFalse);
    sfSprite_setPosition(new_object->sprite, new_object->pos);
    new_object->next = *object_head;
    *object_head = new_object;
    return (0);
}

int add_objects_of_line(object_t **object_head, int y, FILE *fd)
{
    int x = 0;
    char *buffer = NULL;
    size_t size = 0;

    if (fd == NULL)
        return (84);
    getline(&buffer, &size, fd);
    while (buffer[x] != '\0') {
        if (buffer[x] != ' ' && buffer[x] != '\n')
            create_object(object_head, y, x, buffer[x]);
        x++;
    }
    free(buffer);
    return (0);
}

object_t *create_objects(char const *filepath)
{
    FILE *fd = fopen(filepath, "r");
    object_t *objects = NULL;

    for (int y = 0; y < 10; y++)
        add_objects_of_line(&objects, y, fd);
    fclose(fd);
    return (objects);
}

void destroy_objects(object_t *objects)
{
    object_t *prev_object = NULL;

    while (objects != NULL) {
        prev_object = objects;
        objects = objects->next;
        sfSprite_destroy(prev_object->sprite);
        sfTexture_destroy(prev_object->texture);
        free(prev_object);
    }
}
