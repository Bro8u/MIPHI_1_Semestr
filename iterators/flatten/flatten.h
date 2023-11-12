#pragma once
#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
class FlattenedVector {
public:
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        iterator(FlattenedVector<T>* parent, int64_t ptr) : parent_(parent), ptr_(ptr) {}
        // 2 2 8 8
        // 0 2 4 12 20
        
        T& operator*() const {
            size_t it = std::upper_bound(parent_->prefixSums_.begin(), parent_->prefixSums_.end(), ptr_);
            size_t outer = it - parent_->prefixSums_.begin() - 1;
            size_t inner = ptr_ - parent_->prefixSums_[it - 1];
            return parent_->data_[outer][inner];
        }
        T& operator[](const size_t index) const {
            size_t it = std::upper_bound(parent_->prefixSums_.begin(), parent_->prefixSums_.end(), index);
            size_t outer = it - parent_->prefixSums_.begin() - 1;
            size_t inner = index - parent_->prefixSums_[it - 1];
            return parent_->data_[outer][inner];
        }
        T& operator[](const iterator& other) const{
            size_t it = std::upper_bound(parent_->prefixSums_.begin(), parent_->prefixSums_.end(), other.ptr_);
            size_t outer = it - parent_->prefixSums_.begin() - 1;
            size_t inner = other.ptr_ - parent_->prefixSums_[it - 1];
            return parent_->data_[outer][inner];
        }

        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        iterator& operator--() {
            --ptr_;
            return *this;
        }

        size_t operator-(const iterator other) const {
            return ptr_ - other.ptr_;
        }

        size_t operator+(const iterator other) const {
            return ptr_ + other.ptr_;
        }

        size_t operator-(const int delta) const {
            return ptr_ - delta;
        }

        size_t operator+(const int delta) const {
            return ptr_ - delta;
        }

        iterator& operator+=(const iterator other) {
            ptr_ += other.ptr_;
            return *this;
        }
        iterator& operator-=(const iterator other) {
            ptr_ -= other.ptr_;
            return *this;
        }
        iterator& operator+=(const size_t v) {
            ptr_ += v;
            return *this;
        }
        iterator& operator-=(const size_t v) {
            ptr_ -= v;
            return *this;
        }
 
        bool operator==(const iterator other) const {
            return (ptr_ == other.ptr_);
        }
        bool operator!=(const iterator other) const {
            return !(this == other);
        }
        bool operator==(const int v) const {
            return (ptr_ == v);
        }
        bool operator!=(const int v) const {
            return !(this == v);
        }
        bool operator<(const iterator other) const {
            return (ptr_ < other.ptr);
        }
        bool operator<=(const iterator other) const {
            return (this == other || this < other);
        }
        bool operator>(const iterator other) const {
            return !(this <= other);
        }
        bool operator>=(const iterator other) const {
            return !(this < other);
        }
      
        
        // Similarly, implement other required operators (--, --(int), +, -, +=, -=, <, >, <=, >=, [], etc.)
        // ...

    private:
        FlattenedVector<T>* parent_;
        int64_t ptr_;
    };

    FlattenedVector(std::vector<std::vector<T>>& data)
        : data_(data), prefixSums_(data.size() + 1) {
        prefixSums_[0] = 0;
        for (size_t i = 0; i < data_.size(); ++i) {
            prefixSums_[i + 1] = prefixSums_[i] + data_[i].size();
        }
    }

    iterator begin() {
        return iterator(this, 0);
    }
    iterator end() {
        return iterator(this, data_.size());
    }
    

private:
    std::vector<std::vector<T>>& data_;
    std::vector<size_t> prefixSums_;
    // T* index;
};
