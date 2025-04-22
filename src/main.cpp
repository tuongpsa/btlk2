#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../header/brick.h"
#include "../header/menu.h"
#include "../header/varball+bar.h"
#include "../header/win_screen.h"
#include "../header/gameover_screen.h"
#include "../header/levelup_effect.h"
#include "../header/collision.h"
#include "../header/resources.h"
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool quit = false;
int main() {
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    if (!loadResources(renderer, leveltmp)) {
        SDL_Log("Failed to load game resources!");
        return -1;
    }
    menuLoop( backgroundTexture, menuMusic, choosesoundEffect);
    Mix_PlayMusic(gameMusic, -1);
    taogach();
    SDL_Event e;
    Uint32 lastTime = SDL_GetTicks();
    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; 
        lastTime = currentTime;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        if (isAllBricksDestroyed()) {
            maxbrick += 5;
            level ++;
            leveltmp++;
            if(leveltmp>8){
                leveltmp=1;
        }
            if (level > 14) {
            showWinScreen(renderer, font, backgroundTexture, width, height);
        }
            speed += 40;
            taogach(); 
            ballX = toadogocX; 
            ballY = toadogocY;
            ballVelX = 0;
            ballVelY = 0;
            barX = (width - barWidth) / 2; 
            barY = height - 20;
            SDL_Color textColor = {255, 0, 0, 255};  
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(brickTexture);
    std::string path = "assets/back" + std::to_string(leveltmp) + ".png";
    backgroundTexture = IMG_LoadTexture(renderer, path.c_str());
    brickTexture = IMG_LoadTexture(renderer, "assets/br3.png");
    renderBricks(renderer, brickTexture);
    SDL_Color color = {255, 0, 0, 255};
    showLevelUpEffect(renderer, font, backgroundTexture, paddleTexture, ballTexture,
        barX, barY, barWidth, barHeight, ballX, ballY, radius, color);

            lastTime = SDL_GetTicks(); 
            ballVelX = (rand() % 2 == 0 ? -1 : 1) * speed;  
            ballVelY = -speed;
        }
        SDL_RenderClear(renderer);
        checkBrickCollisions(ballX, ballY, radius, ballVelX, ballVelY);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            barX -= 700.f * deltaTime;
            if (barX < 0) barX = 0; 
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            barX += 700.f * deltaTime;
            if (barX + barWidth > width) barX = width - barWidth; 
        }
        handleBallBrickCollision(ballX, ballY, ballVelX, ballVelY,
            deltaTime, radius, bricks, hitsoundEffect);
        if (ballX <= 0) {
            ballVelX = -ballVelX; 
            ballX = 0; 
        }
        if (ballX + radius * 2 >= width) {
            ballVelX = -ballVelX; 
            ballX = width - radius * 2; 
        }
        if (ballY <= 0) {
            ballVelY = -ballVelY;
            ballY = 0;
        }

        
        if (ballY + radius * 2 >= barY && ballY + radius <= barY + barHeight && ballX + radius * 2 > barX && ballX < barX + barWidth) {
            if (ballVelY > 0) {  
                Mix_PlayChannel(-1, popsoundEffect, 0);
                ballVelY = -ballVelY;  
            }
        }
        
        if (ballY + radius * 2 >= height) {
               showGameOverScreen(renderer, font, backgroundTexture,
                gameoverMusic, gameMusic,
                width, height,
                barX, barY, barWidth,
                ballX, ballY, ballVelX, ballVelY,
                speed,
                toadogocX, toadogocY,
                lastTime,
                quit);

            }
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        renderBricks(renderer, brickTexture);
        int textW, textH;
SDL_Color textColor = {255, 255, 255, 255};  
std::string levelText = "Level: " + std::to_string(level);
TTF_SizeText(font, levelText.c_str(), &textW, &textH);
SDL_Rect levelRect = {10, 10, textW, textH};  
SDL_Texture* levelMessage = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, levelText.c_str(), textColor));
SDL_RenderCopy(renderer, levelMessage, NULL, &levelRect);
SDL_DestroyTexture(levelMessage);

        SDL_Rect ballRect = { (int)ballX, (int)ballY,(int) radius * 2,(int) radius * 2 };
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
        SDL_Rect paddleRect = { (int)barX, (int)barY, (int)barWidth, (int)barHeight };
        SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);
        SDL_RenderPresent(renderer);
    }
    freeResources();
    SDL_Quit();
    std::cout<<"Quited";
    return 0;
}