#include "task.h"

char* concat(const char* lhs, const char* rhs) {
    int size1 = 0;
    while (lhs[size1] != '\0') {
        ++size1;
    }
    int size2 = 0;
    while (rhs[size2] != '\0') {
        ++size2;
    }
    char* myString = new char[size1 + size2 + 1];
    myString[size1 + size2] = '\0';
    int first = 0, second = 0, newSize = 0;
    while (newSize <= size1 + size2) {
        if (first < size1) {
            myString[newSize] = lhs[first];
            ++first;
        }
        else if (second < size2){
            myString[newSize] = rhs[second];
            ++second;
        }
        ++newSize;
    }
    return myString;
}
