#include "Globals.h"

Globals::Globals() {

}

Globals::~Globals() {

}

void Globals::SetRect(SDL_Rect* rect, int x, int y, int w, int h) {
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

bool Globals::AABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if (x1 < x2 + w2 &&
			x1 + w1 > x2 &&
			y1 < y2 + h2 &&
			y1 + h1 > y2) {
		return true;
	}

	return false;
}

bool Globals::AABB_1D (int x1, int w1, int x2, int w2) {
	if (x1 <= x2 + w2 && x1 + w1 >= x2) {
		return true;
	}

	return false;
}

bool Globals::Contains(std::unordered_set<int> set, int target) {
	if (set.find(target) != set.end())
		return true;

	return false;
}
