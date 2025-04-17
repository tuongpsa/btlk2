#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>
#include <vector>

struct Brick {
    float x, y;
    int hp;
    bool isDestroyed;
    SDL_Rect rect;
};

extern std::vector<Brick> bricks;  
extern int maxbrick;              

void taogach();  
void checkBrickCollisions(float& ballX, float& ballY, float radius, float& ballVelX, float& ballVelY); 
bool isAllBricksDestroyed();
void renderBricks(SDL_Renderer* renderer, SDL_Texture* brickTexture);

#endif 
