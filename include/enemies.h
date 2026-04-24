#ifndef ENEMIES_H
#define ENEMIES_H

#define MAX_ENEMIES 5

#include "main.h"
#include "healthbar.h"

typedef struct Enemy {
  float x;
  float y;
  float speed;
  bool active;
} Enemy;

typedef struct {
  Enemy enemypool[MAX_ENEMIES];
} EnemyState;

void initEnemies(EnemyState *enemies);
float getEnemySpeed(TimerState *timers);
void spawnEnemy(EnemyState *enemies, TimerState *timers);
void updateEnemies(EnemyState *enemies, HealthState *health, GameState *state);
void drawEnemies(EnemyState *enemies);
void handleSpawn(EnemyState *enemies, TimerState *timers);

#endif