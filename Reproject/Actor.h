#pragma once
class AActor
{
public:
	AActor(int InX = 0, int InY = 0, char InMesh = ' ');
	virtual ~AActor();

	virtual void BeginPlay();

	virtual void Tick();

	virtual void Render();

	virtual void SetActorLocation(int NewX, int NewY);

protected:
	int X;
	int Y;
	int ZOrder;
	char Mesh;
};

