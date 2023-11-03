#include "task.h"

bool is_palindrome(const std::string& s) {
    std::string now = "";
    for (int i = 0; i < s.size(); ++i) {
        if ( (isalpha(s[i])) ) {
            now += tolower(s[i]);
        }
    }
    int i = 0, j = now.size() - 1;
    bool ans = true;
    while (i < j) {
        if (now[i] != now[j]) {
            ans = false;
            break;
        }
        ++i;
        --j;
    }
    return ans;
}
