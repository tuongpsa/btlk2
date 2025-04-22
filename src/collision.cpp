#include "collision.h"

void handleBallBrickCollision(
    float& ballX, float& ballY,
    float& ballVelX, float& ballVelY,
    float deltaTime,
    float radius,
    std::vector<Brick>& bricks,
    Mix_Chunk* hitsoundEffect
) {
    float dx = ballVelX * deltaTime;
    float dy = ballVelY * deltaTime;
    float stepSize = radius / 4.0f;
    int steps = std::ceil(std::max(std::abs(dx), std::abs(dy)) / stepSize);
    if (steps < 1) steps = 1;

    float stepX = dx / steps;
    float stepY = dy / steps;

    for (int i = 0; i < steps; i++) {
        float nextX = ballX + stepX;
        float nextY = ballY + stepY;
        bool collisionX = false;
        bool collisionY = false;

        for (auto& brick : bricks) {
            if (!brick.isDestroyed) {
                bool hitX = nextX + radius * 2 > brick.x && nextX < brick.x + brick.rect.w;
                bool hitY = nextY + radius * 2 > brick.y && nextY < brick.y + brick.rect.h;

                if (hitX && hitY) {
                    brick.hp--;
                    if (brick.hp <= 0) {
                        Mix_PlayChannel(-1, hitsoundEffect, 0);
                        brick.isDestroyed = true;
                    }

                    float overlapLeft = std::abs((nextX + radius * 2) - brick.x);
                    float overlapRight = std::abs((brick.x + brick.rect.w) - nextX);
                    float overlapTop = std::abs((nextY + radius * 2) - brick.y);
                    float overlapBottom = std::abs((brick.y + brick.rect.h) - nextY);
                    float minHorizontal = std::min(overlapLeft, overlapRight);
                    float minVertical = std::min(overlapTop, overlapBottom);

                    if (minVertical < minHorizontal) {
                        ballVelY = -ballVelY;
                        collisionY = true;
                    } else {
                        ballVelX = -ballVelX;
                        collisionX = true;
                    }
                    break;
                }
            }
        }

        if (!collisionX) ballX = nextX;
        if (!collisionY) ballY = nextY;
    }
}
