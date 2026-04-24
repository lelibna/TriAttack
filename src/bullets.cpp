#include "bullets.h"

void shootBullet(BulletState *bullets, int startX, int startY) {
  for(int i = 0; i < MAX_BULLETS; i++){
    if(!bullets->bulletpool[i].active){
      bullets->bulletpool[i] = {startX, startY, true};
      return;
    }
  }
}

void updateBullets(BulletState *bullets) {
  for(int i = 0; i < MAX_BULLETS; i++){
    if(!bullets->bulletpool[i].active) continue;
    bullets->bulletpool[i].y -= 4;
    if(bullets->bulletpool[i].y < 0){
      bullets->bulletpool[i].active = false;
    }
  }
}

void drawBullets(BulletState *bullets) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets->bulletpool[i].active) continue;
    u8g2.drawDisc(bullets->bulletpool[i].x, bullets->bulletpool[i].y, 1);
  }
}