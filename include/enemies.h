#ifndef ENEMIES_H
#define ENEMIES_H

#include "main.h"

float getEnemySpeed(TimerState *timers);
void spawnEnemy(EnemyState *enemies, TimerState *timers);
void addEnemy(EnemyState *enemies, Enemy *e);
void deleteEnemy(EnemyState *enemies, Enemy *e);
void updateEnemies(EnemyState *enemies);
void drawEnemies(EnemyState *enemies);
void handleSpawn(EnemyState *enemies, TimerState *timers);

#endif