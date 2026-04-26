#ifndef PLAYERSELECT_H
#define PLAYERSELECT_H

#include "main.h"

typedef enum {
    PLAYER_1,
    PLAYER_2,
    PLAYER_3
} player_items;

void playerselect_update();
void playerselect_draw();
void reset_playerprofiles();
int getActiveProfile();
const char *getProfileNames(int index);


#endif