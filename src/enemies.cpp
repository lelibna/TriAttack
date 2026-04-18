#include <stdlib.h>
#include <math.h>
#include "enemies.h"
#include "healthbar.h"
#define baseSpeed 1.0

float getEnemySpeed(TimerState *timers) {
  float t = (millis() - timers->gameStartTime) / 1000.0;
  float k = 0.152; //Skalierung
  float speed = baseSpeed * pow(1.01, k * t);
  if (speed > 8.0) speed = 8.0;

  return speed;
}

void spawnEnemy(EnemyState *enemies, TimerState *timers) {
  Enemy *e = (Enemy*) malloc(sizeof(Enemy));
  if (e == NULL) return;

  e->x = random(5, 122);
  e->y = 0;
  e->speed = getEnemySpeed(timers);
  e->next = NULL;
  e->prev = NULL;

  addEnemy(enemies, e);
}

void addEnemy(EnemyState *enemies, Enemy *e) {
  e->next = NULL;
  e->prev = NULL;

  if (enemies->head == NULL) {
    enemies->head = e;
    return;
  }

  Enemy *current = enemies->head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = e;
  e->prev = current;
}

void updateEnemies(EnemyState *enemies, HealthState *health) {
  Enemy *curr = enemies->head;

  while (curr != NULL) {
    Enemy *next = curr->next;

    curr->y += curr->speed;

    if (curr->y > 63) {
      updateHealth(health);
      deleteEnemy(enemies, curr);
    }

    curr = next;
  }
}

void drawEnemies(EnemyState *enemies) {
  Enemy *curr = enemies->head;

  while (curr != NULL) {
    int x = (int)curr->x;
    int y = (int)curr->y;

    u8g2.drawTriangle(x - 3, y - 3, x + 3, y - 3, x, y + 3);
    curr = curr->next;
  }
}

void handleSpawn(EnemyState *enemies, TimerState *timers) {
  unsigned long currentTime = millis();

  if (currentTime - timers->lastSpawn >= timers->nextSpawnDelay) {
    spawnEnemy(enemies, timers);
    timers->lastSpawn = currentTime;
    timers->nextSpawnDelay = getRanDelay(timers);
  }
}

void deleteEnemy(EnemyState *enemies, Enemy *e) {
  if (e == NULL) return;

  if (e->prev != NULL) {
    e->prev->next = e->next;
  } else {
    enemies->head = e->next;
  }

  if (e->next != NULL) {
    e->next->prev = e->prev;
  }

  free(e);
}