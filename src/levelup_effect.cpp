#include "levelup_effect.h"

void showLevelUpEffect(SDL_Renderer* renderer, TTF_Font* font,
                       SDL_Texture* backgroundTexture, SDL_Texture* paddleTexture, SDL_Texture* ballTexture,
                       float barX, float barY, float barWidth, float barHeight,
                       float ballX, float ballY, float radius,
                       SDL_Color textColor)
{
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    int textW, textH;
    TTF_SizeText(font, "LEVEL UP!", &textW, &textH);
    SDL_Rect messageRect = {
        width / 2 - textW / 2,
        height / 2 - textH / 2 + 100,
        textW, textH
    };

    SDL_Surface* surface = TTF_RenderText_Solid(font, "LEVEL UP!", textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    for (int i = 0; i < 8; i++) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_Rect paddleRect = { (int)barX, (int)barY, (int)barWidth, (int)barHeight };
        SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);

        SDL_Rect ballRect = { (int)ballX, (int)ballY, (int)radius * 2, (int)radius * 2 };
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);

        if (i % 2 == 0) {
            SDL_RenderCopy(renderer, message, NULL, &messageRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(420);
    }

    SDL_DestroyTexture(message);
}
