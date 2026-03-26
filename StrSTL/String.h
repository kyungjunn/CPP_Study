#pragma once

#include <iostream>


class String
{
public:
	String()
	{
		Data = new char[1];
		Data[0] = '\0';
		Length = 0;
	}

	//constructor overload
	String(const char* InString)
	{
		Length = CountLength(InString);
		Data = new char[Length + 1];
		CopyString(InString);
	}

	// copy constructor  (자기 형태를 복사, 기본은 안 만들어도 동작을 함)
	String(const String& Other)
	{
		Length = Other.GetLength();
		Data = new char[Other.GetLength() + 1];
		CopyString(Other.GetPointer());
	}

	// C++ 17
	// String(const String& Other) = delete;

	bool operator==(const String& Other)
	{
		if (Length != Other.GetLength())
		{
			return false;
		}

		for (int i = 0; i < Length; ++i)
		{
			if (Data[i] != Other.Data[i])
			{
				return false;
			}
		}

		return true;
	}
	~String()
	{
		delete[] Data; 
		Data = nullptr;
	}

	//operator overloading
	String operator+(const String& RHS) const
	{
		size_t NewLength = Length + RHS.GetLength(); 
		char* NewResult = new char[NewLength];

		// 앞에 있는거 
		for (int i = 0; i < Length; ++i)
		{
			NewResult[i] = Data[i];
		}

		// 뒤에 있는거
		int j = 0;
		for (int i = (int)Length; i < NewLength; ++i)
		{
			NewResult[i] = RHS.Data[j];
			j++;
		}

		NewResult[NewLength] = '\0';

		return String(NewResult);
	}

	inline const char* GetPointer() const
	{
		return Data;
	}

	inline size_t GetLength() const
	{
		return Length;
	}

protected:
	char* Data;
	size_t Length = 0;

	size_t CountLength(const char* InString) const
	{
		int Count = 0;
		while (InString[Count] != '\0')
		{
			Count++;
		}

		return Count;
	}

	void CopyString(const char* InString)
	{
		for (int i = 0; i < Length; ++i)
		{
			Data[i] = InString[i];
		}

		Data[Length] = '\0';
	}

};
