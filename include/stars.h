#ifndef STARS_H
#define STARS_H

#include "main.h"

#define MAX_STARS 11


typedef struct Star {
  int x;
  float y;
} Star;

void updateStars(float speed);
void drawStars();

#endif