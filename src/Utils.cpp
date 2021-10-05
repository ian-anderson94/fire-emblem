#include "Utils.h"

int Utils::ManhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool Utils::StoB(string s) {
    string curr = Utils::ToLower(s);

    if (curr.compare("false") == 0) {
        return false;
    } else {
        return true;
    }
}

string Utils::ToLower(string s) {
    string lowerString = s;
    transform(lowerString.begin(), lowerString.end(), lowerString.begin(),[](unsigned char c){ return tolower(c); });

    return lowerString;
}

bool Utils::Contains(unordered_set<int> set, int target) {
	if (set.find(target) != set.end())
		return true;

	return false;
}