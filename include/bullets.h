#ifndef BULLETS_H
#define BULLETS_H
#include "main.h"
#define MAX_BULLETS 5

typedef struct Bullet {
  int x;
  int y;
  bool active;
} Bullet;

typedef struct {
  Bullet bulletpool[MAX_BULLETS];
} BulletState;

void initBullets(BulletState *bullets);
void shootBullet(BulletState *bullets, int startX, int startY);
void updateBullets(BulletState *bullets);
void drawBullets(BulletState *bullets);

#endif