#include <iostream>
#include "StringUtil.h"

using namespace std;

int main()
{
	char Temp[100] = "Hello World";

	int StringLength = Length(Temp, 100);
	cout << StringLength << endl;

	Replace(Temp, 100, 'l', 'f');

	return 0;
}