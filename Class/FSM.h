#pragma once

#include <iostream>

class UState;
class UTransition;

class UFSM
{
public:
	UFSM();
	~UFSM();

	UState* States;
	UTransition* Transitions;

	void Process(int CurrentState, std::string CurrentCondition);

	std::string GetStateName(int InId);
};

