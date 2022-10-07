#include "barrelmanager.h"

Barrel* barrels[MAX_BARRELS];

void initBarrels() {
  //Used as our sprite base.
  Sprite* barrelSprite = initSprite(SpriteSize_32x32, 0, 0, barrelTiles, barrelTilesLen,
                          barrelPal, barrelPalLen);
  for(int i = 0; i < MAX_BARRELS; i++) {
    Barrel* b = new Barrel { SCREEN_WIDTH, rand() % SCREEN_HEIGHT,
                              rand() % 2 + 1, rand() % 32768, nullptr };
    barrels[i] = b;
    barrels[i]->sprite = duplicate(barrelSprite, 32*i, 32);
    barrels[i]->sprite->priority = OBJPRIORITY_0;
  }
}

void resetBarrels() {
  for(int i = 0; i < MAX_BARRELS; i++) {
    barrels[i]->x = SCREEN_WIDTH;
    barrels[i]->y = rand() % SCREEN_HEIGHT;
    barrels[i]->speed = rand() % 2 + 1;
  }
}

void updateBarrels(Player *player) {
  for(int i = 0; i < MAX_BARRELS; i++) {
    barrels[i]->x -= barrels[i]->speed;

    // Check if barrel collides with player
    Barrel *b = barrels[i];
    int leeway = 10;
    if(player->x+ player->width >= b->x && player->x <= b->x + BARREL_WIDTH &&
       player->y + player->height-leeway >= b->y && player->y+leeway <= b->y + BARREL_HEIGHT)
       player->alive = false;

    if(barrels[i]->x + BARREL_WIDTH < 0) {
      barrels[i]->x = SCREEN_WIDTH;
      barrels[i]->y = rand() % SCREEN_HEIGHT;
      barrels[i]->speed = rand() % 2 + 1;
    }
  }
}

void drawBarrels() {
  for(int i = 0; i < MAX_BARRELS; i++)
    if(barrels[i]) {
      barrels[i]->sprite->x = barrels[i]->x;
      barrels[i]->sprite->y = barrels[i]->y;
      barrels[i]->angle = (barrels[i]->angle + 100) % 32768;
      barrels[i]->sprite->angle = barrels[i]->angle;

      drawSprite(barrels[i]->sprite);
    }
}
