#ifndef SRC_TEXTMANAGER_H_
#define SRC_TEXTMANAGER_H_

#include "Position.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <math.h>
#include <string>
#include <vector>

using namespace std;

class TextManager {
    public:
        static Position SizeListOfText(vector<string> vec);
        static Position LoadFontAndPrint(SDL_Renderer* rend, const char* text, int x, int y);
        //static void LoadFontAndPrint(SDL_Renderer* rend, const char* text, int x, int y, int w, int h);
        //static void LoadFontAndPrint(const char* fontFile, int fontSize, const char* text, SDL_Color color, int x, int y, int w, int h, SDL_Renderer* rend);

    private:
        static const int fontSize;
        static const char* fontFile;

};

#endif /* SRC_TEXTMANAGER_H_ */
