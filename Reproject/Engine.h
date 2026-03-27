#pragma once

class UWorld;

class UEngine
{
protected:
	UEngine();
		
	static UEngine* Instance;

public:
	virtual ~UEngine();

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

	bool bIsRunning = true;
};

#define UEGINE	UEngine::GetInstance()

