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

//TODO Linked list entfernen?


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
static GameState state = GS_PLAYING;

int readADC() {
  return analogRead(POTENTIOMETER);
}


void startGameTimer(TimerState *timers) {
  timers->gameStartTime = millis();
}

int getRanDelay(TimerState *timers) {
  float t = (millis() - timers->gameStartTime) / 1000.0; 

  float baseDelay = 1500 * exp((-0.002)*t);
  float wave = 100.0 * sin(t * 0.1);
  int jitter = random(-50, 50);

  int delay = (int)(baseDelay + wave + jitter + 600);

  if (delay < 500) delay = 500;
  if (delay > 2500) delay = 2500;

  return delay;
}

void initBullets(BulletState *bullets) {
  bullets->head = NULL;
}

void initEnemies(EnemyState *enemies) {
  enemies->head = NULL;
}

void initTimers(TimerState *timers) {
  timers->gameStartTime = 0;
  timers->lastSpawn = 0;
  timers->nextSpawnDelay = 0;
  timers->lastFrameTime = 0;
}


void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(health.dataPin, OUTPUT);
  pinMode(health.clockPin, OUTPUT);
  pinMode(health.latchPin, OUTPUT);
  digitalWrite(health.dataPin, LOW);
  digitalWrite(health.clockPin, LOW);
  digitalWrite(health.latchPin, LOW);
  clearHealthBar(&health);

  initBullets(&bullets);
  initEnemies(&enemies);
  initTimers(&timers);
  initPlayer(&player);
  initSound(&sound, BUZZER);
  health.hp = health.maxHp;
  showHealthBar(&health);

  randomSeed(analogRead(POTENTIOMETER));

  startGameTimer(&timers);
  timers.nextSpawnDelay = getRanDelay(&timers);

  u8g2.begin();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - timers.lastFrameTime >= frameDelay) {
    timers.lastFrameTime = currentTime;

    if(state == GS_GAMEOVER){
        u8g2.drawStr(30,30,"GAME OVER");
        u8g2.sendBuffer();
        return;
    }

    u8g2.clearBuffer();

    int rawPos = readADC();
    rawPos = constrain(rawPos, POT_MIN, POT_MAX);
    player.targetX = map(rawPos, POT_MIN, POT_MAX, PLAYER_MIN_X, PLAYER_MAX_X);

    getPos(&player);

    bool currentButtonState = digitalRead(BUTTON_YELLOW);
    if (player.lastButtonState == HIGH && currentButtonState == LOW) {
      shootBullet(&bullets, player.x, PLAYER_Y);
    }
    player.lastButtonState = currentButtonState;

    updateBullets(&bullets);
    updateStars(getEnemySpeed(&timers));
    handleSpawn(&enemies, &timers);
    updateEnemies(&enemies, &health, &state);
    checkElimination(&bullets, &enemies, &health, &sound, &score);
    updateSound(&sound);

    drawStars();
    drawPlayer(player.x);
    drawBullets(&bullets);
    drawEnemies(&enemies);
    showHealthBar(&health);
    

    u8g2.sendBuffer();
  }
}