#ifndef STARS_H
#define STARS_H

#define MAX_STARS 11

#include "main.h"

typedef struct Star {
  int x;
  float y;
} Star;

void updateStars(TimerState *timers);
void drawStars();

#endif