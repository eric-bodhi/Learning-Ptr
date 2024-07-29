#pragma once

#include <memory>
#include <utility>

// @TODO Create new default deleter from scratch
template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* rawPtr = nullptr) : ptr(rawPtr) {
    }

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    T* get() {
        return ptr;
    }

    const T* get() const {
        return ptr;
    }

    void swap(UniquePtr<T>& other) {
        std::swap(ptr, other.ptr);
    }
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    return UniquePtr(new T(std::forward<Args>(args)...));
}
