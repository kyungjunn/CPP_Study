#pragma once
#include <string>

class UTransition
{
public:
	UTransition();
	~UTransition();

	int CurrentState;
	std::string Condition;
	int NextState;
};

