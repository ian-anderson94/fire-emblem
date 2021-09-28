#include "Game.h"
#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const char* texture) {
    SDL_Surface* tempSurface = IMG_Load(texture);

    if (!tempSurface) {
        std::cout << "Error loading texture\n";
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    if (!tex) {
        std::cout << "Error creating surface\n";
    }

    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}



