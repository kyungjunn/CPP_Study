#pragma once

#ifndef __ENGINE_H__

#define __ENGINE_H__

// 맵 초기화
extern int Map[10][10];

// 메모리에 공간 잡은거 아님
struct FVector2i
{
	int X;
	int Y;
};

extern FVector2i PlayerPosition; // -> 애가 잡은거임. 전역 선언

int Input();

void Process(int PlayerInput);

void Render();

void Gotoxy(int x, int y);

void Clear();

void AddPlayerOffset(FVector2i DeltaPosition);
void AddPlayerOffset(int DeltaX, int DeltaY);

#endif