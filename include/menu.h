#ifndef MENU_H
#define MENU_H

#include "main.h"

typedef enum {
    M_PLAY,
    M_HIGHSCORES,
    M_CREDITS,
    M_COUNT
} menu_items;

typedef struct {
    GameState gs_item;
    menu_items menu_item;
} MenuHandler;

void menu_update();
void menu_draw();
void reset_menu();

#endif