#include <unordered_map>
#include <list>
#include <iterator>
#include <iostream>
using std::cout;

template <typename K, typename V>
class LruCache {
public:
    LruCache(size_t max_size): max_size(max_size) {}

    void Put(const K& key, const V& value) {
        if (M.find(key) != M.end()) {
            M[key]->second = value;
            Q.splice(Q.begin(), Q, M[key]);
        }
        else {
            Q.push_front({key, value});
            M.insert({key, Q.begin()});
            if (Q.size() > max_size && Q.size() > 0) {
                M.erase(Q.back().first);
                Q.pop_back();
            }
        }
    }

    bool Get(const K& key, V* value) {
        if (M.find(key) != M.end()) {
            *value = M[key]->second;
            Q.splice(Q.begin(), Q, M[key]);
            return true;
        }
        return false;
    }
private:
    size_t max_size;
    std::list<std::pair<K, V>> Q;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> M;
};
 