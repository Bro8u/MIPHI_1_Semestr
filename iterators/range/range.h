#pragma once
#include <iostream>

class Range {
public:
    class iterator{
    public:
        
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int64_t;
        using pointer           = int64_t*;
        using reference         = int64_t&;
        iterator(int64_t ptr, int64_t step = 1) : ptr_(ptr), step_(step) {}

        value_type operator*() const{
            return ptr_;
        }
        iterator& operator++() {
            ptr_ += step_;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ptr_ += step_;
            return tmp;
        }
        bool operator==(const iterator other) const {
            if (step_ > 0) {
                return (ptr_ >= other.ptr_);
            }
            else{
                return (ptr_ <= other.ptr_);
            }
        }
        bool operator!=(const iterator other) const {
            return !(ptr_ == other.ptr_ && step_ == other.step_);
        }
        
    private:
        int64_t ptr_, step_;
    };
    
    iterator begin() const {
        return iterator(start_, step_);
    }
    iterator end() const {
        return iterator(end_, step_);
    }
    
    Range(const int64_t end) : start_(0), end_(end), step_(1)  {}

    Range(const int64_t start, const int64_t end) : start_(start), end_(end), step_(1)  {}

    Range(const int64_t start, const int64_t end, const int64_t step) : start_(start), end_(end), step_(step) {}

    int64_t Size() const {
        return (abs(end_ - start_) + abs(step_) - 1) / abs(step_);
    }

private:
    const int64_t start_, end_, step_;
};





