#include <iostream>

using namespace std;

class State
{
public:
	int ID;
	enum StateName{ 배회, 추격, 공격, 죽음 };
};

class Transition
{
public:
	int CurrentState;
	string condition;
	int NextState;
};

// FSM 이 State와 Transition을 가지고 있다. O
// State가 FSM을 가지고 있다. X
// FSM has a State. << has a 관계
// 자연어로 말이 되야 함.
class FSM
{
public:
	State State[4];
	Transition Transition[5];

	void Tick();
};
int main()
{
	FSM EnemyFSM;

	EnemyFSM.Tick();

	return 0;
}


