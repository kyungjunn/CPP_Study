#pragma once
#ifndef __STRSTL__
#define __STRSTL__

#include <stdexcept>

template<typename T>
class StrSTL
{
public:
	StrSTL()
	{
		Length = 0;
		Data = new T[1];
		Data[0] = '\0';
	}
	StrSTL(const T* InStr)
	{
		Length = 0;
		// 길이 세기
		while (InStr[Length] != '\0')
		{
			Length++;
		}

		Data = new T[Length + 1];

		// 직접 복사
		for (int i = 0; i < Length; i++)
		{
			Data[i] = InStr[i];
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
	StrSTL operator+(StrSTL RHS)
	{
		size_t NewLength;
		NewLength = Length + RHS.Length;

		T* NewData = new T[NewLength];

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

		delete[] Data;

		return NewData;
	}

	T* Data;
	size_t Length;
};

#endif // !__STRSTL__