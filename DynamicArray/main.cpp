// Standard Template Library
#include <iostream>
// random access, 추가 삭제 비용 큼.
#include <array>
#include <vector> // Container

// random access X, 추가 삭제 비용 적음.
#include <list>

// 정렬원하면
#include <algorithm>

int main()
{
	std::array<int, 5> IntArray{1, 1, 1, 1, 1};
	std::vector<int> IntDArray;
	std::list<int> IntList;
	IntDArray.push_back(1);
	IntDArray.push_back(2);
	IntDArray.push_back(3);
	IntDArray.push_back(4);

	IntList.push_back(1);
	IntList.push_back(2);
	IntList.push_back(3);
	IntList.push_back(4);

	// 전체 다 탐색해

	for (std::list<int>::iterator i = IntList.begin(); i != IntList.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	for (auto i = IntDArray.begin(); i != IntDArray.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	for (auto i : IntArray)
	{
		std::cout << i << std::endl;
	}

	// 거꾸로 
	for (auto i = IntDArray.rbegin(); i != IntDArray.rend(); ++i)
	{
		std::cout << *i << std::endl;
	}

	// 정렬 원하면 -> algorithm 헤더
	std::sort(IntDArray.begin(), IntDArray.end());

	// 리스트는 정렬 안됨.
	std::sort(IntList.begin(), IntList.end());
	// 그래서 내부적으로 정렬을 가지고 있음.
	IntList.sort();


	return 0;
}