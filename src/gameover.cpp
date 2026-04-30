#include "main.h"
#include "gameover.h"
#include "highscores.h"
#include "playerselect.h"

void gameover_update() {
  if (isButtonBlocked()) return;
  if (digitalRead(BUTTON) == LOW) {
    setState(GS_MENU);
  }
}

void gameover_draw() {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(25, 12, "GAME OVER");

    char buf[24];
    snprintf(buf, sizeof(buf), "Punkte:     %d", getLastScore());
    u8g2.drawStr(15, 30, buf);

    snprintf(buf, sizeof(buf), "Highscore: %d", getHighscore(getActiveProfile()));
    u8g2.drawStr(15, 45, buf);
}