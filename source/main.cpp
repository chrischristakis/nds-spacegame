#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "stars.h"
#include "ship.h"

int frames = 0;

void VBlank() {
  frames++;
}

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

// Resets game state to the beginning.
void reset() {
  resetStars();
}

int main() {
  irqSet(IRQ_VBLANK, VBlank);  // Call VBlank function on each VBlank (frame)

  initVideo();
  initStars();

  oamInit(&oamMain, SpriteMapping_1D_128, false);
  u16* gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
  dmaCopy(shipTiles, gfx, shipTilesLen);

  const int COLORS_PER_PALETTE = 16;
  const int shipId = 0;
  dmaCopy(shipPal, &SPRITE_PALETTE[shipId * COLORS_PER_PALETTE], shipPalLen);

  oamSet(&oamMain, //is it upper screen of bottom?
  		shipId, // the oam entry to set
  		0, 0, // where should be positioned (x,y)?
  		0, // priority
  		OBJPRIORITY_0, // palette for 16 color sprite or alpha for bmp sprite
  		SpriteSize_32x32, // size
  		SpriteColorFormat_16Color, // color type
  		gfx, // the oam gfx
  		0, //affine index
  		false, //double the size of rotated sprites
  		false, //don't hide the sprite
  		false, false, //vflip, hflip
  		false //apply mosaic
  		);

  while(1) {
    swiWaitForVBlank();
    scanKeys();

    // Handle key input
    int keys = keysHeld();
    if(keys & KEY_START)
      reset();

    printf("\x1b[2J"); //Clear terminal
    printf("\nFrame = %d\n", frames);
    printf("RAND_MAX: %d", RAND_MAX);

    updateStars();

    oamUpdate(&oamMain);
  }

  return 0;
}
