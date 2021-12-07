#include "ActorManager.h"

ActorManager::ActorManager(int resolutionX, int resolutionY, int tileSize) {
    resX = resolutionX;
    resY = resolutionY;
    this->tileSize = tileSize;
}

void ActorManager::Render(SDL_Renderer* rend, int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY) {
    vector<Actor*> actorsInViewport = GetActorsInViewport(xOffset, yOffset, wTiles, hTiles, camX, camY);

    for (auto const& actor : actorsInViewport) {
        actor->RenderRelativeToViewport(rend, xOffset, yOffset, camX, camY, wTiles, hTiles);
    }
}

void ActorManager::Update(double dt, Map* map) {
    for (auto const& actor : actors) {
        actor->Update(dt, map, GetPlayerControlled());
    }
}

Actor* ActorManager::GetActor(int xPos, int yPos) {
    for (auto const& actor : actors) {
        Actor::Position pos = actor->GetPosition();

        if (pos.x == xPos && pos.y == yPos) {
            return actor;
        }
    }

    return nullptr;
}

vector<Actor*> ActorManager::GetActorsInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY) {
    vector<Actor*> actorsInViewport;
    
    for (auto const& actor : actors) {
        Actor::Position actorPos = actor->GetPosition();

        if (actorPos.x >= camX && actorPos.x < camX + wTiles) {
            if (actorPos.y >= camY && actorPos.y < camY + hTiles) {
                actorsInViewport.push_back(actor);
            }
        }
    }

    return actorsInViewport;
}

vector<Actor*> ActorManager::GetPlayerControlled() {
    vector<Actor*> playerControlledActors;

    for (auto const& actor : actors) {
        if (actor->IsPlayerControlled()) {
            playerControlledActors.push_back(actor);
        }
    }

    return playerControlledActors;
}

vector<Actor*> ActorManager::GetEnemyControlled() {
    vector<Actor*> playerControlledActors;

    for (auto const& actor : actors) {
        if (!actor->IsPlayerControlled()) {
            playerControlledActors.push_back(actor);
        }
    }

    return playerControlledActors;
}

bool ActorManager::AnyActorsMoving() {
    bool anyMoving = false;

    for (auto const& actor : actors) {
        if (actor->IsMoving()) {
            anyMoving = true;
        }
    }

    return anyMoving;
}

void ActorManager::PopulateFromParty(vector<pair<int, int>> playerSpawns) {
    PlayerAccount* account = PlayerAccount::GetInstance();
    int index = 0;

    for (auto& actor : account->GetParty()) {
        actor->SetPosition(playerSpawns[index].first, playerSpawns[index].second);
        actors.insert(actor);
        index++;
    }
}

// Rework this to allow enemies to spawn on later turns - or just call this on startup and check blueprint again later?
void ActorManager::PopulateEnemiesFromQuestBlueprint(vector<pair<Enums::EnemyType, int>> blueprint, Map* map) {
    for (auto const& kvp : blueprint) {
        if (kvp.second == 0) {
            cout << "adding enemy" << endl;
            Add(ClassDefinitions::CreateEnemyFromEnum(kvp.first, tileSize, 0, map, GetPlayerControlled(), GridLocation {1, 1}));
        }
    }
}