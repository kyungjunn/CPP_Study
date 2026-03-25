// Standard Template Library
#include <iostream>
#include <vector> // Container
#include "DynamicArray.h"

using namespace std;

int main()
{
	DynamicArray<int> IntArray;

	IntArray.PushBack(1);

	for (int i = 0; i < IntArray.GetSize(); ++i)
	{
		cout << IntArray[i] << endl;
		// IntArray.Data[i]
	}


	return 0;
}