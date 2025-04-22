#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <SDL2/SDL.h>

#include <SDL2/SDL_ttf.h>

void showWinScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* backgroundTexture, int width, int height);

#endif
