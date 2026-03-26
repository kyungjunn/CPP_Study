#pragma once
#include <vector>

class UWorld;
class AActor;

class UEngine
{
public:
	UEngine();
	~UEngine();

	void Init();
	void Term();

	void Run();

	inline UWorld* GetWorld()
	{
		return World;
	}
protected:
	void Input();
	void Tick();
	void Render();
	 
	class UWorld* World;

	bool bIsRunning : 1; // 비트 단위로 쓰겠다. 1비트 
};

