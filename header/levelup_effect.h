#ifndef LEVELUP_EFFECT_H
#define LEVELUP_EFFECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "varball+bar.h"

void showLevelUpEffect(SDL_Renderer* renderer, TTF_Font* font,
                       SDL_Texture* backgroundTexture, SDL_Texture* paddleTexture, SDL_Texture* ballTexture,
                       float barX, float barY, float barWidth, float barHeight,
                       float ballX, float ballY, float radius,
                       SDL_Color textColor);

#endif
