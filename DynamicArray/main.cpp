// Standard Template Library
#include <iostream>
#include <vector> // Container
#include "DynamicArray.h"

using namespace std;

void Test(int A, int B = 0, int C = 1)
{
	cout << A << B << C;
}

int main()
{
	Test(1);

	return 0;

	std::vector<int> IntArray;
	DynamicArray OurArray(10);


	for (int i = 0; i < 10; ++i)
	{
		cout << OurArray.GetSize() << endl;
		cout << OurArray.GetCapacity() << endl;
		cout << "-----------------" << endl;

		OurArray.PushBack(i);
	}
	

	//for (int i = 0; i < OurArray.GetSize(); ++i)
	//{
	//	//cout << OurArray.Data[i];
	//	cout << OurArray[i];
	//}


	return 0;
}