#include <cassert>
#include <algorithm>
#include "task.h"
#include <iostream>
using namespace std;

int main() {
    list<int> l = {1, 45, 38, 99, 0, -10, 15};

    auto reversedList = l;
    reverse(l.begin(), l.end());
    
    ReverseList(l);
    
    assert(l == reversedList);
    return 0;
}
