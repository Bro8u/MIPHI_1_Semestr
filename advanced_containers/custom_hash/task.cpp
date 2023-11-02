#include "task.h"

using namespace std;
void PopulateHashMap(
    unordered_map<SuperKey, string>& hashMap,
    const vector<pair<SuperKey, string>>& toAdd) 
    {
        for (auto v : toAdd) {
            hashMap[v.first] = v.second;
        }
    }
