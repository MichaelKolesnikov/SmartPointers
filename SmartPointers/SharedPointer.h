#pragma once
#include "UniquePointer.h"

template <class T>
class SharedPointer
{
private:
    UniquePointer<T>* pointerToUniquePointer;
    int* CountRef;

    explicit SharedPointer(UniquePointer<T>&& pointer)
    {
        pointerToUniquePointer = &NewUniquePointer<T>(*pointer);
        CountRef = new int(0);
    }

public:
    template <class T>
    friend SharedPointer<T> NewSharedPointer(const T&& element);

    template <class T>
    friend SharedPointer<T> NewSharedPointer(const T& element);

    ~SharedPointer() 
    {
        Reset();
    }
    SharedPointer(const SharedPointer& other) : pointerToUniquePointer(other.pointerToUniquePointer), CountRef(other.CountRef)
    {
        if (CountRef) {
            (*CountRef)++;
        }
    }
    SharedPointer& operator=(const SharedPointer& other)
    {
        if (this != &other) 
        {
            Reset();
            pointerToUniquePointer = other.pointerToUniquePointer;
            CountRef = other.CountRef;

            if (CountRef) 
            {
                (*CountRef)++;
            }
        }
        return *this;
    }
    SharedPointer(SharedPointer&& other) : pointerToUniquePointer(other.pointerToUniquePointer), CountRef(other.CountRef)
    {
        other.pointerToUniquePointer = nullptr;
        other.CountRef = nullptr;
    }
    SharedPointer& operator=(SharedPointer&& other)
    {
        if (pointerToUniquePointer != other.pointerToUniquePointer)
        {
            Reset();
            pointerToUniquePointer = other.pointerToUniquePointer;
            *CountRef = other.CountRef;
            other.CountRef = nullptr;
            other.pointerToUniquePointer = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *(*pointerToUniquePointer);
    }

    operator bool()
    {
        return pointerToUniquePointer;
    }

    void Reset()
    {
        if (CountRef) 
        {
            (*CountRef)--;

            if (*CountRef == 0)
            {
                delete pointerToUniquePointer;
                delete CountRef;
                pointerToUniquePointer = nullptr;
                CountRef = nullptr;
            }
        }
    }

    void Swap(SharedPointer<T>& other)
    {
        uniquePointer.Swap(other.uniquePointer);
    }
};

template <class T>
SharedPointer<T> NewSharedPointer(const T&& element = T())
{
    return SharedPointer<T>(NewUniquePointer(element));
}

template <class T>
SharedPointer<T> NewSharedPointer(const T& element)
{
    return SharedPointer<T>(NewUniquePointer(element));
}


