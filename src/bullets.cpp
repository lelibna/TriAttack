#include "bullets.h"

void shootBullet(BulletState *bullets, int startX, int startY) {
  Bullet *b = (Bullet*) malloc(sizeof(Bullet));
  if (b == NULL) return;

  b->x = startX;
  b->y = startY;
  b->next = NULL;
  b->prev = NULL;

  addBullet(bullets, b);
}

void addBullet(BulletState *bullets, Bullet *b) {
  b->next = NULL;
  b->prev = NULL;

  if (bullets->head == NULL) {
    bullets->head = b;
    return;
  }

  Bullet *current = bullets->head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = b;
  b->prev = current;
}

void deleteBullet(BulletState *bullets, Bullet *b) {
  if (b == NULL) return;

  if (b->prev != NULL) {
    b->prev->next = b->next;
  } else {
    bullets->head = b->next;
  }

  if (b->next != NULL) {
    b->next->prev = b->prev;
  }

  free(b);
}

void updateBullets(BulletState *bullets) {
  Bullet *curr = bullets->head;

  while (curr != NULL) {
    Bullet *next = curr->next;

    curr->y -= 4;

    if (curr->y < 0) {
      deleteBullet(bullets, curr);
    }

    curr = next;
  }
}

void drawBullets(BulletState *bullets) {
  Bullet *curr = bullets->head;

  while (curr != NULL) {
    u8g2.drawDisc(curr->x, curr->y, 1);
    curr = curr->next;
  }
}
