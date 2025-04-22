#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "brick.h"

void handleBallBrickCollision(
    float& ballX, float& ballY,
    float& ballVelX, float& ballVelY,
    float deltaTime,
    float radius,
    std::vector<Brick>& bricks,
    Mix_Chunk* hitsoundEffect
);

#endif
