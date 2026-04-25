#include "main.h"
#include "gameover.h"

void gameover_update() {
  if (isButtonBlocked()) return;
  if (digitalRead(BUTTON) == LOW) {
    setState(GS_MENU);
  }
}

void gameover_draw() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(30, 30, "GAME OVER");
}