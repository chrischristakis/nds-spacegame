#include <nds.h>
#include "player.h"
#include "ship.h"

Player::Player(int x, int y) : x(x), y(y) {
  alive = true;
  startX = x;
  startY = y;
  width = 32;
  height = 32;
  sprite = initSprite(SpriteSize_32x32, x, y, shipTiles, shipTilesLen,
                          shipPal, shipPalLen);
}

Player::~Player() {
  delete sprite;
}

void Player::updateSprite() {
  sprite->x = x;
  sprite->y = y;
}

void Player::reset() {
  x = startX;
  y = startY;
  updateSprite();
  alive = true;
}

void Player::draw() {
  updateSprite();
  drawSprite(sprite);
}

void Player::update() {
  int keys = keysHeld();

  int oldY = y;
  if(alive) {
    if(keys & KEY_UP)
      y-=5;
    if(keys & KEY_DOWN)
      y+=5;
  }

  // Vertical bounds
  if(y + height > SCREEN_HEIGHT || y < 0)
    y = oldY;
}
