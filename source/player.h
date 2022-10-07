#ifndef PLAYER_H
#define PLAYER_H
#include "sprite.h"

class Player {
private:
  int startX;
  int startY;
public:
    int x;
    int y;
    int width;
    int height;
    Sprite* sprite;
    bool alive;

    Player(int x, int y);
    ~Player();

    void draw();
    void update();
    void reset();
    void updateSprite();
};

#endif
