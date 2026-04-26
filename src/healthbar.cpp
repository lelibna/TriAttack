#include "healthbar.h"
#include <Arduino.h>

void showHealthBar(HealthState *health){
    int level = health->hp;

    if(level < 0) level = 0;
    if(level > health->maxHp) level = health->maxHp;

    uint8_t ic1 = 0;
    uint8_t ic2 = 0;

    for (int i = 0; i < level; i++) {
        if (i < 8) {
        ic1 |= (1 << i);
        } else {
        ic2 |= (1 << (i - 8));
        }
    }

    digitalWrite(health->latchPin, LOW);
    shiftOut(health->dataPin, health->clockPin, MSBFIRST, ic2);
    shiftOut(health->dataPin, health->clockPin, MSBFIRST, ic1);
    digitalWrite(health->latchPin, HIGH);
}

void updateHealth(HealthState *health){
    health->hp--;
    showHealthBar(health);
    if(health->hp <= 0) setState(GS_GAMEOVER);
}

void clearHealthBar(HealthState *health) {
    digitalWrite(health->latchPin, LOW);
    shiftOut(health->dataPin, health->clockPin, MSBFIRST, 0);
    shiftOut(health->dataPin, health->clockPin, MSBFIRST, 0);
    digitalWrite(health->latchPin, HIGH);
}