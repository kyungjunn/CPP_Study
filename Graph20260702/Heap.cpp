#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//. 최대힙
class PriorityQueue
{
private:
	vector<int> Heap;

public:
	void Push(int Data) // 삽입
	{
		Heap.push_back(Data);

		int Now = Heap.size() - 1; // 배열의 맨 마지막 인덱스

		while (Now > 0)
		{
			int Next = (Now - 1) / 2; // 부모 인덱스 저장 (현재 위치 가져오는 공식)
			if (Heap[Now] <= Heap[Next]) // 노드의 값이 같거나 작으면 건너뜀.
			{
				break;
			}

			// Swap 교환 
			int Temp = Heap[Now];
			Heap[Now] = Heap[Next];
			Heap[Next] = Temp;
			Now = Next;
		}
	}

	int Top() const // 맨위 엿보기
	{
		return Heap[0];
	}

	void Pop() // 맨위 삭제
	{
		if (Heap.empty())
		{
			return;
		}

		Heap[0] = Heap.back(); // 배열의 맨 마지막 놈을 맨 처음으로 덮어씌우기.	
		Heap.pop_back(); // 맨 위 삭제(맨 마지막놈)

		int LastIndex = Heap.size() - 1; // 마지막 인덱스 저장

		int Now = 0;
		while (true)
		{
			int Left = 2 * Now + 1; // 왼쪽 자식 인덱스 (공식 : 2*i + 1, 2*i + 2) 
			int Right = 2 * Now + 2; // 오른쪽
			int Next = Now;

			if (Left <= LastIndex && Heap[Next] < Heap[Left])
			{
				Next = Left; // 왼쪽 자식이 더 크면 왼쪽을 다음 검사 대상으로 
			}
			if (Right <= LastIndex && Heap[Next] < Heap[Right])
			{
				Next = Right; // 오른쪽 자식이 더 크면 오른쪽을 다음 검사 대상으로
			}
			if (Next == Now)
			{
				break;
			}

			// 교환 
			int Temp = Heap[Now];
			Heap[Now] = Heap[Next];
			Heap[Next] = Temp;
			Now = Next;
		}
	}

	int Size() const // 트리(배열) 크기 
	{
		return Heap.size();
	}
};



int main()
{

	PriorityQueue PQ;
	PQ.Push(20);

	while (PQ.Size() > 0)
	{
		int Temp = PQ.Top();
		cout << Temp << endl;
		PQ.Pop();
	}



	return 0;
}