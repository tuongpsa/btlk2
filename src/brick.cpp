#include "brick.h"
#include <cstdlib>
#include <varball+bar.h>

std::vector<Brick> bricks;  
int maxbrick = 5;           

void taogach() {
    float brickWidth = 60;
    float brickHeight = 20;
    bricks.clear();

    for (int i = 0; i < maxbrick; i++) {
        bool validPosition = false;
        Brick brick;

        while (!validPosition) {
            brick.x = 30 + rand() % (int)(480 - brickWidth - 60); // padding
            brick.y = 30 + rand() % (int)(720 / 2);
            brick.isDestroyed = false;
            brick.hp = 1 + rand() % 3;
            brick.rect = { (int)brick.x, (int)brick.y, (int)brickWidth, (int)brickHeight };

            validPosition = true;
            for (const auto& other : bricks) {
                if (SDL_HasIntersection(&brick.rect, &other.rect)) {
                    validPosition = false;
                    break;
                }
            }
        }

        bricks.push_back(brick);
    }
}

void checkBrickCollisions(float& ballX, float& ballY, float radius, float& ballVelX, float& ballVelY) {
    for (auto& brick : bricks) {
        if (!brick.isDestroyed) {
            if (ballX + radius * 2 > brick.x - 1 && ballX < brick.x + brick.rect.w - 1 &&
                ballY + radius * 2 > brick.y && ballY < brick.y + brick.rect.h) {
                brick.hp--;
                if (brick.hp <= 0) {
                    brick.isDestroyed = true;
                }
                ballVelY = -ballVelY;
            }
        }
    }
}
bool isAllBricksDestroyed() {
    for (const auto& brick : bricks) {
        if (brick.isDestroyed==false) {
            return false; 
        }
    }
    return true; 
}
void renderBricks(SDL_Renderer* renderer, SDL_Texture* brickTexture) {
    for (const auto& brick : bricks) {
        if (brick.isDestroyed==false) {
            SDL_Rect brickRect = { (int)brick.rect.x, (int)brick.rect.y, (int)brick.rect.w, (int)brick.rect.h };
            SDL_RenderCopy(renderer, brickTexture, NULL, &brickRect);
        }
    }
}
