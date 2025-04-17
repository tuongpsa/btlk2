#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

extern SDL_Renderer* renderer;

void menuLoop(SDL_Texture* backgroundTexture, Mix_Music* menusound, Mix_Chunk* choosesoundEffect);

#endif
