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
            M[key] = value;
            Q.remove(key);
            Q.push_front(key);
        }
        else {
            Q.push_front(key);
            M.insert({key, value});
            if (Q.size() > max_size && Q.size() > 0) {
                M.erase(Q.back());
                Q.pop_back();
            }
        }
        
        
    }

    bool Get(const K& key, V* value) {
        if (M.find(key) != M.end()) {
            *value = M[key];
            Q.remove(key);
            Q.push_front(key);
            return true;
        }
        return false;
    }
private:
    size_t max_size;
    std::list<K> Q;
    std::unordered_map<K, V> M;
};
