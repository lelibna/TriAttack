#ifndef ENEMIES_H
#define ENEMIES_H

#include "main.h"
#include "healthbar.h"

typedef struct Enemy {
  float x;
  float y;
  float speed;
  struct Enemy *next;
  struct Enemy *prev;
} Enemy;

typedef struct {
  Enemy *head;
} EnemyState;

void initEnemies(EnemyState *enemies);
float getEnemySpeed(TimerState *timers);
void spawnEnemy(EnemyState *enemies, TimerState *timers);
void addEnemy(EnemyState *enemies, Enemy *e);
void deleteEnemy(EnemyState *enemies, Enemy *e);
void updateEnemies(EnemyState *enemies, HealthState *health, GameState *state);
void drawEnemies(EnemyState *enemies);
void handleSpawn(EnemyState *enemies, TimerState *timers);

#endif