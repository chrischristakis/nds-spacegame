#ifndef SPRITE_H
#define SPRITE_H
#include <nds.h>

struct Sprite {
  int id;
  int x;
  int y;
  int angle;
  u16* oamPtr;
  SpriteSize size;
  ObjPriority priority = OBJPRIORITY_0;
};

void drawSprite(Sprite* sprite);
Sprite* initSprite(SpriteSize size, int x, int y, const unsigned int* tiles,
int tilesLen, const unsigned short* palette, int paletteLen);

#endif
