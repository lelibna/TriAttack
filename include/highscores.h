#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#pragma once

void loadHighscores();
void saveHighscore(int profileIndex, int score);
int getHighscore(int profileIndex);
void highscores_update();
void highscores_draw();

#endif