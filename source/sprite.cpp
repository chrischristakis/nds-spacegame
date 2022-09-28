#include "sprite.h"

static int GLOBAL_ID = 0;

int rot = 0;
void drawSprite(Sprite* sprite) {
  rot++;
  oamRotateScale(&oamMain, sprite->id, sprite->angle, intToFixed(1, 8),
                 intToFixed(1, 8));

  oamSet(&oamMain, //is it upper screen of bottom?
      sprite->id, // the oam entry to set
      sprite->x, sprite->y, // where should be positioned (x,y)?
      sprite-> priority, // priority
      sprite->id, // palette id (we'll just use our sprite id)
      sprite->size,
      SpriteColorFormat_16Color, // color type
      sprite->oamPtr,
      sprite->id, //affine index (we'll just use our sprite id)
      false, // Double the size of rotated sprites
      false, // Visiblility
      false, false, // vflip, hflip
      false // mosaic
      );
}

Sprite* initSprite(SpriteSize size, int x, int y, const unsigned int* tiles,
                int tilesLen, const unsigned short* palette, int paletteLen) {

  Sprite* sprite = new Sprite{ GLOBAL_ID++, x, y, 0, nullptr, size };

  u16* gfx = oamAllocateGfx(&oamMain, size, SpriteColorFormat_16Color);
  sprite->oamPtr = gfx;

  const int COLORS_PER_PALETTE = 16;

  dmaCopy(tiles, gfx, tilesLen);
  dmaCopy(palette, &SPRITE_PALETTE[sprite->id * COLORS_PER_PALETTE], paletteLen);
  // If sprites shared the same palette, we'd use a unique palette id here.
  // But we're not so share sprite id with palette id (And affine id!)

  return sprite;
}
