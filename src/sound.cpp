#include "sound.h"

void initSound(SoundState *sound, int buzzerPin) {
  sound->buzzerPin = buzzerPin;
  sound->hitActive = false;
  sound->hitStage = 0;
  sound->nextTime = 0;
}

void startHitSound(SoundState *sound) {
  sound->hitActive = true;
  sound->hitStage = 0;
  sound->nextTime = 0;
}

void updateSound(SoundState *sound) {
  if (!sound->hitActive) return;

  unsigned long now = millis();

  if (now >= sound->nextTime) {
    switch (sound->hitStage) {
      case 0:
        tone(sound->buzzerPin, 1200);
        sound->nextTime = now + 40;
        sound->hitStage++;
        break;

      case 1:
        tone(sound->buzzerPin, 800);
        sound->nextTime = now + 60;
        sound->hitStage++;
        break;

      case 2:
        noTone(sound->buzzerPin);
        sound->hitActive = false;
        break;
    }
  }
}