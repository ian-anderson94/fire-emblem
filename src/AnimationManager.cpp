#include "AnimationManager.h"

AnimationManager* AnimationManager::instance = nullptr;

AnimationManager* AnimationManager::GetInstance() {
    if (!instance) {
        instance = new AnimationManager();
    }

    return instance;
}

void AnimationManager::TickAnimationTimer(double dt) {
    animationTimer += dt;

    if (animationTimer > animationTimerMax) {
        animationTimer = 0;
    }
}

int AnimationManager::GetFrameIndex(int framesInTexture) {
    double percentage = animationTimer / animationTimerMax;

    return floor(percentage * framesInTexture);
}