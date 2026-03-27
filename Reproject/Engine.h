#pragma once

#include <Windows.h>

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

	// 원래는 Renderer 
	HANDLE ScreenBufferHandle[2]; // 2장그릴거니까
	int ActiveScreenBufferIndex = 0; // 몇 번째꺼

	void InitBuffer();
	void Clear(); // 지우기
	void Render(int InX, int InY, char InMesh); // 그리기
	void Flip(); // 왔다갔다
	void TermBuffer();

protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	bool bIsRunning = true;
};

#define GENGINE	UEngine::GetInstance()

