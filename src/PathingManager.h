#ifndef SRC_PATHINGMANAGER_H_
#define SRC_PATHINGMANAGER_H_

#include "Map.h"
#include "Tile.h"

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct GridLocation {
    int x, y;
};

inline bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

inline bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

inline bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

namespace std {
    /* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<GridLocation> {
        typedef GridLocation argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const GridLocation& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
                    std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

class PathingManager {
    public:
        PathingManager(Map* map);

        void CalculatePath(int actorX, int actorY, int cursorX, int cursorY);
        void Update(Map* map);

    private:
        Map* map;

        vector<GridLocation> AStarSearch(GridLocation start, GridLocation end);
        vector<GridLocation> GetNeighbors(GridLocation curr);
        vector<GridLocation> ReconstructPath(GridLocation start, GridLocation end, unordered_map<GridLocation, GridLocation> visitedLocations);
        int CalculateHeuristic(GridLocation left, GridLocation right);
        int CalculateCost(GridLocation left, GridLocation right);
        bool InBounds(int x, int y);

        void PrintPath(vector<GridLocation> path);
};

#endif /* SRC_PATHINGMANAGER_H_ */