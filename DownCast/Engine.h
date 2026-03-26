#pragma once
#include <vector>

class UWorld;
class AActor;

class UEngine
{
protected:
	UEngine();

	static UEngine* Instance;

public:
	~UEngine();

	static UEngine* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new UEngine();
		}
		return Instance;
	}
	void Init();
	void Term();

	void Run();

	inline UWorld* GetWorld()
	{
		return World;
	}

	static int KeyCode;

protected:
	void Input();
	void Tick();
	void Render();
	 
	class UWorld* World;

	bool bIsRunning : 1; // 비트 단위로 쓰겠다. 1비트 
};

#define GEngine		UEngine::GetInstance()