#pragma once
#ifndef __SDYNAMICARRAY_H__
#define __SDYNAMICARRAY_H__


class SDynamicArray
{
public:
	SDynamicArray() 
	{
		Size = 0;
		Capacity = 1;
		Data = new int[1];
	}
	// 생성자 오버로딩
	SDynamicArray(int InitialCapacity = 10)
	{
		Size = 0;
		Capacity = InitialCapacity;
		Data = new int[InitialCapacity];
	}
	~SDynamicArray()
	{
		delete[] Data;
		Data = nullptr;
	}

	void PushBack(int InValue)
	{
		Size++;
		int* NewData = nullptr;

		if (Size > Capacity)
		{
			Capacity = Capacity * 2;
			NewData = new int[Capacity];

			for (int i = 0; i < Size; ++i)
			{
				NewData[i] = Data[i];
			}

			delete[] Data;

			Data = NewData;
		}

		Data[Size - 1] = InValue;
	}
	inline size_t GetSize() const 
	{
		return Size;
	}

	inline size_t GetCapacity() const 
	{
		return Capacity;
	}

	int	RemoveAt(int RemoveIndex)
	{
		if (RemoveIndex > Size || RemoveIndex < 0)
		{
			return;
		}

		for (int i = RemoveIndex; i < Size; ++i)
		{
			Data[i] = Data[i + 1];
		}

		Size--;
	}

	int* Data;
	size_t Size;
	size_t Capacity;
};
#endif // !1
