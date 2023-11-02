#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};
namespace std {
    template <>
    class hash<SuperKey> {
    public:
        size_t operator()(const SuperKey& k) const {
            size_t h1 = hash<std::string>()(k.StrPart);
            size_t h2 = hash<int>()(k.IntPart);
            size_t h3 = hash<float>()(k.FloatPart);
            return h1 ^ (h2 << 1) + h3;
        }
    };
}
/*
 * Напишите хэш-функцию, реализовав специализацию шаблона std::hash для типа SuperKey
 * Напишите функцию PopulateHashMap, которая добавляет в hashMap пары ключ-значение из данного вектора toAdd
 */
void PopulateHashMap(
    std::unordered_map<SuperKey, std::string>& hashMap,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
);

