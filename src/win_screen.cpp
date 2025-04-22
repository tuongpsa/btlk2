#include "win_screen.h"
#include <cstdlib>

void showWinScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* backgroundTexture, int width, int height) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    int textW, textH;
    SDL_Color textColor = {255, 255, 255, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU WIN!", textColor);
    SDL_Texture* message1 = SDL_CreateTextureFromSurface(renderer, textSurface);
    TTF_SizeText(font, "YOU WIN!", &textW, &textH);
    SDL_Rect messageRect1 = {width / 2 - textW / 2, height / 3 - textH / 2, textW, textH};
    SDL_RenderCopy(renderer, message1, NULL, &messageRect1);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(message1);
    SDL_Delay(2000);
    exit(0);
}
