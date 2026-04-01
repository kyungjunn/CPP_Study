#include <iostream>
#include "Engine.h"
#include "World.h"

#include <random>

#include "SDL.h"
#include "SDL_main.h"

// 사용할 라이브러리 파일 추가
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

using namespace std;

int SDL_main(int argc, char* argv[])
{
	// rand 보다 좀 더 좋은 난수를 뽑기 위해
	// 난수 만들어주는 애
	std::random_device RandomDevice;
	// 랜덤 알고리즘 
	std::mt19937 RandomGenerator(RandomDevice());
	// 넓은 공간으로 뽑는 거 
	std::uniform_int_distribution<int> DistX(0, 640);
	std::uniform_int_distribution<int> DistY(0, 480);

	std::uniform_int_distribution<int> DistR(0, 255);
	std::uniform_int_distribution<int> DistG(0, 255);
	std::uniform_int_distribution<int> DistB(0, 255);
	std::uniform_int_distribution<int> DistA(0, 255);

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("Hello", 100, 100, 1024, 720, SDL_WINDOW_SHOWN);

	// GPU, 붓
	SDL_Renderer* MyRender = SDL_CreateRenderer(MyWindow, -1, 0);

	SDL_Rect Square = { 100, 100, 50, 50 };

	while (1)
	{
		SDL_Event MyEvent;
		SDL_PollEvent(&MyEvent); // 이벤트가 있냐 계속 물어보는거임

		if (MyEvent.type == SDL_QUIT) // 이벤트에서 type이 창 끄는 걸 눌렀냐
		{
			break;
		}
		// Drawcall 
		// CPU가 하는 건 GPU 한테 할 일을 적는 거
		// GPU 한테 보낼 명령어 모음(아직 안보낸거)
		SDL_SetRenderDrawColor(MyRender, 255, 255, 255, 255);

		// 그리기 전에 지우기
		SDL_RenderClear(MyRender);
		
		// 사각형 채워서 그리기 
		//SDL_SetRenderDrawColor(MyRender, 255, 255, 0, 255);
		//SDL_RenderFillRect(MyRender, &Square);
		//SDL_RenderDrawRect(MyRender, &Square);

		// 강사님 버전 - 사각형 선으로 그리기
		// 랜덤으로 
		/*for (int i = 0; i < 10; ++i)
		{
			SDL_SetRenderDrawColor(MyRender, DistR(RandomDevice),
				DistG(RandomDevice), DistB(RandomDevice), DistA(Ra															ndomDevice));

			SDL_Rect MyRect = { DistX(RandomDevice), DistY(RandomDevice)
				, DistX(RandomDevice), DistY(RandomDevice) };

			SDL_RenderFillRect(MyRender, &MyRect);																			
		}*/
		
		// 동그라미
		SDL_SetRenderDrawColor(MyRender, 255, 0, 0, 0);

		int Radius = 200;
		int CenterX = 512;
		int CenterY = 360;
		int Size = 30;

		for (int Theta = 0; Theta < 360; Theta += Size)
		{
			
			float Radian1 = (float)Theta * 3.141592f / 180.0f;
			float Radian2 = (float)(Theta + Size) * 3.141592f / 180.0f;
			int X1 = Radius * SDL_cos(Radian1) + CenterX;
			int Y1 = Radius * SDL_sin(Radian1) + CenterY;
			int X2 = Radius * SDL_cos(Radian2) + CenterX;
			int Y2 = Radius * SDL_sin(Radian2) + CenterY;

			//SDL_RenderDrawPoint(MyRender, X1, Y1);
			SDL_RenderDrawLine(MyRender, X1, Y1, X2, Y2);
		}


		// 보내기 CPU -> GPU
		// 많이 보낼 수록 느려짐.
		SDL_RenderPresent(MyRender); 
	}

	// 만들었으면 지우기
	SDL_DestroyRenderer(MyRender);

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