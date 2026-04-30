#include "main.h"
#include "menu.h"

static menu_items currentItem = M_PLAY;

static bool buttonwaspressed = false;
static uint32_t pressstarttime = 0;
static bool longppresshandled = false;

static const MenuHandler menuhandler[] = {
    {GS_PLAYERSELECT,    M_PLAY},
    {GS_HIGHSCORES, M_HIGHSCORES},
    {GS_CREDITS,    M_CREDITS}
}; 

void menu_update(){
    if (isButtonBlocked()) return;
    bool buttonpressed = (digitalRead(BUTTON) == LOW);

    if(buttonpressed && !buttonwaspressed){
        pressstarttime = millis();
        longppresshandled = false;
    } else if(buttonpressed && buttonwaspressed){
        if(!longppresshandled && (millis() - pressstarttime >= LONG_PRESS)){
            longppresshandled = true;
            for (int i = 0; i < M_COUNT; i++) {
                if (menuhandler[i].menu_item == currentItem) {
                    setState(menuhandler[i].gs_item);
                    reset_menu();
                    break;
                }
            }
        }
    } else if (!buttonpressed && buttonwaspressed){
        if(!longppresshandled){
            currentItem = (menu_items)((currentItem+1) % M_COUNT);
        }
    }
    buttonwaspressed = buttonpressed;
}

void menu_draw() {
    u8g2.setFont(u8g2_font_6x10_tf);

    u8g2.drawStr(20, 15, "MENU");

    u8g2.drawStr(10, 32, currentItem == M_PLAY ? "> Spielen" : "  Spielen");
    u8g2.drawStr(10, 44, currentItem == M_HIGHSCORES ? "> Highscores" : "  Highscores");
    u8g2.drawStr(10, 56, currentItem == M_CREDITS ? "> Credits" : "  Credits");
    /* TODO ZUR FOR SCHLEIFE ÄNDERN
    for (int i = 0; i < M_COUNT; i++) {
        char buf[20];
        snprintf(buf, sizeof(buf), "%s%s", i == currentItem ? "> " : "  ", profileNames[i]);
        u8g2.drawStr(10, 26 + i * 13, buf);
    }
    */
}

void reset_menu(){
    currentItem = M_PLAY;
}

