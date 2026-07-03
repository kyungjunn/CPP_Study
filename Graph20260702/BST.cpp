#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//class BinarySearchTree
//{
//private:
//	BSTNode* Root = nullptr;
//
//	BSTNode* InsertRec(BSTNode* Node, int Key)
//	{
//		if (Node == nullptr) // 더 이상 자식이 없을 때
//		{
//			return new BSTNode(Key); // 새로운 노드를 만들어줌
//		}
//
//		if (Key < Node->Key)
//		{
//			Node->Left = InsertRec(Node->Left, Key);
//		}
//		else if (Key > Node->Key)
//		{
//			Node->Right = InsertRec(Node->Right, Key);
//		}
//
//		return Node;
//	}
//
//	BSTNode* RemoveRec(BSTNode* Node, int Key)
//	{
//		if (Node == nullptr)
//		{
//			return nullptr;
//		}
//
//		if (Key < Node->Key)
//		{
//			Node->Left = RemoveRec(Node->Left, Key);
//		}
//		else if (Key > Node->Key)
//		{
//			Node->Right = RemoveRec(Node->Right, Key);
//		}
//		else
//		{
//			// 삭제 대상이 잎(leaf) 노드인 경우 (자식 X)
//			if (Node->Left == nullptr && Node->Right == nullptr)
//			{
//				delete Node;
//				return nullptr;
//			}
//
//			// 삭제 대상의 자식이 하나인 경우
//			if (Node->Left == nullptr)
//			{
//				BSTNode* RightChild = Node->Right;
//				delete Node;
//				return RightChild;
//			}
//			if (Node->Right == nullptr)
//			{
//				BSTNode* LeftChild = Node->Left;
//				delete Node;
//				return LeftChild;
//			}
//
//			// 삭제 대상의 자식이 두개인 경우
//			BSTNode* MinNode = FindMin(Node->Right);
//
//			Node->Key = MinNode->Key;
//			Node->Right = RemoveRec(Node->Right, MinNode->Key);
//
//		}
//
//		return Node;
//	}
//
//	BSTNode* FindMin(BSTNode* Node)
//	{
//		while (Node->Left)
//		{
//			Node = Node->Left;
//		}
//
//		return Node;
//	}
//public:
//	~BinarySearchTree()
//	{
//		Clear(Root);
//	}
//
//	void Insert(int Key)
//	{
//		Root = InsertRec(Root, Key);
//	}
//
//	bool Contains(int Key) const
//	{
//		BSTNode* Current = Root;
//
//		while (Current != nullptr)
//		{
//			if (Key == Current->Key)
//			{
//				return true;
//			}
//
//			Current = (Key < Current->Key) ? Current->Left : Current->Right;
//		}
//
//		return false;
//	}
//
//	void Remove(int Key)
//	{
//		Root = RemoveRec(Root, Key);
//	}
//
//	void Clear(BSTNode* Node)
//	{
//		if (Node == nullptr)
//		{
//			return;
//		}
//
//		Clear(Node->Left);
//		Clear(Node->Right);
//
//		delete Node;
//	}
//};

struct BSTNode
{
	int Key; // 노드의 값
	BSTNode* Left;
	BSTNode* Right;

	BSTNode(int Value) : Key(Value), Left(nullptr), Right(nullptr)
	{

	}
};

class BinarySearchTree2
{
private:
	BSTNode* Root = nullptr;


	void Clear(BSTNode* Node)
	{
		if (Node == nullptr)
		{
			return;
		}

		Clear(Node->Left);
		Clear(Node->Right);

		delete Node;
	}
public:
	~BinarySearchTree2()
	{
		Clear(Root);
	}

	void BuildFromSortedArray(const vector<int>& Values)
	{
		Clear(Root);
		Root = nullptr;

		if (Values.empty())
		{
			return;
		}

		int LastIndex = static_cast<int>(Values.size()) - 1;

		Root = BuildTree(Values, 0, LastIndex);
	}

	BSTNode* BuildTree(const vector<int>& Values, int Low, int High)
	{
		if (Low > High)
		{
			return nullptr;
		}

		// 중간
		int Mid = (Low + High) / 2;

		// 중간값으로 노드 생성
		BSTNode* Node = new BSTNode(Values[Mid]);

		// 왼쪽
		Node->Left = BuildTree(Values, Low, Mid - 1);

		// 오른쪽
		Node->Right = BuildTree(Values, Mid + 1, High);

		// 반환
		return Node;
	}

};

//int main()
//{	
//	vector<int> Data =
//	{
//		0, 1, 2, 3, 4, 5 ,6, 7, 8, 9
//	};
//
//	// 재정렬 -> BST 들어가기 좋은 형태로 정렬
//	// 배열을 통짜로 BST 노드 형태로 만들기
//
//	BinarySearchTree2 Bst2;
//	Bst2.BuildFromSortedArray(Data);
//
//
//	return 0;
//}
