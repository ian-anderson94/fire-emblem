#ifndef SRC_GRIDLOCATION_H_
#define SRC_GRIDLOCATION_H_

#include <tuple>

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

#endif /* SRC_GRIDLOCATION_H_ */