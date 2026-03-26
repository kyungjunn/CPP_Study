#include <iostream>
#include "String.h"

using namespace std;

int main()
{
	String s1 = "qwer";
	String s2 = "asdf";
	String s3 = s1 + s2;

	cout << s3.GetPointer();
	
	return 0;
}