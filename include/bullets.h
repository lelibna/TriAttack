#ifndef BULLETS_H
#define BULLETS_H
#include "main.h"

void shootBullet(BulletState *bullets, int startX, int startY);
void addBullet(BulletState *bullets, Bullet *b);
void deleteBullet(BulletState *bullets, Bullet *b);
void updateBullets(BulletState *bullets);
void drawBullets(BulletState *bullets);

#endif