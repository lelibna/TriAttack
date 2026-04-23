#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <U8g2lib.h>

#define BUTTON_YELLOW 1
#define POTENTIOMETER 3
#define BUZZER 10
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define POT_MIN        800
#define POT_MAX       3200
#define PLAYER_MIN_X    5
#define PLAYER_MAX_X  122
#define PLAYER_Y       58

typedef enum {
  GS_PLAYING,
  GS_GAMEOVER,
  GS_TITLESCREEN,
} GameState;


typedef struct {
  unsigned long gameStartTime;
  unsigned long lastSpawn;
  unsigned long nextSpawnDelay;
  unsigned long lastFrameTime;
} TimerState;

typedef struct {
  unsigned long score;
  unsigned long highScore;
} ScoreState;

extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2;

int readADC();

void startGameTimer(TimerState *timers);
int getRanDelay(TimerState *timers);
void initTimers(TimerState *timers);

#endif