#include <iostream>
#include "Engine.h"
#include "World.h"

#include <string>
#include <map> 

using namespace std;

//typedef unsigned char byte;
using byte = unsigned char;

int SDL_main(int argc, char* argv[])
{
	// key 값 value 값 -> 딕셔너리
	std::map<string, string> Dictionary;

	Dictionary["hello"] = "ㅎㅇ";
	Dictionary["world"] = "ㅎㅎ";
	Dictionary["4"] = "죽을 사";
	Dictionary["1"] = "일";

	for (std::map<std::string, std::string>::iterator i = Dictionary.begin(); i != Dictionary.end(); ++i)
	{
		cout << (i->first) << ", " << (i->second) << endl;
	}

	for (auto i : Dictionary)
	{
		cout << i.first << ", " << i.second << endl;
	}
	//GENGINE->GetInstance();
	//UEngine* MyEngine = UEngine::GetInstance();

	// 엔진을 먼저 키고 -> 월드를 받아와서 -> 맵 이름 파일로 맵을 로딩
	//GEngine->GetWorld()->Load("level01.txt");

	//// 그리고 실행
	//GEngine->Run();

	//delete GEngine;

	return 0;
}