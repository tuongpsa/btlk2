#ifndef GAMEOVER_SCREEN_H
#define GAMEOVER_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "brick.h"
#include "varball+bar.h"
extern bool quit;
    
extern std::vector<Brick> bricks;

int showGameOverScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* backgroundTexture,
    Mix_Music* gameoverMusic, Mix_Music* gameMusic,
    int width, int height,
    float& barX, float& barY, int barWidth,
    float& ballX, float& ballY, float& ballVelX, float& ballVelY,
    float speed,
    float toadogocX, float toadogocY,
    Uint32& lastTime,
    bool& quit);





#endif
