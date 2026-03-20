#pragma once
class AActor
{
public:
	AActor();
	~AActor();

	int X;
	int Y;
	int Mesh;

	void Move(int X, int Y);
};

