#include "task.h"

void ReverseList(std::list<int>& l) {
    std::list<int>::iterator begin = l.begin(), end = --l.end();
    while (begin != end) {
        std::iter_swap(begin, end);
        --end;
        ++begin;
    }
}
