#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "enemies.h"
#include "bullets.h"
#include "stars.h"
#include "sound.h"
#include "healthbar.h"

#define BUTTON_YELLOW 1
#define POTENTIOMETER 3
#define BUZZER 10

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

int readADC() {
  return analogRead(POTENTIOMETER);
}

void getPos(PlayerState *player) {
  int diff = player->targetX - player->x;

  if (abs(diff) > 1) {
    int speed = abs(diff) / 5 + 1;

    if (diff > 0) {
      player->x += speed;
    } else {
      player->x -= speed;
    }
  }
}

void drawPlayer(int x) {
  int ground = 63;
  u8g2.drawTriangle(x - 5, ground, x + 5, ground, x, ground - 5);
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

void checkElimination(BulletState *bullets, EnemyState *enemies, HealthState *health) {
  Enemy *e = enemies->head;

  while (e != NULL) {
    Enemy *nextEnemy = e->next;

    Bullet *b = bullets->head;

    while (b != NULL) {
      Bullet *nextBullet = b->next;

      int dx = b->x - (int)e->x;
      int dy = b->y - (int)e->y;

      if (abs(dx) <= 3 && abs(dy) <= 3) {
        startHitSound(&sound);
        deleteBullet(bullets, b);
        deleteEnemy(enemies, e);
        break;
      }

      b = nextBullet;
    }

    e = nextEnemy;
  }
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

void initPlayer(PlayerState *player) {
  player->x = 64;
  player->targetX = 64;
  player->lastButtonState = HIGH;
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

    u8g2.clearBuffer();

    int rawPos = readADC();
    rawPos = constrain(rawPos, 800, 3200);
    player.targetX = map(rawPos, 800, 3200, 5, 122);

    getPos(&player);

    bool currentButtonState = digitalRead(BUTTON_YELLOW);
    if (player.lastButtonState == HIGH && currentButtonState == LOW) {
      shootBullet(&bullets, player.x, 58);
    }
    player.lastButtonState = currentButtonState;

    updateBullets(&bullets);
    updateStars(&timers);
    handleSpawn(&enemies, &timers);
    updateEnemies(&enemies, &health);
    checkElimination(&bullets, &enemies, &health);
    updateSound(&sound);

    drawStars();
    drawPlayer(player.x);
    drawBullets(&bullets);
    drawEnemies(&enemies);
    showHealthBar(&health);
    

    u8g2.sendBuffer();
  }
}