#include "main.h"
#include "highscores.h"
#include "playerselect.h"
#include <Preferences.h>

static Preferences prefs;
static int highscores[PLAYERCOUNT] = {0, 0, 0};

void loadHighscores() {
    prefs.begin("highscores", true);
    for (int i = 0; i < PLAYERCOUNT; i++) {
        char key[8];
        snprintf(key, sizeof(key), "p%d", i);
        highscores[i] = prefs.getInt(key, 0);
    }
    prefs.end();
}

void saveHighscore(int profileIndex, int score) {
    if (score <= highscores[profileIndex]) return;

    highscores[profileIndex] = score;

    prefs.begin("highscores", false);
    char key[8];
    snprintf(key, sizeof(key), "p%d", profileIndex);
    prefs.putInt(key, score);
    prefs.end();
}

int getHighscore(int profileIndex) {
    return highscores[profileIndex];
}

void highscores_update(){
  if (isButtonBlocked()) return;
  if (digitalRead(BUTTON) == LOW) {
    setState(GS_MENU);
  }
}

void highscores_draw(){
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(25, 12, "HIGHSCORES");

    char buf[32];
    for(int i = 0; i < PLAYERCOUNT; i++){
        snprintf(buf, sizeof(buf), "%s:     %d", getProfileNames(i) , getHighscore(i));
        u8g2.drawStr(15, 30+12*i, buf);
    }
}