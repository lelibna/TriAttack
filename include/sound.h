#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

typedef struct SoundState{
  int buzzerPin;
  bool hitActive;
  int hitStage;
  unsigned long nextTime;
} SoundState;

void initSound(SoundState *sound, int buzzerPin);
void startHitSound(SoundState *sound);
void updateSound(SoundState *sound);

#endif