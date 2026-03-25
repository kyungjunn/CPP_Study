#pragma once
#ifndef __DynamicArray_H__
#define __DynamicArray_H__

#include <stdexcept>

template<typename T>
class DynamicArray
{
public:
	/*DynamicArray()
	{
		Size = 0;
		Capacity = 1;
		Data = new T[Capacity];
	}*/

	// 생성자 오버로딩 (인자값 변경으로 함수 재사용)
	DynamicArray(int InitialCapacity = 10)
	{
		Size = 0;
		Capacity = InitialCapacity;
		Data = new T[InitialCapacity];
	}
	~DynamicArray()
	{
		delete[] Data;
		Data = nullptr;
	}

	// 크기 2배로 늘리기
	// 값도 안바꾸고 복사도 안하겠다.
	void PushBack(const T& InValue)
	{
		Size++;
		
		// Size > Capacity
		// 저장공간 늘리기
		// 이 부분은 ReSize 함수로 리팩토링 가능
		T* NewData = nullptr;
		if (Size > Capacity)
		{
			Capacity = Capacity * 2;

			// 1. 늘어난 영역만큼 메모리 할당
			NewData = new T[Capacity];

			// memcpy()
			// memmove()
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
	// 이거 정도는 알아.
	const T& operator[](int index) const
	{
		if (index < 0 || index > Size)
		{
			throw std::exception("인덱스 범위 벗어남");
		}
		return Data[index];
	}

	//[1][2][3][4] -> [1][2][4]
	void RemoveAt(int RemoveIndex)
	{
		if (RemoveIndex >= Size || RemoveIndex < 0)
		{
			throw std::out_of_range("인덱스가 범위를 벗어남");
		}

		// memmove()
		for (int i = RemoveIndex; i < Size; ++i)
		{
			Data[i] = Data[i + 1];
		}

		Size--;
	}
	
	void Clear()
	{
		Size = 0;
	}

protected:
	T* Data;
	size_t Size = 0;
	size_t Capacity = 1;

public:
	class Iterator // 역할 => 가리키는 것.
	{
	public:
		Iterator(T* InPointer) : Pointer(InPointer)
		{
		}

		// 전위증가
		Iterator& operator++()
		{
			Pointer++;
			return *this;
		}

		// 후위증가
		Iterator operator++(int)
		{
			Pointer++;
			return Iterator(Pointer);
		}
		
		bool operator!=(const Iterator& Other)
		{
			return (Pointer != Other.Pointer);
		}

		T& operator*()
		{
			return *Pointer;
		}

	protected:
		T* Pointer; // => 그래서 포인터로
	};

	Iterator begin()
	{
		return Iterator(Data);
	}
	Iterator end()
	{
		return Iterator(Data+Size);
	}
};

#endif // !__DynamicArray_H__
