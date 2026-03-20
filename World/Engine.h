#pragma once

class UWorld;

class UEngine
{
public:
	UEngine();
	~UEngine();

	void Init();
	void Run();
	void Term();
	void Input();
	void Tick();
	void Render();

	UWorld* World;

	bool bIsRunning;
};

