#include "TextManager.h"
#include <iostream>

const int TextManager::fontSize = 28;
const char* TextManager::fontFile = "./fonts/OpenSans-Regular.ttf";

Position TextManager::SizeListOfText(vector<string> vec) {
    SDL_Color white = SDL_Color { 255, 255, 255 };
    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    int w = 0, h = 0;

    for (int i = 0; i < vec.size(); i++) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, vec[i].c_str(), white);
        w = max(w, surfaceMessage->w);
        h += surfaceMessage->h;
        SDL_FreeSurface(surfaceMessage);
    }

    TTF_CloseFont(font);
    return Position { -1, -1, w, h };
}

Position TextManager::LoadFontAndPrint(SDL_Renderer* rend, const char* text, int x, int y) {
    //const char* fontFile = "./fonts/OpenSans-Regular.ttf";
    //int fontSize = 28;

    SDL_Color white = SDL_Color { 255, 255, 255 };

    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surfaceMessage);

    SDL_Rect dst { x, y, surfaceMessage->w, surfaceMessage->h };

    SDL_RenderCopy(rend, message, NULL, &dst);

    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);

    return Position { x, y, dst.w, dst.h };
}

/*
void TextManager::LoadFontAndPrint(SDL_Renderer* rend, const char* text, int x, int y, int w, int h) {
    const char* fontFile = "./fonts/OpenSans-Regular.ttf";
    int fontSize = 28;
    SDL_Color white = SDL_Color { 255, 255, 255 };

    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surfaceMessage);

    SDL_Rect rect {x, y, w, h};

    SDL_RenderCopy(rend, message, NULL, &rect);

    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void TextManager::LoadFontAndPrint(const char* fontFile, int fontSize, const char* text, SDL_Color color, int x, int y, int w, int h, SDL_Renderer* rend) {
    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surfaceMessage);

    SDL_Rect rect {x, y, w, h};

    SDL_RenderCopy(rend, message, NULL, &rect);

    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}
*/