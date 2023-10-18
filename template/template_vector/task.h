#include <iostream>

template<typename T>
class Array {
public:
    Array(std::ostream& ostream): Ostream_(ostream) {
        size_ = 0;
        capacity_ = 2;
        data_ = new T[capacity_];
        Ostream_.clear();
        Ostream_ << "Constructed. " << *this;
    }

    Array(const Array<T>& array) : Ostream_(array.Ostream_), capacity_(array.capacity_), size_(array.Size()) {
        data_ = new T[capacity_];
        CopyData(array.data_, data_);
        Ostream_.clear();
        Ostream_ << "Constructed from another Array. " << *this;
    }

    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T()) : Ostream_(ostream), size_(size) {
        capacity_ = size_ * 2; 
        data_ = new T[capacity_];
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
    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            capacity_ = newCapacity;
            T* newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
        }
    }

     void Resize(size_t newSize) {
        if (size_ >= newSize) {
            size_ = newSize;
            Reserve(newSize);
            T* const newData = new T[capacity_];
            CopyData(data_, newData);
            delete[] data_;
            data_ = newData;
            return;    
        }
        Reserve(newSize);
        T* const newData = new T[capacity_];
        CopyData(data_, newData);
        delete[] data_;
        data_ = newData;
        for (size_t i = size_; i < newSize; ++i) {
            data_[i] = T();
        }
        size_ = newSize;
    }

    void PushBack(T value = 0) {
        if (size_ == capacity_) {
            Reserve(capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;
    }
    void PushFront(T value) {
        if (size_ == capacity_) {
            Reserve(capacity_ * 2);
        }
        T* const newData = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            newData[i + 1] = data_[i];
        }
        newData[0] = value;
        delete[] data_;
        data_ = newData;
        ++size_;
    }

    void PopBack() {
        if (Size()) {
            --size_;
        }
    }

    const T& operator [](const size_t i) const {
        return data_[i];
    }

    T& operator [](const size_t i) {
        return data_[i];
    }

    explicit operator bool() const {
        return size_ > 0;
    }

    bool operator <(const Array<T>& it) const {
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

    bool operator >(const Array<T>& it) const {
        if (it < *this) {
            return true;
        }
        else{
            return false;
        }
    }

    bool operator !=(const Array<T>& it) const {
        if ((it < *this) || (it > *this)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator ==(const Array<T>& it) const {
        if (!(it < *this) && !(it > *this)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator <=(const Array<T>& it) const {
        if ( *this < it || *this == it) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator >=(const Array<T>& it) const {
        if (*this > it || *this == it) {
            return true;
        }
        else {
            return false;
        }
    }

    Array<T>& operator <<(const T& value) {
        PushBack(value);
        return *this;
    }

    Array<T>& operator <<(const Array<T>& it) {
        if (capacity_ < it.Size() + size_) {
            Reserve(it.Size() + size_);
        }
        
        for (size_t i = 0; i < it.Size(); ++i) {
            data_[i + size_] = it[i];
        }
        size_ += it.Size();
        return *this;
    }

    bool Insert(size_t pos, const T& value) {
        if (pos > size_) {
            return false;
        }
        if (pos == size_) {
            PushBack(value);
            return true;
        }
        if (pos == 0) {
            PushFront(value);
            return true;
        }
        data_[pos] = value;
        return true;
        
    }

    bool Erase(size_t pos) {
        if (!size_ || pos >= size_) {
            return false;
        }
        T* newData = new T[capacity_];
        for (size_t i = 0; i < pos; ++i) {
            newData[i] = data_[i];
        }
        for (size_t i = pos; i < size_ - 1; ++i) {
            newData[i] = data_[i + 1];
        }
        delete[] data_;
        data_ = newData;
        --size_;
        return true;
    }
    template<typename U>
    friend std::ostream& operator<<(std::ostream& ostream, const Array<U>& array);
private:
    
    std::ostream& Ostream_;
    size_t capacity_, size_;
    T* data_;
    void CopyData(T* source, T* destination) {
        for (size_t i = 0; i < size_; ++i) {
            destination[i] = source[i];
        }
    }
};

template<typename T>
std::ostream& operator << (std::ostream& ostream, const Array<T>& array) {
    ostream.clear();
    ostream << "Result Array's capacity is " <<  array.capacity_  << " and size is " <<  array.size_;
    for(size_t i = 0; i < array.Size(); ++i) {
        if (i == 0){
            ostream << ", elements are: ";
        }
        ostream << array[i] << ((i < array.Size() - 1) ? ", " : "");
    }
    return ostream;
}

