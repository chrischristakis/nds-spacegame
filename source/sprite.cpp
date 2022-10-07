#include "sprite.h"

static int GLOBAL_ID = 0;

void drawSprite(Sprite* sprite) {
  // We're using sprite id as our rotation id because it's convenient
  oamRotateScale(&oamMain, sprite->id, sprite->angle, (sprite->scale << 8),
                 (sprite->scale << 8));

  oamSet(&oamMain,
      sprite->id, // the oam entry to set
      sprite->x, sprite->y, // where should be positioned (x,y)?
      sprite->priority, // priority
      sprite->paletteId, // palette id
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

// For when we just want to duplicate an existing sprite without allocating
// More memory in vram, saves us space.
Sprite* duplicate(Sprite* source, int x, int y) {
  Sprite* sprite = new Sprite {};

  // Shallow copy is ok since we actually want to keep the same location in
  // memory for the sprite when duplicated.
  memcpy(sprite, source, sizeof(*source));

  // ... But we need to make the ID unique for oamSet to work. Otherwise we
  // just overwrite the source sprite when rednering
  sprite->id = GLOBAL_ID++;
  sprite->x = x;
  sprite->y = y;

  return sprite;
}

Sprite* initSprite(SpriteSize size, int x, int y, const unsigned int* tiles,
                int tilesLen, const unsigned short* palette, int paletteLen) {

  Sprite* sprite = new Sprite{ GLOBAL_ID, GLOBAL_ID, x, y, 0, nullptr, size, 1 };
  GLOBAL_ID++;

  u16* gfx = oamAllocateGfx(&oamMain, size, SpriteColorFormat_16Color);
  sprite->oamPtr = gfx;

  const int COLORS_PER_PALETTE = 16;

  dmaCopy(tiles, gfx, tilesLen);
  dmaCopy(palette, &SPRITE_PALETTE[sprite->id * COLORS_PER_PALETTE], paletteLen);
  // If sprites shared the same palette, we'd use a unique palette id here.
  // But we're not so share sprite id with palette id (And affine id!)

  return sprite;
}

// Same as init sprite, but for when we already have a palette and don't
// need to make a new one.
Sprite* initSprite(SpriteSize size, int x, int y, const unsigned int* tiles,
  int tilesLen, int paletteId) {
  Sprite* sprite = new Sprite{ GLOBAL_ID++, paletteId, x, y, 0, nullptr, size, 1 };

  u16* gfx = oamAllocateGfx(&oamMain, size, SpriteColorFormat_16Color);
  sprite->oamPtr = gfx;

  dmaCopy(tiles, gfx, tilesLen);

  return sprite;
}
