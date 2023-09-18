#pragma once
#include <utility>

template <typename T>
class SharedPointer final {
private:
	T* Pointer;
	int* CountRef;

public:
	SharedPointer() : Pointer(nullptr), CountRef(nullptr) {}
	explicit SharedPointer(T*& pointer) : CountRef(new int(1))
	{
		Pointer = pointer;
		pointer = nullptr;
	}
	explicit SharedPointer(T*&& pointer) : CountRef(new int(1))
	{
		Pointer = std::move(pointer);
	}

	~SharedPointer() {
		Reset();
	}
	SharedPointer(const SharedPointer<T>& other) : Pointer(other.Pointer), CountRef(other.CountRef)
	{
		if (CountRef) {
			(*CountRef)++;
		}
	}
	SharedPointer<T>& operator=(const SharedPointer<T>& other)
	{
		if (this != &other) {
			Reset();
			Pointer = other.Pointer;
			CountRef = other.CountRef;

			if (CountRef) {
				(*CountRef)++;
			}
		}
		return *this;
	}
	SharedPointer(SharedPointer<T>&& other) noexcept : Pointer(other.Pointer), CountRef(other.CountRef)
	{
		other.Pointer = nullptr;
		other.CountRef = nullptr;
	}
	SharedPointer<T>& operator=(SharedPointer<T>&& other)
	{
		if (this != &other) {
			Reset();

			Pointer = other.Pointer;
			CountRef = other.CountRef;

			other.Pointer = nullptr;
			other.CountRef = nullptr;
		}
		return *this;
	}

	T& operator*() const
	{
		return *Pointer;
	}

	operator bool()
	{
		return CountRef && CountRef > 0;
	}

	int UseCount() const
	{
		return (CountRef ? *CountRef : 0);
	}

	void Reset()
	{
		if (CountRef) {
			(*CountRef)--;

			if (*CountRef == 0)
			{
				delete Pointer;
				delete CountRef;
				Pointer = nullptr;
				CountRef = nullptr;
			}
		}
	}

	bool Unique() const
	{
		if (CountRef)
		{
			return *CountRef == 1;
		}
		return false;
	}

	void Swap(SharedPointer<T>& other)
	{
		T* tmp1 = Pointer;
		Pointer = other.Pointer;
		other.Pointer = tmp1;
		int* tmp2 = CountRef;
		CountRef = other.CountRef;
		other.CountRef = tmp2;
	}
};

template <class T>
SharedPointer<T> NewSharedPointer(T element = T())
{
	SharedPointer<T> newSharedPointer(new T(element));
	return newSharedPointer;
}
