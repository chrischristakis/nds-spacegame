#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "stars.h"

int frames = 0;

void VBlank() {
  frames++;
}

void initVideo() {

  consoleDemoInit();  // Bottom screen will just display text.

  //Initialize our starfield video mode and bank
  videoSetMode(MODE_FB0);      // Allows us to draw directly to the LCD
  vramSetBankA(VRAM_A_LCD);
}

int main() {
  irqSet(IRQ_VBLANK, VBlank);  // Call VBlank function on each VBlank (frame)

  initVideo();
  initStars();

  while(1) {
    swiWaitForVBlank();
    scanKeys();
    printf("\x1b[2J"); //Clear terminal
    printf("\nFrame = %d\n", frames);
    printf("RAND_MAX: %d", RAND_MAX);

    updateStars();
  }

  return 0;
}
