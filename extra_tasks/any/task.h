#pragma once

#include <typeinfo>
#include <type_traits>
#include <new>
#include <memory>
#include <stdexcept>

class Any;

class AnyValueBase {
public:
    virtual ~AnyValueBase() = default;
    virtual const std::type_info& type() const = 0;
    virtual std::unique_ptr<AnyValueBase> clone() const = 0;
};

template<typename T>
class AnyValue : public AnyValueBase {
    T value;

public:
    AnyValue(const T& v) : value(v) {}

    const T& getValue() const {
        return value;
    }

    const std::type_info& type() const override {
        return typeid(T);
    }

    std::unique_ptr<AnyValueBase> clone() const override {
        return std::make_unique<AnyValue<T>>(*this);
    }
};

class Any {
    std::unique_ptr<AnyValueBase> ptr;
public:
    Any() = default;

    template<typename T>
    Any(const T& value) : ptr(std::make_unique<AnyValue<T>>(value)) {}

    Any(const Any& other) : ptr(other.ptr ? other.ptr->clone() : nullptr) {}

    Any(Any&& other) noexcept = default;
    Any& operator=(Any other) {
        ptr = std::move(other.ptr);
        return *this;
    }

    bool Empty() const {
        return ptr == nullptr;
    }
    
    void Reset() {
        ptr.reset();
    }

    void Swap(Any& other) noexcept {
        ptr.swap(other.ptr);
    }

    template<typename T>
    const T& Value() const {    
        if (!ptr || ptr->type() != typeid(T)) {
            throw std::bad_cast();
        }
        auto valPtr = dynamic_cast<AnyValue<T>*>(ptr.get());
        return valPtr->getValue();
    }
};


