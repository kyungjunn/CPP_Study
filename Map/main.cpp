#include "Engine.h"

int main()
{
	bool bIsPlaying = true;
	Render();

	// 절차지향
	// GameLoop
	while (bIsPlaying) // -> Frame
	{
		int PlayerInput = Input();
		Process(PlayerInput);
		Render();
	}

	return 0;
}
