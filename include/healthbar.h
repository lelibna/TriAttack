#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "main.h"

typedef struct HealthState{
    int hp;
    int maxHp;
    int dataPin;
    int clockPin;
    int latchPin;
} HealthState;

void showHealthBar(HealthState *health);
void updateHealth(HealthState *health);
void clearHealthBar(HealthState *health);

#endif