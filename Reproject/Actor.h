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

	inline const int GetZOrder() 
	{
		return ZOrder;
	}

protected:
	int X;
	int Y;

	int R;
	int G;
	int B;

	int ZOrder;
	char Mesh;
};

