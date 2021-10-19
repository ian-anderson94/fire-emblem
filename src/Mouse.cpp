#include "Mouse.h"

Mouse::Position Mouse::GetPosition() {
    int x, y;

    SDL_GetMouseState(&x, &y);

    return Position { x, y };
}