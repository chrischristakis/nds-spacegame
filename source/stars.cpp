#include "stars.h"

Star stars[STAR_COUNT];  // Actual definition goes here.
u16* bgGfx;

void initStar(Star* star, int xStart) {
  star->x = xStart;
  star->y = rand() % SCREEN_HEIGHT;
  star->speed = ((rand() % 4) + 1) * -1;
  star->colour = RGB15(31, 31, (int)(31 * (rand()/(float)RAND_MAX))) | 1 << 15;
}

void resetStars() {
  for(int i = 0; i < STAR_COUNT; i++) {
    bgGfx[stars[i].x + stars[i].y * SCREEN_WIDTH] = SPACE_COL;
    initStar(&stars[i], rand() % SCREEN_WIDTH);
  }
}

void initStars() {
  // Allocate memory for a background with a corresponding ID
  int bg = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
  bgSetPriority(bg, 2);
  bgGfx = (u16*)bgGetGfxPtr(bg);  // Pointer to bg allocation

  // Set bg to solid colour
  for(int y = 0; y < SCREEN_HEIGHT; y++)
     for(int x = 0; x < SCREEN_WIDTH; x++)
       bgGfx[x + y * SCREEN_WIDTH] = SPACE_COL;

  // Now, we initialize the stars all across the screen
  resetStars();
}

void updateStars() {
  for(int i = 0; i < STAR_COUNT; i++) {
    // 'Erase' the star
    bgGfx[stars[i].x + stars[i].y * SCREEN_WIDTH] = SPACE_COL;

    stars[i].x += stars[i].speed;
    if(stars[i].x < 0)
      initStar(&stars[i], SCREEN_WIDTH);  // Reset to the right of the screen

    bgGfx[stars[i].x + stars[i].y * SCREEN_WIDTH] = stars[i].colour;
  }
}
