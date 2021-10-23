#ifndef SRC_PLAYERACCOUNT_H_
#define SRC_PLAYERACCOUNT_H_

#include "Actor.h"

#include <algorithm>
#include <vector>

using namespace std;

class PlayerAccount {
    public:
        PlayerAccount();
        static PlayerAccount* GetInstance();

        int GetMaxPartySize() { return maxPartySize; };
        vector<Actor*> GetRoster() { return roster; };
        vector<Actor*> GetParty() { return party; };

        void AddToRoster(Actor* actor) { roster.push_back(actor); };
        void AddToParty(Actor* actor) { party.push_back(actor); };
        void RemoveFromRoster(Actor* actor) { roster.erase(remove(roster.begin(), roster.end(), actor), roster.end()); };
        void RemoveFromParty(Actor* actor) { party.erase(remove(party.begin(), party.end(), actor), party.end()); };

    private:
        static PlayerAccount* instance;
        vector<Actor*> roster;
        vector<Actor*> party;
        int maxPartySize;
};

#endif /* SRC_PLAYERACCOUNT_H_ */