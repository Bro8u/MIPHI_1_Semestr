#include <cstring>
struct State {
    int ref_count = 0; // сколько строк используют этот State.
    char* ptr_;
    size_t size_ = 0, capacity_ = 2;
    
};

class CowString {
public:
    CowString() : data_(new State{1, new char[2], 0, 2}) {}
    CowString(const CowString& other) {
        data_ = other.data_;
        ++data_->ref_count;
    }
    ~CowString() {
        --data_->ref_count;
        if (data_->ref_count == 0) {
            delete[] data_->ptr_;
            delete data_;
        }
    }
    CowString& operator=(const CowString& other) {
        if (this == &other){ return *this; }
        --data_->ref_count;
        if (data_->ref_count == 0) {
            delete[] data_->ptr_;
            delete data_;
        }
        data_ = other.data_;
        ++data_->ref_count;
        return *this; 
    }
    
    const char& At(size_t index) const {
        return data_->ptr_[index];
    }
    char& operator[](size_t index) {
        check();
        return data_->ptr_[index];
    }

    const char& Back() const {
        return data_->ptr_[data_->size_ - 1];
    }

    void PushBack(char c) {
        if (data_->size_ == data_->capacity_) {
            Reserve(data_->size_ * 2);
        }
        check();
        data_->ptr_[data_->size_] = c;
        ++data_->size_;
    }

    size_t Size() const {
        return data_->size_;
    }
    size_t Capacity() const {
        return data_->capacity_;
    }

    void Reserve(size_t capacity) {
        if (capacity > data_->capacity_) {
            char* newPtr_ = new char[capacity];
            for (size_t i = 0; i < data_->size_; ++i) {
                newPtr_[i] = data_->ptr_[i];
            }
            check();
            delete[] data_->ptr_;
            data_->ptr_ = newPtr_;
            data_->capacity_ = capacity;
        }
    }
    void Resize(size_t size) {
        check();
        if (size > data_->size_) {
            if (size > data_->capacity_) {
                Reserve(size);
            }   
        }     
        data_->size_ = size;                               
    }
private:
    State* data_;
    
    void check() {
        if (data_->ref_count > 1) {
            State* newData_ = new State{1, new char[data_->capacity_], data_->size_, data_->capacity_};
            for (size_t i = 0; i < data_->size_; ++i) {
                newData_->ptr_[i] = data_->ptr_[i];
            }
            --data_->ref_count;
            data_ = newData_;
        }
    }

};
