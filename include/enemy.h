#ifndef ENEMY_H
#define ENEMY_H

#include <citro2d.h>

class Enemy {
public:
    float x;
    float y;
    float speed;
    float leftLimit;
    float rightLimit;

    Enemy(float startX, float startY);

    void Update();
    void Draw();
};

#endif
