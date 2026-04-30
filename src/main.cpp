#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "enemies.h"
#include "bullets.h"
#include "stars.h"
#include "sound.h"
#include "healthbar.h"
#include "player.h"
#include "game.h"
#include "titlescreen.h"
#include "gameover.h"
#include "menu.h"
#include "credits.h"
#include "playerselect.h"
#include "highscores.h"

static const StateHandler stateHandlers[] = {
  { GS_TITLESCREEN, titlescreen_update, titlescreen_draw },
  { GS_MENU,        menu_update,        menu_draw        },
  { GS_PLAYERSELECT,playerselect_update, playerselect_draw},
  { GS_HIGHSCORES,  highscores_update,  highscores_draw  },
  { GS_PLAYING,     playing_update,     playing_draw     },
  { GS_GAMEOVER,    gameover_update,    gameover_draw    },
  { GS_CREDITS,     credits_update,     credits_draw}
};

static GameState state = GS_TITLESCREEN;

static unsigned long stateEntryTime = 0;

static int lastScore;

const int numStates = sizeof(stateHandlers) / sizeof(stateHandlers[0]);

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0,
  18, // OLED_CLK
  19, // OLED_MOSI
  5,  // OLED_CS
  6,  // OLED_DC
  4   // OLED_RES
);

static HealthState health = {
  10, // hp
  10, // maxHp
  7,  // dataPin
  0,  // clockPin
  2   // latchPin
};

const int frameDelay = 30;

static BulletState bullets;
static EnemyState enemies;
static TimerState timers;
static PlayerState player;
static SoundState sound;
static ScoreState score;

int readADC() {
  return analogRead(POTENTIOMETER);
}

int getRanDelay(TimerState *timers) {
  float t = (millis() - timers->gameStartTime) / 1000.0; 

  float baseDelay = 1100 * exp((-0.002)*t);
  float wave = 100.0 * sin(t * 0.1);
  int jitter = random(-50, 50);

  int delay = (int)(baseDelay + wave + jitter + 600);

  if (delay < 500) delay = 500;
  if (delay > 2500) delay = 2500;

  return delay;
}

void initBullets(BulletState *bullets) {
  for(int i = 0; i < MAX_BULLETS; i++){
    bullets->bulletpool[i].active = false;
  }
}

void initEnemies(EnemyState *enemies) {
    for(int i = 0; i < MAX_ENEMIES; i++){
    enemies->enemypool[i].active = false;
  }
}

void initTimers(TimerState *timers) {
  timers->gameStartTime = 0;
  timers->lastSpawn = 0;
  timers->nextSpawnDelay = 0;
  timers->lastFrameTime = 0;
}

void setState(GameState newState){
  stateEntryTime = millis();

  switch(newState){
    case GS_PLAYING:
      initBullets(&bullets);
      initEnemies(&enemies);
      initTimers(&timers);
      initPlayer(&player);
      initSound(&sound, BUZZER);
      initScore(&score);
      health.hp = health.maxHp;
      showHealthBar(&health);
      startGameTimer(&timers);
      timers.nextSpawnDelay = getRanDelay(&timers);
      break;
    case GS_GAMEOVER:
      saveHighscore(getActiveProfile(), score.score);
      lastScore = score.score;
      score.score = 0;
      break;
    default:
      break;
  }
  state = newState;
}

bool isButtonBlocked(){
  return (millis() - stateEntryTime) < STATE_ENTRY_BLOCK_MS;
}

void startGameTimer(TimerState *timers) {
  timers->gameStartTime = millis();
}

void playing_update() {
  if (isButtonBlocked()) return;
  int rawPos = constrain(readADC(), POT_MIN, POT_MAX);
  player.targetX = map(rawPos, POT_MIN, POT_MAX, PLAYER_MIN_X, PLAYER_MAX_X);
  getPos(&player);

  bool btn = digitalRead(BUTTON);
  if (player.lastButtonState == HIGH && btn == LOW)
    shootBullet(&bullets, player.x, PLAYER_Y);
  player.lastButtonState = btn;

  updateBullets(&bullets);
  updateStars(getEnemySpeed(&timers));
  handleSpawn(&enemies, &timers);
  updateEnemies(&enemies, &health, &state);
  checkElimination(&bullets, &enemies, &health, &sound, &score);
  updateSound(&sound);
}

void playing_draw() {
  drawStars();
  drawPlayer(player.x);
  drawBullets(&bullets);
  drawEnemies(&enemies);
  showHealthBar(&health);
}

int getLastScore(){
  return lastScore;
}


void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(health.dataPin, OUTPUT);
  pinMode(health.clockPin, OUTPUT);
  pinMode(health.latchPin, OUTPUT);
  digitalWrite(health.dataPin, LOW);
  digitalWrite(health.clockPin, LOW);
  digitalWrite(health.latchPin, LOW);
  clearHealthBar(&health);
  loadHighscores();

  randomSeed(analogRead(POTENTIOMETER));

  u8g2.begin();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - timers.lastFrameTime >= frameDelay) {
    timers.lastFrameTime = currentTime;

    u8g2.clearBuffer();

    for (int i = 0; i < numStates; i++) {
    if (stateHandlers[i].id == state) {
      stateHandlers[i].update();
      stateHandlers[i].draw();
      break;
      }
    }

    u8g2.sendBuffer();
  }
}