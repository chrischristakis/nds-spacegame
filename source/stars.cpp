#include "stars.h"

Star stars[STAR_COUNT];  // Actual definition goes here.

void initStar(Star* star, int xStart) {
  star->x = xStart;
  star->y = rand() % SCREEN_HEIGHT;
  star->speed = ((rand() % 4) + 1) * -1;
  star->colour = RGB15(31, 31, (int)(31 * (rand()/(float)RAND_MAX)));
}

void initStars() {
  // Set starfield background to a solid colour.
  for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++) {
    VRAM_A[i] = SPACE_COL;
  }

  // Now, we initialize the stars all across the screen
  for(int i = 0; i < STAR_COUNT; i++) {
    initStar(&stars[i], rand() % SCREEN_WIDTH);
  }
}

void updateStars() {
  for(int i = 0; i < STAR_COUNT; i++) {
    // 'Erase' the star
    VRAM_A[stars[i].x + stars[i].y * SCREEN_WIDTH] = SPACE_COL;

    stars[i].x += stars[i].speed;
    if(stars[i].x < 0)
      initStar(&stars[i], SCREEN_WIDTH);  // Reset to the right of the screen

    // Now, redraw it.
    VRAM_A[stars[i].x + stars[i].y * SCREEN_WIDTH] = stars[i].colour;
  }
}
