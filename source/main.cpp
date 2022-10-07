#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "stars.h"

#include "player.h"
#include "barrelmanager.h"

int frames = 0;

// --- TEMP --- //
Player *player = nullptr;
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

// Resets game state to the beginning.
void reset() {
  resetStars();
  player->reset();
  resetBarrels();
}

int main() {
  irqSet(IRQ_VBLANK, VBlank);  // Call VBlank function on each VBlank (frame)

  // Use a 1D mapping scheme in the OAM
  oamInit(&oamMain, SpriteMapping_1D_32, false);

  initVideo();
  initStars();
  initBarrels();

  player = new Player {0, 32};

  while(1) {
    swiWaitForVBlank();  // Wait until a VBlank to proceed
    scanKeys();  // Update NDS input

    printf("\x1b[2J"); //Clear terminal
    if(!(player->alive))
      printf("\n\nYou died!! Press enter to restart.");

    // Handle key input by checking bits against flgas (Like KEY_START)
    int keys = keysHeld();
    if(keys & KEY_START && !(player->alive))
      reset();

    player->update();
    updateStars();
    updateBarrels(player);

    player->draw();
    drawBarrels();

    oamUpdate(&oamMain);
  }

  return 0;
}
