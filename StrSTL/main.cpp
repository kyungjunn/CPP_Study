#include <iostream>
#include "StrSTL.h"

using namespace std;

int main()
{
	StrSTL<char> String1("qw");
	StrSTL<char> String2("er");
	StrSTL<char> String3 = String1 + String2;
	
	cout << String3.Data;
	
	
	return 0;
}