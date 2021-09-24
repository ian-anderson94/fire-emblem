#ifndef SRC_TEXTMANAGER_H_
#define SRC_TEXTMANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class TextManager {
public:
	static void LoadFontAndPrint(const char* fontFile, int fontSize, const char* text, SDL_Color color, int x, int y, int w, int h, SDL_Renderer* rend);
};

#endif /* SRC_TEXTMANAGER_H_ */
