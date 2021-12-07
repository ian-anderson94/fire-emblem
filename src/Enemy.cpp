#include "Enemy.h"

Enemy::Enemy(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats,
    Map* map, AIParadigm* paradigm, vector<Actor*> actors, int spawnTurn) 
    : Actor(image, icon, xPos, yPos, ts, actorStats) {
        this->map = map;
        this->paradigm = paradigm;
        this->actors = actors;
        this->spawnTurn = spawnTurn;

        playerControlled = false;
        pathingManager = new PathingManager(map, ts);
        threatTable = new ThreatTable(actors, xPos, yPos);
    }

void Enemy::Update(double dt, Map* map, vector<Actor*> actors) {
    this->actors = actors;

    Actor::Update(dt, map, actors);

    threatTable->Update(actors, x, y);
}

void Enemy::DoTurn() {
    Actor* target = paradigm->IdentifyMostThreateningEnemy(threatTable->GetTable());

    Actor::Position targetPos = target->GetPosition();

    pathingManager->CalculatePath(x, y, targetPos.x, targetPos.y);

    pathingManager->TrimPath();

    Move(pathingManager->GetPath());

}
