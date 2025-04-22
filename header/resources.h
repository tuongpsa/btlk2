#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

bool loadResources(SDL_Renderer* renderer, int leveltmp);
void freeResources();

extern Mix_Music* menuMusic;
extern Mix_Music* gameMusic;
extern Mix_Music* gameoverMusic;
extern Mix_Chunk* hitsoundEffect;
extern Mix_Chunk* popsoundEffect;
extern Mix_Chunk* choosesoundEffect;
extern TTF_Font* font;
extern SDL_Texture* paddleTexture;
extern SDL_Texture* ballTexture;
extern SDL_Texture* brickTexture;
extern SDL_Texture* backgroundTexture;

#endif
