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

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    float height = 720;
float width = 480;
float radius = 10;
float speed = 400.f;  
float ballVelX = speed; 
float ballVelY = -speed;
float toadogocX = (width / 2) - radius;
float toadogocY = height - 15.01 - (2 * radius);
SDL_Color textColor = {255, 0, 0, 255};
void renderText(const char* text, int x, int y, SDL_Color color, bool isSelected) {
    SDL_Color highlightColor = {255, 255, 0, 255}; 
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, isSelected ? highlightColor : color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

   
    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_Rect textRect = {x - textWidth / 2, y - textHeight / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, texture, NULL, &textRect); 
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int selectedOption = 0;
void menuLoop(SDL_Texture* backgroundTexture, Mix_Music* menusound, Mix_Chunk* choosesoundEffect) {
    SDL_Event e;
    bool running = true;
    Mix_PlayMusic(menusound, -1);


    SDL_Texture* butstartTexture = IMG_LoadTexture(renderer, "assets/buttonstart.png");
    SDL_Texture* butexitTexture = IMG_LoadTexture(renderer, "assets/buttonexit.png");
    SDL_Texture* butoptionsTexture = IMG_LoadTexture(renderer, "assets/buttonoptions.png");
    SDL_Texture* butstartTextureHighlight = IMG_LoadTexture(renderer, "assets/choose1.png");
    SDL_Texture* butexitTextureHighlight = IMG_LoadTexture(renderer, "assets/choose3.png");
    //SDL_Texture* butoptionsTextureHighlight = IMG_LoadTexture(renderer, "assets/choose2.png");

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
                    } /*else if (selectedOption == 1) {
                        std::cout << "Options" << std::endl;
                    }*/
                    else if (selectedOption == 1) {
                        
                        exit(0);
                    }
                }
            }
        }
    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        int buttonWidth = 200;
        SDL_Rect butstartRect = {width / 2 - buttonWidth / 2, 250, buttonWidth, 50};
        //SDL_Rect butoptionsRect = {width / 2 - buttonWidth / 2, 350, buttonWidth, 50};
        SDL_Rect butexitRect = {width / 2 - buttonWidth / 2, 350, buttonWidth, 50};

    
        SDL_Texture* startTexture = (selectedOption == 0) ? butstartTextureHighlight : butstartTexture;
        SDL_Texture* exitTexture = (selectedOption == 1) ? butexitTextureHighlight : butexitTexture;
        //SDL_Texture* optionsTexture = (selectedOption == 1) ? butoptionsTextureHighlight : butoptionsTexture;
    
        SDL_RenderCopy(renderer, startTexture, NULL, &butstartRect);
       // SDL_RenderCopy(renderer, optionsTexture, NULL, &butoptionsRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &butexitRect);

    
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(butstartTexture);
    SDL_DestroyTexture(butexitTexture);
    SDL_DestroyTexture(butoptionsTexture);
    SDL_DestroyTexture(butstartTextureHighlight);
    SDL_DestroyTexture(butexitTextureHighlight);
    //SDL_DestroyTexture(butoptionsTextureHighlight);
}


int maxbrick = 5;
int level = 1;
int leveltmp=1;
struct Brick {
    float x, y;
    int hp;
    bool isDestroyed;
    SDL_Rect rect;
};
std::vector<Brick> bricks;

void taogach() {
    float brickWidth = 60;
    float brickHeight = 20;
    bricks.clear();

    for (int i = 0; i < maxbrick; i++) {
        bool validPosition = false;
        Brick brick;

        while (!validPosition) {
            brick.x = 30 + rand() % (int)(480 - brickWidth - 30 - 30);
            brick.y = 30 + rand() % (int)(720 / 2);
            brick.isDestroyed = false;
            brick.hp = 1 + rand() % 3;
            brick.rect = { (int)brick.x, (int)brick.y, (int)brickWidth, (int)brickHeight };

            validPosition = true;

            
            for (const auto& other : bricks) {
                if (SDL_HasIntersection(&brick.rect, &other.rect)) {
                    validPosition = false; 
                    break;
                }
            }
        }

        bricks.push_back(brick);
    }
}

    
void renderBricks(SDL_Renderer* renderer, SDL_Texture* brickTexture) {
    for (const auto& brick : bricks) {
        if (brick.isDestroyed==false) {
            SDL_Rect brickRect = { (int)brick.rect.x, (int)brick.rect.y, (int)brick.rect.w, (int)brick.rect.h };
            SDL_RenderCopy(renderer, brickTexture, NULL, &brickRect);
        }
    }
}
void checkBrickCollisions(float& ballX, float& ballY, float radius, float& ballVelX, float& ballVelY) {
    for (auto& brick : bricks) {
        if (brick.isDestroyed==false) {
            if (ballX + radius * 2 > brick.x-1 && ballX < brick.x + brick.rect.w-1 &&
                ballY + radius * 2 > brick.y && ballY < brick.y + brick.rect.h) {
                brick.hp--;
                if(brick.hp <=0){
                    brick.isDestroyed = true;
                    
                        
                    
                }
                ballVelY = -ballVelY;
            }
        }
    }
}
bool isAllBricksDestroyed() {
    for (const auto& brick : bricks) {
        if (brick.isDestroyed==false) {
            return false; 
        }
    }
    
    
    return true; 
}



int main() {
    
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(64);
    Mix_Music* menuMusic = Mix_LoadMUS("assets/menusound.mp3");
    Mix_Music* gameMusic = Mix_LoadMUS("assets/theme.mp3");
    Mix_Music* gameoverMusic = Mix_LoadMUS("assets/gameoversound.mp3");
    Mix_Chunk* hitsoundEffect = Mix_LoadWAV("assets/hitsound.wav");
    Mix_Chunk* popsoundEffect = Mix_LoadWAV("assets/pop.wav");
    Mix_Chunk* choosesoundEffect = Mix_LoadWAV("assets/choosesound.wav");

    bool quit = false;
    SDL_Event e;
    TTF_Init();
    font = TTF_OpenFont("PixelGame.otf", 40);
    
    
SDL_Texture* paddleTexture = IMG_LoadTexture(renderer, "assets/thanh1.png");
SDL_Texture* ballTexture = IMG_LoadTexture(renderer, "assets/pig.png");
SDL_Texture* brickTexture = IMG_LoadTexture(renderer, "assets/br3.png");
std::string path = "assets/back" + std::to_string(leveltmp) + ".png";
SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, path.c_str());
menuLoop( backgroundTexture, menuMusic, choosesoundEffect);
Mix_PlayMusic(gameMusic, -1);
    float ballX = (width / 2) - radius;
    float ballY = height - 20.01 - (2 * radius);
    //thanh chan
    float barWidth = width/2;  
    float barHeight = 15;
    float barX = (width - barWidth) / 2; 
    float barY = height - 20;
    taogach();

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
        if (isAllBricksDestroyed() ) {
            maxbrick += 5;
            level ++;
            leveltmp++;
            if(leveltmp>8){
                leveltmp=1;
        }
        if (level > 14) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
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
int textW, textH;
TTF_SizeText(font, "LEVEL UP!", &textW, &textH);
SDL_Rect messageRect = {width / 2 - textW / 2, height / 2 - textH / 2 + 100, textW, textH}; 

for (int i = 0; i < 8; i++) {
    SDL_RenderClear(renderer);
    
    
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    
    
    
    SDL_Rect paddleRect = { (int)barX, (int)barY, barWidth, barHeight };
    SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);
    
    
    SDL_Rect ballRect = { (int)ballX, (int)ballY, radius * 2, radius * 2 };
    SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);

    
    if (i % 2 == 0) {  
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, "LEVEL UP!", textColor));
        SDL_RenderCopy(renderer, message, NULL, &messageRect);
        SDL_DestroyTexture(message);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(420);
}
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


        float dx = ballVelX * deltaTime;
float dy = ballVelY * deltaTime;

float stepSize = radius / 4.0f;
int steps = std::ceil(std::max(std::abs(dx), std::abs(dy)) / stepSize);
if (steps < 1) steps = 1;

float stepX = dx / steps;
float stepY = dy / steps;

for (int i = 0; i < steps; i++) {
    float nextX = ballX + stepX;
    float nextY = ballY + stepY;

    bool collisionX = false;
    bool collisionY = false;

    for (auto& brick : bricks) {
        if (!brick.isDestroyed) {
            bool hitX = nextX + radius * 2 > brick.x && nextX < brick.x + brick.rect.w;
            bool hitY = nextY + radius * 2 > brick.y && nextY < brick.y + brick.rect.h;

            if (hitX && hitY) {
                brick.hp--;
                if (brick.hp <= 0) {
                    Mix_PlayChannel(-1, hitsoundEffect, 0);
                    brick.isDestroyed = true;
                }

                float overlapLeft = std::abs((nextX + radius * 2) - brick.x);
                float overlapRight = std::abs((brick.x + brick.rect.w) - nextX);
                float overlapTop = std::abs((nextY + radius * 2) - brick.y);
                float overlapBottom = std::abs((brick.y + brick.rect.h) - nextY);

                float minHorizontal = std::min(overlapLeft, overlapRight);
                float minVertical = std::min(overlapTop, overlapBottom);

                if (minVertical < minHorizontal) {
                    ballVelY = -ballVelY;
                    collisionY = true;
                } else {
                    ballVelX = -ballVelX;
                    collisionX = true;
                }

                break; 
            }
        }
    }

    // Chỉ cập nhật vị trí nếu không có va chạm
    if (!collisionX) {
        ballX = nextX;
    }
    if (!collisionY) {
        ballY = nextY;
    }
}

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
            


SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
int textW, textH;
SDL_Color textColor = {255, 255, 255, 255}; 
Mix_PlayMusic(gameoverMusic, -1);
TTF_SizeText(font, "GAME OVER!", &textW, &textH);
SDL_Rect messageRect1 = {width / 2 - textW / 2, height / 3 - textH / 2, textW, textH};
SDL_Texture* message1 = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, "GAME OVER!", textColor));
SDL_RenderCopy(renderer, message1, NULL, &messageRect1);
SDL_DestroyTexture(message1);


TTF_SizeText(font, "Press any key to restart!", &textW, &textH);
SDL_Rect messageRect2 = {width / 2 - textW / 2, height / 2 - textH / 2, textW, textH};
SDL_Texture* message2 = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, "Press any key to restart", textColor));
SDL_RenderCopy(renderer, message2, NULL, &messageRect2);
SDL_DestroyTexture(message2);


TTF_SizeText(font, "Press ESC to quit", &textW, &textH);
SDL_Rect messageRect3 = {width / 2 - textW / 2, height * 2 / 3 - textH / 2, textW, textH};
SDL_Texture* message3 = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, "Press ESC to quit", textColor));
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
                    barX = (width - barWidth) / 2; 
                    barY = height - 20;
                    //speed = 400.f;
                    ballVelX = speed;
                    ballVelY = -speed;
                    //maxbrick = 5;
                    bricks.clear();
                    taogach(); 
                
                    lastTime = SDL_GetTicks();  // Đặt lại thời gian sau khi reset
                } else {
                    quit = true; 
                }
                
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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect ballRect = { (int)ballX, (int)ballY, radius * 2, radius * 2 };
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect paddleRect = { (int)barX, (int)barY, barWidth, barHeight };
        SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);
        
        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(gameMusic);
    Mix_FreeMusic(gameoverMusic);
    Mix_FreeChunk(hitsoundEffect);
    Mix_CloseAudio();
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(brickTexture);
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}