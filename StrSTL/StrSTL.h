#pragma once
#ifndef __STRSTL__
#define __STRSTL__

#include <stdexcept>

class StrSTL
{
public:
	StrSTL()
	{
		Length = 0;
		Data = new char[1];
		Data[0] = '\0';
	}
	StrSTL(const char* InString)
	{
		Length = 0;
		// 길이 세기
		while (InString[Length] != '\0')
		{
			Length++;
		}

		Data = new char[Length + 1];

		// 복사
		for (int i = 0; i < Length; i++)
		{
			Data[i] = InString[i];
		}

		Data[Length] = '\0'; // 문자열 끝에 null
	}
	~StrSTL()
	{
		delete[] Data;
		Data = nullptr;
	}

	//void PushBack(const T& InStr)
	//{
	//	Length = 0;
	//	// 길이 세기
	//	while(InStr[Length] != '\0')
	//	{ 
	//		Length++;
	//	}

	//	Data = new T[Length + 1];

	//	// 직접 복사
	//	for (int i = 0; i < Length; i++)
	//	{
	//		Data[i] = InStr[i];
	//	}

	//	Data[Length] = '\0'; // 문자열 끝에 null
	//}

	inline size_t GetLength() const
	{
		return Length;
	}

	// 합치기
	StrSTL operator+(const StrSTL& RHS)
	{
		size_t NewLength;
		NewLength = Length + RHS.Length;
		
		char* NewData = new char[NewLength + 1];

		// 앞 문자열 복사
		for (int i = 0; i < Length; ++i)
		{
			NewData[i] = Data[i];
		}

		// 뒤 문자열 복사
		for (int i = 0; i < RHS.Length; ++i)
		{
			NewData[Length + i] = RHS.Data[i];
		}

		NewData[NewLength] = '\0';
		
		// 소멸하려면 이 안에 따로 String 클래스 만들어서 소멸할 것.  
		//delete[] NewData;

		return NewData; 
	}

	char* Data;
	size_t Length;
};

#endif // !__STRSTL__