
#include <math.h>
#include <algorithm>
#include <iostream>
#pragma once

namespace NPointers {


    int Increment(int* arg) {
        int a;
        a = *arg + 1;
        return a;
    }
    int Multiply(const int a, const int b, bool* isOverflow) {
        *isOverflow = true;
        if (a * b > pow(2, 31) - 1) {
            *isOverflow = false;
        }
        return (a * b);
    }
    int ScalarProduct(const int a[], const int b[], int size_of) {
        int summ = 0;
        for(int i = 0; i < (int)size_of; ++i) {
            summ += a[i] * b[i];
        }
        return summ; 
    }
    int SizeOfMaximumSquareOfCrosses(const char* a, int n, int m) {
        int dp[n][m];
        for (int i = 0; i < n; ++i) {
            dp[i][0] = (a[m * i] == '+') ? 1 : 0;
        }
        for (int i = 0; i < m; ++i) {
            dp[0][i] = (a[i] == '+') ? 1 : 0;
        }
        int i = 1, j = 1, maxx = 1; 
        while (i < n) {
            j = 1;
            while (j < m) {
                if (a[i * m + j] == '+'){
                    dp[i][j] = 1 + (std::min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]}));
                    maxx = std::max(maxx, dp[i][j]);
                }
                ++j;
            }
            ++i;
        }
        
        return maxx;

    }
    long long* MultiplyToLongLong(int a, int b) {
        long long res = (static_cast<long long>(a) * static_cast<long long>(b));
        long long* ptr = &res;
        return ptr;
    }
    /* To implement:
    Increment
    Multiply
    ScalarProduct
    SizeOfMaximumSquareOfCrosses
    MultiplyToLongLong
    */
}

namespace NReferences {
    void MultiplyInplace(int a, int b){
        a *= b;
    }
    int CompareArraysByAverage(const int a[], int size_of, int b[]){
        int first = 0, second = 0, len = 0;
        for (int i = 0; i < (int)size_of; ++i) {
            first += a[i];
        }
        int* ptr = b;
        while (ptr) {
            second += *ptr;
            ++ptr;
            ++len;
        }
        if (first / size_of < second / len ) {
            return -1;
        }
        else if (first / size_of > second / len) {
            return 1;
        }
        else{
            return 0;
        }
        
    }
    /* To implement:
    MultiplyInplace
    CompareArraysByAverage
    */
}
