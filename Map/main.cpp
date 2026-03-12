#include "Engine.h"

int main()
{
	
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
