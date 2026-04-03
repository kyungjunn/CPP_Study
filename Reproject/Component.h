#pragma once

// 이걸 상속받는 사람들한테 밑에 함수를 무조건 만들라고 강요
// 추상 클래스
// interface
class UComponent
{
public:
	UComponent();
	virtual ~UComponent();

	// 순수 가상 함수
	virtual void BeginPlay() = 0;

	virtual void Tick() = 0;

};