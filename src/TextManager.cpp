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