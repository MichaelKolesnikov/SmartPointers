#pragma once
#include <utility>

template <typename T>
class SmartPointer final {
private:
	T* Pointer;
	int* CountRef;

	SmartPointer() : Pointer(nullptr), CountRef(nullptr) {}
	explicit SmartPointer(T*& pointer) : CountRef(new int(1))
	{
		Pointer = pointer;
		pointer = nullptr;
	}
	explicit SmartPointer(T*&& pointer) : CountRef(new int(1))
	{
		Pointer = std::move(pointer);
	}

public:
	template <class T>
	friend SmartPointer<T> NewSmartPointer(const T&& element);
	~SmartPointer() {
		Reset();
	}
	SmartPointer(const SmartPointer<T>& other) : Pointer(other.Pointer), CountRef(other.CountRef)
	{
		if (CountRef) {
			(*CountRef)++;
		}
	}
	SmartPointer<T>& operator=(const SmartPointer<T>& other)
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
	SmartPointer(SmartPointer<T>&& other) noexcept : Pointer(other.Pointer), CountRef(other.CountRef)
	{
		other.Pointer = nullptr;
		other.CountRef = nullptr;
	}
	SmartPointer<T>& operator=(SmartPointer<T>&& other)
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

	void Swap(SmartPointer<T>& other)
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
SmartPointer<T> NewSmartPointer(const T&& element)
{
	SmartPointer<T> newPointer(new T(element));
	return newPointer;
}
