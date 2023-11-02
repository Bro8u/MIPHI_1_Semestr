#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int>& v) {
    priority_queue<int> Q;
    vector<int> ans(v.size());
    for (auto v : v) {
        Q.push(v);
    }
    for (int i = v.size() - 1; i >= 0; --i) {
        ans[i] = Q.top();
        Q.pop();
    }
    return ans;
}
