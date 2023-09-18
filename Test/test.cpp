#include "pch.h"
#include "..//SmartPointers/UniquePointer.h"
#include "..//SmartPointers/SharedPointer.h"

template <class T>
void ChangeSharedPointer(SharedPointer<T> sharedPointer, T newValue)
{
	*sharedPointer = newValue;
}

TEST(UniquePointer, UniquePointer) {
	int value = 15, newValue = 9;
	int* simplePointer = new int(value);
	UniquePointer<int> uniquePointer(simplePointer);
	EXPECT_TRUE(simplePointer == nullptr);
	*uniquePointer = newValue;
	EXPECT_EQ(*uniquePointer, newValue);
}

TEST(SharedPointer, SharedPointer) {
	int value = 15, newValue = 9;
	int* simplePointer = new int(value);
	SharedPointer<int> sharedPointer(simplePointer);
	EXPECT_TRUE(simplePointer == nullptr);
	ChangeSharedPointer<int>(sharedPointer, newValue);
	EXPECT_EQ(*sharedPointer, newValue);
}
