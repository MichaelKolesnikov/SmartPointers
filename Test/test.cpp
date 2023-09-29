#include "pch.h"
#include "..//SmartPointers/UniquePointer.h"
#include "..//SmartPointers//SharedPointer.h"
#include "..//SmartPointers/SmartPointer.h"

#include <vector>

using namespace std;

template <class T>
void ChangeSmartPointer(SmartPointer<T> pointer, T newValue)
{
	*pointer = newValue;
}

class HardClass
{
private:
	vector<int> v;
public:
	HardClass()
	{
		v.resize(1000000);
	}

	int GetFirst()
	{
		return v[0];
	}
};

TEST(UniquePointer, UniquePointer) {
	// memory release check
	for (int i = 0; i < 1e3; ++i)
	{
		auto newPointer = NewUniquePointer(HardClass());
	}

	for (int i = 0; i < 1e4; ++i)
	{
		auto ptr = NewUniquePointer(rand());
		int newValue = rand();
		*ptr = newValue;
		EXPECT_EQ(*ptr, newValue);
	}
}

TEST(SharedPointer, SharedPointer) {
	// memory release check
	for (int i = 0; i < 1e3; ++i)
	{
		auto ptr = NewSharedPointer<HardClass>(HardClass());
	}

	for (int i = 0; i < 1e4; ++i)
	{
		auto ptr = NewSharedPointer(rand());
		int newValue = rand();
		*ptr = newValue;
		EXPECT_EQ(*ptr, newValue);
	}
}

TEST(SmartPointer, SmartPointer) {
	// memory release check
	for (int i = 0; i < 1e3; ++i)
	{
		auto newPointer = NewSmartPointer(HardClass());
	}

	for (int i = 0; i < 1e4; ++i)
	{
		auto ptr = NewSmartPointer(rand());
		int newValue = rand();
		ChangeSmartPointer(ptr, newValue);
		EXPECT_EQ(*ptr, newValue);
	}
}
