//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW

#include <iostream>
#include <vector>

#include "UniquePointer.h"
#include "SharedPointer.h"

using namespace std;

int main()
{
	auto pointer = NewSharedPointer<int>(6);
	cout << *pointer << endl;

	return 0;
	/*_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();*/
}
