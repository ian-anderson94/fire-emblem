#include "PathingManager.h"

PathingManager::PathingManager(Map* map) {
    this->map = map;
}

void PathingManager::Update(Map* map) {
    this->map = map;
}

void PathingManager::CalculatePath(int actorX, int actorY, int cursorX, int cursorY) {

}