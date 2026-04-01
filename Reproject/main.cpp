#include <iostream>
#include "Engine.h"
#include "World.h"

#include "SDL.h"
#include "SDL_main.h"

// 사용할 라이브러리 파일 추가
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

using namespace std;

int SDL_main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("Hello", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	while (1)
	{
		SDL_Event MyEvent;
		SDL_PollEvent(&MyEvent); // 이벤트가 있냐 계속 물어보는거임

		if (MyEvent.type == SDL_QUIT) // 이벤트에서 type이 창 끄는 걸 눌렀냐
		{
			break;
		}
	}

	SDL_DestroyWindow(MyWindow);

	SDL_Quit();

	return 0;
}

//int main()
//{
//	//GENGINE->GetInstance();
//	//UEngine* MyEngine = UEngine::GetInstance();
//
//	// 엔진을 먼저 키고 -> 월드를 받아와서 -> 맵 이름 파일로 맵을 로딩
//	GENGINE->GetWorld()->Load("level01.txt");
//
//	// 그리고 실행
//	GENGINE->Run();
//
//	return 0;
//}