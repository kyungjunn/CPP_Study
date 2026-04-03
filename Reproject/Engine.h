#pragma once

#include <Windows.h>
#include "SDL.h"

// 사용할 라이브러리 파일 추가
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

class UWorld;
class UResourceManager;

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

	void Stop();

	inline UWorld* GetWorld()
	{
		return World;
	}
	
	// 원래는 Renderer 
	HANDLE ScreenBufferHandle[2]; // 2장그릴거니까
	int ActiveScreenBufferIndex = 0; // 몇 번째꺼

	void InitBuffer();
	void Clear(); // 지우기
	void Render(int InX, int InY, char InMesh);
	void Render(int InX, int InY, int R, int G, int B);
	void Render(int InX, int InY, SDL_Texture* InTexture);
	void Flip(); // 왔다갔다
	void TermBuffer();

	inline const SDL_Event& GetEvent()
	{
		return MyEvent;
	}

	inline float GetDeltaSeconds() const
	{
		return DeltaSeconds;
	}

	inline SDL_Renderer* GetRenderer() const
	{
		return MyRenderer;
	}

	inline SDL_Window* GetWindow() const
	{
		return MyWindow;
	}

	inline UResourceManager* GetResourceManager() const
	{
		return ResourceManager;
	}

protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	bool bIsRunning = true;

	SDL_Window* MyWindow;
	SDL_Renderer* MyRenderer;	
	SDL_Event MyEvent;
	SDL_AudioSpec wav_spec;


	float DeltaSeconds;
	
	UResourceManager* ResourceManager;
};

#define GEngine			UEngine::GetInstance()

