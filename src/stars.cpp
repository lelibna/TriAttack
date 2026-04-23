#include "stars.h"

static Star stars[MAX_STARS] = {
    {5,2}, {20,10}, {40, 30}, {60, 5},
    {80, 20}, {100, 50}, {120, 15},
    {10, 20}, {30, 55}, {50, 25}, {70, 45}
};

void updateStars(float speed){
    for(int i = 0; i < MAX_STARS; i++){
        stars[i].y += speed * 0.2;

        if(stars[i].y > 63){
            stars[i].y = -5;
        }
    }
}

void drawStars() {
  for (int i = 0; i < MAX_STARS; i++) {
    u8g2.drawPixel(stars[i].x, (int)stars[i].y);
  }
}