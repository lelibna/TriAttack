#ifndef BULLETS_H
#define BULLETS_H
#include "main.h"

typedef struct Bullet {
  int x;
  int y;
  struct Bullet *next;
  struct Bullet *prev;
} Bullet;

typedef struct {
  Bullet *head;
} BulletState;

void initBullets(BulletState *bullets);
void shootBullet(BulletState *bullets, int startX, int startY);
void addBullet(BulletState *bullets, Bullet *b);
void deleteBullet(BulletState *bullets, Bullet *b);
void updateBullets(BulletState *bullets);
void drawBullets(BulletState *bullets);

#endif