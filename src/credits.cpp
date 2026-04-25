#include "main.h"
#include "credits.h"

void credits_update(){
    if (isButtonBlocked()) return;
    if (digitalRead(BUTTON) == LOW) {
        setState(GS_MENU);
    }
}

void credits_draw(){
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(40, 10, "Credits");
    u8g2.drawStr(10, 30, "Alles:  Lena");
    u8g2.drawStr(10, 40, "Unterstüzung: Tobi");
}