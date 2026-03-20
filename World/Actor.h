#pragma once
class AActor
{
public:
	AActor();
	~AActor();

private:
	int X;
	int Y;
	int Mesh;	

public:
	int GetX();
	// void SetX(int InX);
	int GetY();
	void SetY(int InY);

	virtual void Move();

	/* virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(); */

};