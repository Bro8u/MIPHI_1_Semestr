#include <iostream>

class Array {

public:

    Array(std::ostream& ostream): Ostream_(ostream) {
        size_ = 0;
        capacity_ = 2;
        data_ = new int[capacity_];
        Ostream_.clear();
        Ostream_ << "Constructed. " << *this;
    }
    Array(const Array& array) : Ostream_(array.Ostream_), capacity_(array.capacity_), size_(array.Size()) {
        data_ = new int[capacity_];
        CopyData(array.data_, data_);
        Ostream_.clear();
        Ostream_ << "Constructed from another Array. " << *this;
    }
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0) : Ostream_(ostream), size_(size) {
        capacity_ = size_ * 2; 
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = defaultValue;
        }
        Ostream_.clear();
        Ostream_ << "Constructed with default. " << *this;
    }

    ~Array() {
        Ostream_.clear();
        Ostream_ << "Destructed " << size_ << '\n';
        delete[] data_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            capacity_ = newCapacity;
            int* newData = new int[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
        
    }
    void Resize(size_t newSize) {
        if (size_ >= newSize) {
            size_ = newSize;
            Reserve(newSize);
            int* const newData = new int[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
            return;    
        }
        Reserve(newSize);
        int* const newData = new int[capacity_];
        CopyData(data_, newData);
        delete[] data_;
        data_ = newData;
        for (size_t i = size_; i < newSize; ++i) {
            data_[i] = 0;
        }
        size_ = newSize;
    }

    void PushBack(int value = 0) {
        if (size_ == capacity_) {
            Reserve(capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;

    }
    void PopBack() {
        if (Size()) {
            --size_;
        }
    }

    const int& operator[](const size_t i) const {
        return data_[i];
    }
    int& operator[](const size_t i) {
        return data_[i];
    }
    explicit operator bool() const {
        return size_ > 0;
    }

    bool operator<(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.Size()); ++i) {
            if (data_[i] < it[i]) {
                return true;
            }
            else if (data_[i] > it[i]) {
                return false;
            }
        }
        if (size_ < it.Size()) {
            return true;
        }
        return false;
    }
    bool operator>(const Array& it) const {
        if (it < *this) {
            return true;
        }
        else{
            return false;
        }
    }
    bool operator!=(const Array& it) const {
        if ((it < *this) || (it > *this)) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator==(const Array& it) const {
        if (!(it < *this) && !(it > *this)) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator<=(const Array& it) const {
        if ( *this < it || *this == it) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator>=(const Array& it) const {
        if (*this > it || *this == it) {
            return true;
        }
        else {
            return false;
        }
    }

    Array& operator<<(const int value) {
        PushBack(value);
        return *this;
    }
    Array& operator<<(const Array& it) {
        if (capacity_ < it.Size() + size_) {
            Reserve(it.Size() + size_);
        }
        
        for (size_t i = 0; i < it.Size(); ++i) {
            data_[i + size_] = it[i];
        }
        size_ += it.Size();
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Array& array);

private:
    std::ostream& Ostream_;
    size_t capacity_, size_;
    int* data_;
    void CopyData(int* source, int* destination) {
        for (size_t i = 0; i < size_; ++i) {
            destination[i] = source[i];
        }
    }
};

std::ostream& operator <<(std::ostream& ostream, const Array& arr) {
    ostream.clear();
    ostream << "Result Array's capacity is " <<  arr.capacity_  << " and size is " <<  arr.size_;
    for(size_t i = 0; i < arr.Size(); ++i) {
        if (i == 0){
            ostream << ", elements are: ";
        }
        ostream << arr[i] << ((i < arr.Size() - 1) ? ", " : "");
    }
    return ostream;
}
