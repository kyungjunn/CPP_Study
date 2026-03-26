#include <iostream>
#include "StrSTL.h"
#include "String.h"

using namespace std;

int main()
{
	StrSTL String1("qw");
	StrSTL String2("er");
	StrSTL String3 = String1 + String2;
	
	cout << String3.Data;
	
	String s1 = "qwer";
	String s2 = "asdf";
	String s3 = s1 + s2;

	cout << s3.GetPointer();
	
	return 0;
}