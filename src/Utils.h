#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>
#include <string>

#include <unordered_set>

using namespace std;

class Utils {
    public:
        static bool StoB(string s);
        static bool Contains(unordered_set<int> set, int target);
        static string ToLower(string s);


};

#endif /* SRC_UTILS_H_ */