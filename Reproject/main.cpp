#include <iostream>
#include "Engine.h"
#include "World.h"

#include <random>

using namespace std;

int SDL_main(int argc, char* argv[])
{
	//GENGINE->GetInstance();
	//UEngine* MyEngine = UEngine::GetInstance();

	// 엔진을 먼저 키고 -> 월드를 받아와서 -> 맵 이름 파일로 맵을 로딩
	GENGINE->GetWorld()->Load("level01.txt");

	// 그리고 실행
	GENGINE->Run();

	return 0;
}