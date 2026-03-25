#pragma once
#ifndef __DynamicArray_H__
#define __DynamicArray_H__

class DynamicArray
{
public:
	DynamicArray()
	{
		Size = 0;
		Capacity = 1;
		Data = new int[Capacity];
	}

	// 생성자 오버로딩 (인자값 변경으로 함수 재사용)
	DynamicArray(int InitialCapacity = 10)
	{
		Size = 0;
		Capacity = InitialCapacity;
		Data = new int[InitialCapacity];
	}
	~DynamicArray()
	{
		delete[] Data;
		Data = nullptr;
	}

	// 크기 2배로 늘리기
	void PushBack(int InValue)
	{
		Size++;
		int* NewData = nullptr;

		// Size > Capacity
		// 저장공간 늘리기
		if (Size > Capacity)
		{
			Capacity = Capacity * 2;

			// 1. 늘어난 영역만큼 메모리 할당
			NewData = new int[Capacity];

			// 2. 원본 복제
			for (int i = 0; i < Size - 1; ++i)
			{
				NewData[i] = Data[i];
			}

			// 4. 원래 있던 걸 지운다.
			delete[] Data;

			// 5. 원래 데이터의 포인터에 새 데이터 포인터 연결
			Data = NewData;
		}

		// Size <= Capacity
		// 그냥 추가
		// 3. 새로 들어온 값 넣기
		Data[Size - 1] = InValue;
	}

	// define 
	// 함수 뒤에 const => 읽기전용(readonly)으로 값을 바꾸지 않겠다
	// 사이즈가 더 커지면 알아서 바꿔줌 -> size_t 64
	inline size_t GetSize() const
	{
		return Size;
	}

	inline size_t GetCapacity() const
	{
		return Capacity;
	}

	// operator overload
	// 자료형 앞에 붙으면 return 값 바꾸지 마라.
	const int& operator[](int index) const
	{
		return Data[index];
	}

	//[1][2][3][4] -> [1][2][4]
	void RemoveAt(int RemoveIndex)
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
	

protected:
	int* Data;
	size_t Size = 0;
	size_t Capacity = 1;
};

#endif // !__DynamicArray_H__
