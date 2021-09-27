#include "TurnManager.h"

TurnManager::TurnManager(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;
    
    isCurrentTurnOver = true;

    turnOrder = new TurnOrder(resX, resY, tileSize);
}

Actor* TurnManager::GetNextTurn(unordered_set<Actor*> actors) {
    if (turnOrder->Empty()) {
        turnOrder->GenerateTurnOrder(actors);
    }

    isCurrentTurnOver = false;

    return turnOrder->GetNext();
}

void TurnManager::Render(SDL_Renderer* rend) {
    turnOrder->Render(rend);
}