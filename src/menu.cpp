#include "menu.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

extern int selectedOption;
int width1 = 480;
 int height1 = 720;

void menuLoop(SDL_Texture* backgroundTexture, Mix_Music* menusound, Mix_Chunk* choosesoundEffect) {
    SDL_Event e;
    bool running = true;
    Mix_PlayMusic(menusound, -1);
    SDL_Texture* butstartTexture = IMG_LoadTexture(renderer, "assets/buttonstart.png");
    if (!butstartTexture) {
        std::cerr << "Failed to load buttonstart texture: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* butexitTexture = IMG_LoadTexture(renderer, "assets/buttonexit.png");
    if (!butexitTexture) {
        std::cerr << "Failed to load buttonexit texture: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(butstartTexture);
        return;
    }

    SDL_Texture* butstartTextureHighlight = IMG_LoadTexture(renderer, "assets/choose1.png");
    if (!butstartTextureHighlight) {
        std::cerr << "Failed to load buttonstart highlight texture: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(butstartTexture);
        SDL_DestroyTexture(butexitTexture);
        return;
    }

    SDL_Texture* butexitTextureHighlight = IMG_LoadTexture(renderer, "assets/choose3.png");
    if (!butexitTextureHighlight) {
        std::cerr << "Failed to load buttonexit highlight texture: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(butstartTexture);
        SDL_DestroyTexture(butexitTexture);
        SDL_DestroyTexture(butstartTextureHighlight);
        return;
    }
    int selectedOption = 0;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                Mix_PlayChannel(-1, choosesoundEffect, 0);
                if (e.key.keysym.sym == SDLK_UP) selectedOption = (selectedOption - 1 + 2) % 2;
                if (e.key.keysym.sym == SDLK_DOWN) selectedOption = (selectedOption + 1) % 2;
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (selectedOption == 0) {
                        Mix_HaltMusic();
                        running = false;
                    } else if (selectedOption == 1) {
                        running = false; 
                    }
                }
            }
        }
    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        int buttonWidth = 200;
        SDL_Rect butstartRect = {width1/ 2 - buttonWidth / 2, 250, buttonWidth, 50};
        SDL_Rect butexitRect = {width1 / 2 - buttonWidth / 2, 350, buttonWidth, 50};

        SDL_Texture* startTexture = (selectedOption == 0) ? butstartTextureHighlight : butstartTexture;
        SDL_Texture* exitTexture = (selectedOption == 1) ? butexitTextureHighlight : butexitTexture;

        SDL_RenderCopy(renderer, startTexture, NULL, &butstartRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &butexitRect);

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyTexture(butstartTexture);
    SDL_DestroyTexture(butexitTexture);
    SDL_DestroyTexture(butstartTextureHighlight);
    SDL_DestroyTexture(butexitTextureHighlight);
}
