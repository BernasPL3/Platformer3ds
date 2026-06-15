#include "enemy.h"

Enemy::Enemy(float startX, float startY) {
    x = startX;
    y = startY;

    speed = 1.0f;

    leftLimit = startX - 40.0f;
    rightLimit = startX + 40.0f;
}

void Enemy::Update() {
    x += speed;

    if (x <= leftLimit || x >= rightLimit) {
        speed = -speed;
    }
}

void Enemy::Draw() {
    C2D_DrawRectSolid(
        x,
        y,
        0.0f,
        20.0f,
        20.0f,
        C2D_Color32(255, 255, 0, 255)
    );
}
