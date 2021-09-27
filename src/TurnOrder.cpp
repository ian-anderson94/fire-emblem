#include "TurnOrder.h"

TurnOrder::TurnOrder(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;

    x = tileSize;
    y = tileSize / 4;
    w = resX - (tileSize * 2);
    h = tileSize / 2;

    imagePath = "./assets/turnorder_bar.png";
    turnOrderTexture = TextureManager::loadTexture(imagePath);
}

void TurnOrder::GenerateTurnOrder(unordered_set<Actor*> actors) {
    for (auto const& actor : actors) {
        Actor::Stats stats = actor->GetStats();
        int speedRoll = stats.spd + (rand() % 20 + 1);

        turnOrder.push(pair<int, Actor*>(speedRoll, actor));
    }
}

Actor* TurnOrder::GetNext() {
    Actor* next = turnOrder.top().second;
    turnOrder.pop();

    return next;
}

bool TurnOrder::Empty() {
    if (turnOrder.empty()) {
        return true;
    }

    return false;
}

void TurnOrder::Render(SDL_Renderer* rend) {
    RenderBar(rend);
    RenderIcons(rend);
}

void TurnOrder::RenderBar(SDL_Renderer* rend) {
    SDL_Rect dst {x, y, w, h};
    SDL_RenderCopy(rend, turnOrderTexture, NULL, &dst);
}

void TurnOrder::RenderIcons(SDL_Renderer* rend) {
    int xOffset = tileSize * 2;
    int yOffset = y;
    int iconSize = 32;

    priority_queue<pair<int, Actor*>, vector<pair<int, Actor*>>, Comparator> tempQueue;

    tempQueue = turnOrder;

    while (!tempQueue.empty()) {
        Actor* currActor = tempQueue.top().second;

        SDL_Texture* tex = currActor->GetIcon();
        SDL_Rect dst {xOffset, yOffset, iconSize, iconSize};
        SDL_RenderCopy(rend, tex, NULL, &dst);
        xOffset += tileSize;

        tempQueue.pop();
    }

    /*
    for (auto const& kvp : turnOrder) {
        Actor* currActor = kvp.second;
        SDL_Texture* tex = currActor->GetIcon();
        SDL_Rect dst {xOffset, yOffset, iconSize, iconSize};
        SDL_RenderCopy(rend, tex, NULL, &dst);
        xOffset += tileSize;
    }
    */
}