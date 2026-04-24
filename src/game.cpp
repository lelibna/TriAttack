#include "game.h"
#include "main.h"

void checkElimination(BulletState *bullets, EnemyState *enemies, HealthState *health, SoundState *sound, ScoreState *score) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies->enemypool[i].active) continue;

    for (int j = 0; j < MAX_BULLETS; j++) {
      if (!bullets->bulletpool[j].active) continue;

      int dx = bullets->bulletpool[j].x - (int)enemies->enemypool[i].x;
      int dy = bullets->bulletpool[j].y - (int)enemies->enemypool[i].y;

      if (abs(dx) <= 3 && abs(dy) <= 3) {
        startHitSound(sound);
        bullets->bulletpool[j].active = false;
        enemies->enemypool[i].active = false;
        score->score++;
        break;
      }
    }
  }
}