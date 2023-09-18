#pragma once
#include <utility>
template <typename T>
class UniquePointer final {
private:
    T* Pointer;
public:
    explicit UniquePointer(T*& pointer) 
    {
        Pointer = pointer;
        pointer = nullptr;
    }
    explicit UniquePointer(T*&& pointer)
    {
        Pointer = std::move(pointer);
    }

    ~UniquePointer() {
        delete Pointer;
    }
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;
    UniquePointer(UniquePointer&& other) : Pointer(other.Pointer) 
    {
        other.Pointer = nullptr;
    }
    UniquePointer& operator=(UniquePointer&& other) {
        if (this != &other) {
            delete Pointer;
            Pointer = other.Pointer;
            other.Pointer = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *Pointer;
    }

    operator bool()
    {
        return Pointer;
    }

    void Swap(UniquePointer<T>& other)
    {
        T* tmp1 = Pointer;
        Pointer = other.Pointer;
        other.Pointer = tmp1;
    }
};

template <class T>
UniquePointer<T> NewUniquePointer(T element = T())
{
    UniquePointer<T> newUniquePointer(new T(element));
    return newUniquePointer;
}
