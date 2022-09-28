#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "stars.h"
#include "ship.h"
#include "barrel.h"
#include "fracas.h"

int frames = 0;

// --- TEMP --- //
Sprite *s1 = nullptr;
Sprite *s2 = nullptr;
Sprite *tl, *tr, *bl, *br;
// ------------ //

void VBlank() { frames++; }

void initVideo() {

  consoleDemoInit();  // Bottom screen will just display text (Occupies VRAM C)

  videoSetMode(MODE_5_2D |
              DISPLAY_BG2_ACTIVE |
              DISPLAY_SPR_ACTIVE |
              DISPLAY_SPR_1D);

  //Set up VRAM A for our starfield background
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

  // Initialize Bank B for use for sprites
  vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
}

void initSprites() {
  // Set up the OAM for use with a 32 byte boundary
  oamInit(&oamMain, SpriteMapping_1D_32, false);

  s1 = initSprite(SpriteSize_32x32, 0, 0, shipTiles, shipTilesLen,
                          shipPal, shipPalLen);

  s2 = initSprite(SpriteSize_32x32, 32, 0, barrelTiles, barrelTilesLen,
                          barrelPal, barrelPalLen);

  //FRACAS SEGMENTS (Its a 2048 len array, hence 2048/4 = 512)
  tl = initSprite(SpriteSize_64x64, 64, 0, fracasTiles+512*0, fracasTilesLen/4,
                          fracasPal, fracasPalLen);

  tr = initSprite(SpriteSize_64x64, 128, 0, fracasTiles+512*1, fracasTilesLen/4,
                          tl->id);

  bl = initSprite(SpriteSize_64x64, 64, 64, fracasTiles+512*2, fracasTilesLen/4,
                          tl->id);

  br = initSprite(SpriteSize_64x64, 128, 64, fracasTiles+512*3, fracasTilesLen/4,
                          tl->id);
}

// Resets game state to the beginning.
void reset() {
  resetStars();
}

int main() {
  irqSet(IRQ_VBLANK, VBlank);  // Call VBlank function on each VBlank (frame)

  initVideo();
  initSprites();
  initStars();

  while(1) {
    swiWaitForVBlank();  // Wait until a VBlank to proceed
    scanKeys();  // Update NDS input

    printf("\x1b[2J"); //Clear terminal
    printf("\nFrame = %d\n", frames);
    printf("S1 ID: %d\n", s1->id);
    printf("S2 ID: %d\n", s2->id);

    // Handle key input by checking bits against flgas (Like KEY_START)
    int keys = keysHeld();
    if(keys & KEY_START)
      reset();

    s2->angle = frames * 100 % 32768;

    drawSprite(s1);
    drawSprite(s2);

    drawSprite(tl);
    drawSprite(tr);
    drawSprite(bl);
    drawSprite(br);

    updateStars();
    oamUpdate(&oamMain);
  }

  return 0;
}
