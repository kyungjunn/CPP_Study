#pragma once

// interface , C++  에는 interface  없음
// abstract class, pure virtual function
class IRenderableComponent
{
public:
	virtual void Render() = 0;

	int ZOrder = 0;

	int bIsVisible : 1;
};

