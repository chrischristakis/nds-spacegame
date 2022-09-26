#ifndef STARS_H
#define STARS_H
#include <nds.h>

const int STAR_COUNT = 20;
const int SPACE_COL = RGB15(0, 1, 4);

struct Star {
  int x;
  int y;
  int speed;
  int colour;
};

// We need the extern here so we dont define it here, but declare it.
extern Star stars[STAR_COUNT];

void initStars();
void updateStars();

void initStar(Star* star, int xStart);
#endif
