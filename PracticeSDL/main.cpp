#include <iostream>

#include <SDL.h>

// 사용할 라이브러리 파일 추가
// 이거까지 해야 빌드할 때 생성
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

using namespace std;

int SDL_main(int argc, char* argv[])
{
	// 초기화
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("MyWindow", 100, 100,
		1024, 720, SDL_WINDOW_SHOWN);

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow,
		-1, 0);

	int X = 0;
	int Y = 0;
	int TileSize = 20;
	bool bIsRunning = true;

	while (bIsRunning)
	{
		SDL_Event MyEvent;
		SDL_PollEvent(&MyEvent);


		SDL_Keycode Keycode = MyEvent.key.keysym.sym;
		if (MyEvent.type == SDL_QUIT || Keycode == SDLK_ESCAPE)
		{
			bIsRunning = false;
		}

		if (MyEvent.type == SDL_KEYDOWN)
		{
			if (Keycode == SDLK_w)
			{
				Y--;
			}
			if (Keycode == SDLK_s)
			{
				Y++;
			}
			if (Keycode == SDLK_a)
			{
				X--;
			}
			if (Keycode == SDLK_d)
			{
				X++;
			}
		}


		SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 255);
		SDL_RenderClear(MyRenderer);


		SDL_SetRenderDrawColor(MyRenderer, 255, 0, 0, 255);
		SDL_Rect Square = { X, Y, TileSize, TileSize };
		SDL_RenderFillRect(MyRenderer, &Square);

		SDL_RenderPresent(MyRenderer);
	}

	SDL_DestroyRenderer(MyRenderer);

	SDL_DestroyWindow(MyWindow);

	SDL_Quit();

	return 0;
}