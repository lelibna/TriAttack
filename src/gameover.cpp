#include "main.h"
#include "gameover.h"

void gameover_update() {
  if (digitalRead(BUTTON) == LOW) {
    setState(GS_TITLESCREEN);
  }
}

void gameover_draw() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(30, 30, "GAME OVER");
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawStr(15, 45, "Neustart");
}