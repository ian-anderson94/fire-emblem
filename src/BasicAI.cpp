#include "BasicAI.h"

// Gets closest actor
Actor* BasicAI::IdentifyMostThreateningEnemy(unordered_map<Actor*, ThreatTable::ThreatStruct> threatTable) {
    Actor* mostThreatening = nullptr;
    int minDistance = INT_MAX;

    for (auto const& threatStruct : threatTable) {
        if (threatStruct.second.distance <= minDistance) {
            minDistance = threatStruct.second.distance;
            mostThreatening = threatStruct.first;
        }
    }

    return mostThreatening;
}