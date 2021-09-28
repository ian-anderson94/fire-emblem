#include "Utils.h"

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