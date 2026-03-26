#include <iostream>
#include "Engine.h"
#include "World.h"
#include <fstream> // 파일 읽고 쓰기

using namespace std;

int main()
{
	UEngine* MyEngine = new UEngine();
	
	MyEngine->GetWorld()->Load("level01.umap");

	MyEngine->Run();

	delete MyEngine;
	return 0;
}