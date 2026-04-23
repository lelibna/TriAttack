#include "game.h"

void checkElimination(BulletState *bullets, EnemyState *enemies, HealthState *health, SoundState *sound, ScoreState *score) {
  Enemy *e = enemies->head;

  while (e != NULL) {
    Enemy *nextEnemy = e->next;

    Bullet *b = bullets->head;

    while (b != NULL) {
      Bullet *nextBullet = b->next;

      int dx = b->x - (int)e->x;
      int dy = b->y - (int)e->y;

      if (abs(dx) <= 3 && abs(dy) <= 3) {
        startHitSound(sound);
        deleteBullet(bullets, b);
        deleteEnemy(enemies, e);
        score++;
        break;
      }

      b = nextBullet;
    }

    e = nextEnemy;
  }
}