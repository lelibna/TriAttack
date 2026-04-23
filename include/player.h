#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int x;
  int targetX;
  bool lastButtonState;
} PlayerState;

void getPos(PlayerState *player);
void drawPlayer(int x);
void initPlayer(PlayerState *player);

#endif