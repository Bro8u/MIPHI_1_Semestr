#include "task.h"

bool operator <(const SuperKey& lhs, const SuperKey& rhs) {
    
    if (lhs.StrPart < rhs.StrPart) {
        return true;
    }
    else if (lhs == rhs) {
        return false;
    }
    else if (lhs.StrPart == rhs.StrPart) {
        if (lhs.IntPart < rhs.IntPart) {
            return true;
        }
        else if (lhs.IntPart == rhs.IntPart) {
            if (lhs.FloatPart < rhs.FloatPart) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void PopulateMap(
    std::map<SuperKey, std::string>& map,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd) 
    {
        for (auto v : toAdd) {
            map[v.first] = v.second;
        }
    }
