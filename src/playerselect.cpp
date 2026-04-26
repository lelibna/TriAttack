#include "main.h"
#include "playerselect.h"

static const char* profileNames[PLAYERCOUNT] = { "Spieler 1", "Spieler 2", "Gast" };
static int currentplayer;

static bool buttonwaspressed = false;
static uint32_t pressstarttime = 0;
static bool longppresshandled = false;



void playerselect_update(){
    if (isButtonBlocked()) return;
    bool buttonpressed = (digitalRead(BUTTON) == LOW);

    if(buttonpressed && !buttonwaspressed){
        pressstarttime = millis();
        longppresshandled = false;
    } else if(buttonpressed && buttonwaspressed){
        if(!longppresshandled && (millis() - pressstarttime >= LONG_PRESS)){
            longppresshandled = true;
            setState(GS_PLAYING);
        }
    } else if (!buttonpressed && buttonwaspressed){
        if(!longppresshandled){
            currentplayer = (player_items)((currentplayer+1) % PLAYERCOUNT);
        }
    }
    buttonwaspressed = buttonpressed;
}

void playerselect_draw() {
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(20, 10, "Wer spielt?");

    for (int i = 0; i < PLAYERCOUNT; i++) {
        char buf[20];
        snprintf(buf, sizeof(buf), "%s%s", i == currentplayer ? "> " : "  ", profileNames[i]);
        u8g2.drawStr(10, 26 + i * 13, buf);
    }
}

void reset_playerprofiles() {
    currentplayer = 0;
    buttonwaspressed = false;
    pressstarttime = 0;
    currentplayer = 0;
}

int getActiveProfile() {
    return currentplayer;
}

const char *getProfileNames(int index){
    return profileNames[index];
}