#include "main.h"
#include "player.h"
#include "math.h"

void getPos(PlayerState *player) {
  int diff = player->targetX - player->x;

  if (abs(diff) > 1) {
    int speed = abs(diff) / 5 + 1;

    if (diff > 0) {
      player->x += speed;
    } else {
      player->x -= speed;
    }
  }
}

void initPlayer(PlayerState *player) {
  player->x = 64;
  player->targetX = 64;
  player->lastButtonState = HIGH;
}

void drawPlayer(int x) {
  int ground = 63;
  u8g2.drawTriangle(x - 5, ground, x + 5, ground, x, ground - 5);
}