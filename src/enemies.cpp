#include <stdlib.h>
#include <math.h>
#include "enemies.h"
#include "healthbar.h"
#include "main.h"
#define baseSpeed 1.0

float getEnemySpeed(TimerState *timers) {
  float t = (millis() - timers->gameStartTime) / 1000.0;
  float k = 0.152; //Skalierung
  float speed = baseSpeed * pow(1.01, k * t);
  if (speed > 8.0) speed = 8.0;

  return speed;
}

void spawnEnemy(EnemyState *enemies, TimerState *timers) {

  for(int i = 0; i < MAX_ENEMIES; i++){
    if(!enemies->enemypool[i].active){
      enemies->enemypool[i] = {(float)random(5, 122), 0, getEnemySpeed(timers), true};
      return;
    }
  }
}



void updateEnemies(EnemyState *enemies, HealthState *health, GameState *state) {

  for(int i = 0; i < MAX_ENEMIES; i++){
    if(!enemies->enemypool[i].active) continue;
    enemies->enemypool[i].y += enemies->enemypool[i].speed;
    if(enemies->enemypool[i].y > SCREEN_HEIGHT){
      updateHealth(health);
      enemies->enemypool[i].active = false;
    }
  }
}

void drawEnemies(EnemyState *enemies) {
  for(int i = 0; i < MAX_ENEMIES; i++){
    if(!enemies->enemypool[i].active) continue;
    int x = enemies->enemypool[i].x;
    int y = enemies->enemypool[i].y;
    u8g2.drawTriangle(x - 3, y - 3, x + 3, y - 3, x, y + 3);
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
