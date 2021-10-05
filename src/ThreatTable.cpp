#include "ThreatTable.h"

ThreatTable::ThreatTable(vector<Actor*> actors, int xPos, int yPos) {
    for (auto const& actor : actors) {
        threatTable.insert(pair<Actor*, ThreatStruct>(actor, ThreatStruct{actor, 0, 0, 0}));

        Actor::Position actorPos = actor->GetPosition();
        threatTable[actor].distance = Utils::ManhattanDistance(actorPos.x, actorPos.y, xPos, yPos);
    }
}

void ThreatTable::Update(vector<Actor*> actors, int xPos, int yPos) {
    for (auto const& actor : actors) {
        Actor::Position actorPos = actor->GetPosition();

        threatTable[actor].distance = Utils::ManhattanDistance(actorPos.x, actorPos.y, xPos, yPos);
    }
}