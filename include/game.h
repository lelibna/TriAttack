#ifndef GAME_H
#define GAME_H

#include "healthbar.h"
#include "enemies.h"
#include "bullets.h"
#include "sound.h"

void checkElimination(BulletState *bullets, EnemyState *enemies, HealthState *health, SoundState *sound, ScoreState *score);
void initScore(ScoreState *score);
#endif