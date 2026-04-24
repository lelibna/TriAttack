#include "titlescreen.h"
#include "main.h"

void titlescreen_update(){
    if(digitalRead(BUTTON) == LOW){
        setState(GS_PLAYING);
    }
}

void titlescreen_draw(){
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(25, 25, "TriAttack");
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(20, 45, "Start");
}