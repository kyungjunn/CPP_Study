#include "FSM.h"

#include "State.h"
#include "Transition.h"

#include <iostream>

UFSM::UFSM()
{
	States = new UState[4];
	Transitions = new UTransition[5];

	States[0].ID = 1;
	States[0].StateName = "배회";

	States[1].ID = 2;
	States[1].StateName = "추격";

	States[2].ID = 3;
	States[2].StateName = "공격";

	States[3].ID = 4;
	States[3].StateName = "죽음";

	Transitions[0].CurrentState = 1;
	Transitions[0].Condition = "적발견";
	Transitions[0].NextState = 2;

	Transitions[1].CurrentState = 2;
	Transitions[1].Condition = "적놓침";
	Transitions[1].NextState = 1;

	Transitions[2].CurrentState = 2;
	Transitions[2].Condition = "사정거리접근";
	Transitions[2].NextState = 3;

	Transitions[3].CurrentState = 3;
	Transitions[3].Condition = "사정거리이탈";
	Transitions[3].NextState = 2;

	Transitions[4].CurrentState = 3;
	Transitions[4].Condition = "HP없음";
	Transitions[4].NextState = 4;
}

UFSM::~UFSM()
{
	delete[] States;
	States = nullptr;
	delete[] Transitions;
	Transitions = nullptr;
}

void UFSM::Process(int CurrentState, std::string CurrentCondition)
{
	for (int i = 0; i < 5; ++i)
	{
		if (Transitions[i].CurrentState == CurrentState && 
			Transitions[i].Condition == CurrentCondition)
		{
			std::cout << Transitions[i].NextState;

			return;
		}
	}
	std::cout << GetStateName(CurrentState) << std::endl;
}

std::string UFSM::GetStateName(int InId)
{
	for (int i = 0; i < 4; ++i)
	{
		if (States[0].ID == InId)
		{
			return States[i].StateName;
		}
	}
	return "상태없음";
}
