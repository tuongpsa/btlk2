#include "resources.h"

Mix_Music* menuMusic = nullptr;
Mix_Music* gameMusic = nullptr;
Mix_Music* gameoverMusic = nullptr;
Mix_Chunk* hitsoundEffect = nullptr;
Mix_Chunk* popsoundEffect = nullptr;
Mix_Chunk* choosesoundEffect = nullptr;
TTF_Font* font = nullptr;
SDL_Texture* paddleTexture = nullptr;
SDL_Texture* ballTexture = nullptr;
SDL_Texture* brickTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;

bool loadResources(SDL_Renderer* renderer, int leveltmp) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(64);

    menuMusic = Mix_LoadMUS("assets/menusound.mp3");
    gameMusic = Mix_LoadMUS("assets/theme.mp3");
    gameoverMusic = Mix_LoadMUS("assets/gameoversound.mp3");
    hitsoundEffect = Mix_LoadWAV("assets/hitsound.wav");
    popsoundEffect = Mix_LoadWAV("assets/pop.wav");
    choosesoundEffect = Mix_LoadWAV("assets/choosesound.wav");

    if (!TTF_WasInit()) TTF_Init();
    font = TTF_OpenFont("PixelGame.otf", 40);

    paddleTexture = IMG_LoadTexture(renderer, "assets/thanh1.png");
    ballTexture = IMG_LoadTexture(renderer, "assets/pig.png");
    brickTexture = IMG_LoadTexture(renderer, "assets/br3.png");
    std::string path = "assets/back" + std::to_string(leveltmp) + ".png";
    backgroundTexture = IMG_LoadTexture(renderer, path.c_str());

    return menuMusic && gameMusic && gameoverMusic &&
           hitsoundEffect && popsoundEffect && choosesoundEffect &&
           font && paddleTexture && ballTexture && brickTexture && backgroundTexture;
}

void freeResources() {
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(gameMusic);
    Mix_FreeMusic(gameoverMusic);
    Mix_FreeChunk(hitsoundEffect);
    Mix_FreeChunk(popsoundEffect);
    Mix_FreeChunk(choosesoundEffect);
    TTF_CloseFont(font);
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(brickTexture);
    SDL_DestroyTexture(backgroundTexture);
}
