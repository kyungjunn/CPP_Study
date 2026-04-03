#include "Engine.h"
#include "World.h"
#include "ResourceManager.h"
#include <string>

#include "SDL.h"

UEngine* UEngine::Instance = nullptr;

UEngine::UEngine()
{
	Init();
}

UEngine::~UEngine()
{
}

void UEngine::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	MyWindow = SDL_CreateWindow("Hello", 100, 100, 1024, 720, SDL_WINDOW_SHOWN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, 
		SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC 
		|| SDL_RENDERER_TARGETTEXTURE);

	// 그래픽카드 같은 게 없을 때 SOFTWARE를 사용 ( 더 느려짐)
	//MyRenderer = SDL_CreateRenderer(MyWindow, -1, 
		//SDL_RENDERER_SOFTWARE || SDL_RENDERER_PRESENTVSYNC);

	ResourceManager = new UResourceManager();

	bool bIsRunning = true;

	InitBuffer();

	World = new UWorld();
}

void UEngine::Term()
{
	// 만들었으면 지우기
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();

	delete World;
	TermBuffer();
	World = nullptr;

	delete ResourceManager;
}

void UEngine::Run()
{
	World->BeginPlay();

	Uint64 LastTime;
	while (bIsRunning)
	{
		LastTime = SDL_GetTicks64();

		SDL_PollEvent(&MyEvent);
		Input();
		Tick();
		Render();
		
		DeltaSeconds = (float)(SDL_GetTicks64() - LastTime) / 1000.0f; // m/s
		// SDL_Log("FPS : %f s", DeltaSeconds);
	}
}

void UEngine::Stop()
{
	bIsRunning = false;
}

void UEngine::InitBuffer()
{
	// 만들어줘
	ScreenBufferHandle[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
		NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	ScreenBufferHandle[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
		NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	ConsoleCursorInfo.dwSize = 1;
	ConsoleCursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(ScreenBufferHandle[0], &ConsoleCursorInfo);
	SetConsoleCursorInfo(ScreenBufferHandle[1], &ConsoleCursorInfo);
}

void UEngine::Clear()
{
	// Drawcall 
	// CPU가 하는 건 GPU 한테 할 일을 적는 거
	// GPU 한테 보낼 명령어 모음(아직 안보낸거)
	SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 255);

	// 그리기 전에 지우기
	SDL_RenderClear(MyRenderer);

	// Console Clear
	DWORD DW;
	// 지금 그리고 있는 거 지워줘
	FillConsoleOutputCharacter(ScreenBufferHandle[ActiveScreenBufferIndex], ' ',
		80 * 25, COORD{0, 0}, &DW);
}

void UEngine::Render(int InX, int InY, char InMesh)
{
	char MeshString[2] = { 0 , };
	MeshString[0] = InMesh;

	SetConsoleCursorPosition(ScreenBufferHandle[ActiveScreenBufferIndex],
		COORD{ (SHORT)InX, (SHORT)InY });
	WriteFile(ScreenBufferHandle[ActiveScreenBufferIndex], MeshString,
		1, NULL, NULL);
}

void UEngine::Render(int InX, int InY, int R, int G, int B)
{
	int TileSize = 30;
	SDL_SetRenderDrawColor(MyRenderer, R, G, B, 255);
	//SDL_RenderDrawPoint(MyRender, InX, InY);
	SDL_Rect MyRect = { InX * TileSize, InY * TileSize, TileSize, TileSize };
	SDL_RenderFillRect(MyRenderer, &MyRect);
}

// 텍스처 Render
void UEngine::Render(int InX, int InY, SDL_Texture* InTexture)
{
	int TileSize = 30;

	SDL_Rect MyRect = { InX * TileSize, InY * TileSize, TileSize, TileSize };
	SDL_RenderCopy(MyRenderer, InTexture, nullptr,&MyRect);
}

void UEngine::Flip()
{
	SetConsoleActiveScreenBuffer(ScreenBufferHandle[ActiveScreenBufferIndex]);
	ActiveScreenBufferIndex = !ActiveScreenBufferIndex; // 0, 1 왔다갔다 옛날스타일
}

void UEngine::TermBuffer()
{
	// 만들었으면 지우자.
	CloseHandle(ScreenBufferHandle[0]);
	CloseHandle(ScreenBufferHandle[1]);
}

void UEngine::Input()
{
	/*if (_kbhit())
	{
		KeyCode = _getch();
	}*/
}

void UEngine::Tick()
{
	if (MyEvent.type == SDL_QUIT) // 이벤트에서 type이 창 끄는 걸 눌렀냐
	{
		bIsRunning = false;
	}

	World->Tick();
}

void UEngine::Render()
{
	World->Render();

	// 보내기 CPU -> GPU
	// 많이 보낼 수록 느려짐.
	SDL_RenderPresent(MyRenderer);
}
