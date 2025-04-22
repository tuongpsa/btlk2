#include "gameover_screen.h"

int showGameOverScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* backgroundTexture,
    Mix_Music* gameoverMusic, Mix_Music* gameMusic,
    int width, int height,
    float& barX, float& barY, int barWidth,
    float& ballX, float& ballY, float& ballVelX, float& ballVelY,
    float speed,
    float toadogocX, float toadogocY,
    Uint32& lastTime,
    bool& quit) {

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    int textW, textH;
    SDL_Color textColor = {255, 255, 255, 255}; 

    Mix_PlayMusic(gameoverMusic, -1);

    TTF_SizeText(font, "GAME OVER!", &textW, &textH);
    SDL_Rect messageRect1 = {width / 2 - textW / 2, height / 3 - textH / 2, textW, textH};
    SDL_Surface* surface1 = TTF_RenderText_Solid(font, "GAME OVER!", textColor);
    SDL_Texture* message1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);
    SDL_RenderCopy(renderer, message1, NULL, &messageRect1);
    SDL_DestroyTexture(message1);

    TTF_SizeText(font, "Press any key to restart", &textW, &textH);
    SDL_Rect messageRect2 = {width / 2 - textW / 2, height / 2 - textH / 2, textW, textH};
    SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Press any key to restart", textColor);
    SDL_Texture* message2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    SDL_RenderCopy(renderer, message2, NULL, &messageRect2);
    SDL_DestroyTexture(message2);

    TTF_SizeText(font, "Press ESC to quit", &textW, &textH);
    SDL_Rect messageRect3 = {width / 2 - textW / 2, height * 2 / 3 - textH / 2, textW, textH};
    SDL_Surface* surface3 = TTF_RenderText_Solid(font, "Press ESC to quit", textColor);
    SDL_Texture* message3 = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_FreeSurface(surface3);
    SDL_RenderCopy(renderer, message3, NULL, &messageRect3);
    SDL_DestroyTexture(message3);

    SDL_RenderPresent(renderer);
    SDL_Delay(500);

    int response = -1;
    bool waitingForInput = true;
    while (waitingForInput) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                response = 1;
                waitingForInput = false;
            }
            if (ev.type == SDL_KEYDOWN) {
                SDL_Keycode key = ev.key.keysym.sym;
                Mix_HaltMusic();
                if (key == SDLK_ESCAPE) {
                    response = 1;
                } else {
                    response = 0;
                }
                waitingForInput = false;
            }
        }
    }

    if (response == 0) {
        Mix_PlayMusic(gameMusic, -1);
        barX = (width - barWidth) / 2;
        barY = height - 20;
        ballX = toadogocX;
        ballY = toadogocY;
        ballVelX = speed;
        ballVelY = -speed;
        bricks.clear();
        taogach();
        lastTime = SDL_GetTicks();
    } 
    else {
        quit = true;
    }
    return response;
}
