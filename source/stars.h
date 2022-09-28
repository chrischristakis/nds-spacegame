#ifndef STARS_H
#define STARS_H
#include <nds.h>

const int STAR_COUNT = 20;
const int SPACE_COL = RGB15(0, 1, 4) | 1 << 15;
// The 16th bit is for the transparency, it must be 1 or it's transparent ^

struct Star {
  int x;
  int y;
  int speed;
  int colour;
};

// We need the extern here so we dont define it here, but declare it.
// Otherwise we'd redefine it each time we include the header.
extern Star stars[STAR_COUNT];

void initStars();
void updateStars();
void resetStars();

#endif
