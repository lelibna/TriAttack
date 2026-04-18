#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <U8g2lib.h>

typedef struct Bullet {
  int x;
  int y;
  struct Bullet *next;
  struct Bullet *prev;
} Bullet;

typedef struct Enemy {
  float x;
  float y;
  float speed;
  struct Enemy *next;
  struct Enemy *prev;
} Enemy;

typedef struct {
  Bullet *head;
} BulletState;

typedef struct {
  Enemy *head;
} EnemyState;

typedef struct {
  unsigned long gameStartTime;
  unsigned long lastSpawn;
  unsigned long nextSpawnDelay;
  unsigned long lastFrameTime;
} TimerState;

typedef struct {
  int x;
  int targetX;
  bool lastButtonState;
} PlayerState;

typedef struct HealthState{
    int hp;
    int maxHp;
    int dataPin;
    int clockPin;
    int latchPin;
} HealthState;

extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2;

extern const int frameDelay;

int readADC();
void getPos(PlayerState *player);
void drawPlayer(int x);

void startGameTimer(TimerState *timers);
int getRanDelay(TimerState *timers);

void checkElimination(BulletState *bullets, EnemyState *enemies, HealthState *health);

void initBullets(BulletState *bullets);
void initEnemies(EnemyState *enemies);
void initTimers(TimerState *timers);
void initPlayer(PlayerState *player);

#endif