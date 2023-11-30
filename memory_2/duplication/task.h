#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>

std::vector<std::unique_ptr<std::string>> Duplicate(const std::vector<std::shared_ptr<std::string>>& vec) {
    std::vector<std::unique_ptr<std::string>> dup;
    for (auto v : vec) {
        dup.push_back(std::make_unique<std::string>(*v));
    }
    return dup;
}

std::vector<std::shared_ptr<std::string>> DeDuplicate(const std::vector<std::unique_ptr<std::string>>& dup) {
    std::vector<std::shared_ptr<std::string>> dedup(dup.size());
    
    for (size_t i = 0; i < static_cast<size_t>(dup.size()); ++i) {
        bool flag = false;
        size_t j = 0;
     
        for (;j < i; ++j) {
            
            if (*dedup[j] == *dup[i]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            dedup[i] = dedup[j];
        }
        else {
            dedup[i] = std::make_shared<std::string>(*dup[i]);
        }
    }

    return dedup;
}