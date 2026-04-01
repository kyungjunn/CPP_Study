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