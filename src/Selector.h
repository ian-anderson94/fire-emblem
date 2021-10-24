#ifndef SRC_SELECTOR_H_
#define SRC_SELECTOR_H_

#include "InputManager.h"
#include "Position.h"
#include "TextureManager.h"

#include <string>
#include <vector>

using namespace std;

template <class T>
class Selector {
    public:
        Selector(vector<T> options);
        void SetAndBoundCurrSelection(int delta);
        void RenderRelativeToSelection(SDL_Renderer* rend, Position sPos);
        /*
        template<T> inline Selector(vector<T> options) {
            this->options = options;
            currSelection = 0;
            selectorTexture = TextureManager::loadTexture(selectorImagePath);
        };

        template<T> inline void RenderRelativeToSelection(SDL_Renderer* rend, Position sPos) {
            int frame = AnimationManager::GetInstance()->GetFrameIndex(6);
            SDL_Rect src { frame * 64, 0, 64, 64};
            SDL_Rect dest { sPos.x , sPos.y , sPos.w, sPos.h };
            SDL_RenderCopy(rend, selectorTexture, &src, &dest);
        };

        template<T> inline void SetAndBoundCurrSelection(int delta) {
            currSelection += delta;

            if (currSelection < 0) {
                currSelection = options.size() - abs(currSelection);
            } else if (currSelection >= options.size()) {
                currSelection = currSelection - options.size();
            }
        };
        */
        int GetSelectionIndex() { return currSelection; };
        T GetSelection() { return options[currSelection]; };

    private:
        int currSelection;
        vector<T> options;

        const char* selectorImagePath = "./assets/selector_arrow.png";
        SDL_Texture* selectorTexture;

};

template <class T>
Selector<T>::Selector(vector<T> options) {
    this->options = options;

    currSelection = 0;
    selectorTexture = TextureManager::loadTexture(selectorImagePath);
}

template <class T>
void Selector<T>::RenderRelativeToSelection(SDL_Renderer* rend, Position sPos) {
    int frame = AnimationManager::GetInstance()->GetFrameIndex(6);
    SDL_Rect src { frame * 64, 0, 64, 64};
    SDL_Rect dest { sPos.x , sPos.y , sPos.w, sPos.h };
    SDL_RenderCopy(rend, selectorTexture, &src, &dest);
}

template <class T>
void Selector<T>::SetAndBoundCurrSelection(int delta) {
    currSelection += delta;

    if (currSelection < 0) {
        currSelection = options.size() - abs(currSelection);
    } else if (currSelection >= options.size()) {
        currSelection = currSelection - options.size();
    }
}

#endif /* SRC_SELECTOR_H_ */