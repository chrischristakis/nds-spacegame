#ifndef BARRELMANAGER_H
#define BARRELMANAGER_H
#include "barrel.h"
#include "player.h"
#include "sprite.h"

struct Barrel {
  int x;
  int y;
  int speed;
  int angle;
  Sprite* sprite;
};

const int MAX_BARRELS = 5;
const int BARREL_WIDTH = 32, BARREL_HEIGHT = 32;
extern Barrel* barrels[MAX_BARRELS];

void initBarrels();
void updateBarrels(Player *player);
void drawBarrels();
void resetBarrels();

#endif
