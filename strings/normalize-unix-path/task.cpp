#include "task.h"

using namespace std;

string normalize(string_view path) {

    vector<string> way;
    string ans = "";
    int index = 0;
    bool flag = true;
    string now = "";
    if (path[0] != '/') {
        flag = false;
    }
    while (path[index] != '\0') {
        if (!flag && path[index] != '/') {
            now += path[index];
        }
        if (!flag && path[index] == '/') {
            way.push_back(now);
            now = "";
            flag = true;
        }
        if (path[index] == '/') {
            flag = false;
        }
        ++index;
    }
    
    way.push_back(now);
    vector<int> used(way.size(), 1);
    index = 0;
    while (index < (int)way.size()) {
        if (way[index] == "..") {
            if (path[0] == '/') {
                if (index > 0) {
                    used[index - 1] = 0;  
                }
                used[index] = 0;
            }
            else {
                if (index > 0) {
                    if (way[index - 1] == ".." && used[index - 1]) {
                        ++index;
                        continue;
                    }
                    else{
                        used[index - 1] = 0;
                        used[index] = 0;
                    }
                }
                // leave if it is first .. 
            }
        }
        if (way[index] == "." || way[index] == "" || way[index] == "/") {
            used[index] = 0;
        }
        ++index;
    }

    if (path.size() == 1) {
        ans += path[0];
        return ans;
    }
    else if (path.size() == 2 && path[0] == '.' && path[1] == '.') {
        ans += path[0];
        ans += path[1];
        return ans;
    }
    else {
        if (path[0] == '/') {
            ans = "/";
        }
        for (int i = 0; i < (int)used.size(); ++i) {
            if (used[i]) {
                ans += way[i] + "/";
            }
        }
        if (ans[ans.size() - 1] == '/' && ans.size() > 1){ 
            ans.pop_back();
        }
        return ans;
    }
    

}
