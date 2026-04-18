#ifndef ENEMIES_H
#define ENEMIES_H

#include "main.h"
#include "healthbar.h"

float getEnemySpeed(TimerState *timers);
void spawnEnemy(EnemyState *enemies, TimerState *timers);
void addEnemy(EnemyState *enemies, Enemy *e);
void deleteEnemy(EnemyState *enemies, Enemy *e);
void updateEnemies(EnemyState *enemies, HealthState *health);
void drawEnemies(EnemyState *enemies);
void handleSpawn(EnemyState *enemies, TimerState *timers);
void hitSound(int buzzer);

#endif