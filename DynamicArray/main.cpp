// Standard Template Library
#include <iostream>
#include <vector> // Container
#include "DynamicArray.h"

using namespace std;

class FVector2D
{
public:
	FVector2D(int InX = 0, int InY = 0) : X(InX), Y(InY)
	{
	}
	int X;
	int Y;

	// operator overload
	FVector2D operator+(FVector2D RHS) // RightHandSide
	{
		FVector2D New;
		New.X = X + RHS.X;
		New.Y = Y + RHS.Y;

		return New;
	}
};
int main()
{
	DynamicArray<int> IntArray;

	IntArray.PushBack(1);
	IntArray.PushBack(2);
	IntArray.PushBack(3);
	IntArray.PushBack(4);

	// STL 이거는(사용) 할 줄 알아야 돼. 다른 거 모르겠으면 넘겨.
	for (DynamicArray<int>::Iterator iter = IntArray.begin(); iter.operator!=(IntArray.end());
		iter++)
	{
		cout << *iter << endl;
	}

	for (auto Data : IntArray)
	{
		cout << Data << endl;
	}

	/*FVector2D First(0, 0);
	FVector2D Second(2, 2);
	FVector2D Three = Second;

	Second.X = 4;
	Second.Y = 4;

	cout << Second.X << endl;
	cout << Three.X << endl;*/

	//FVector2D Three = First + Second;

	return 0;
}