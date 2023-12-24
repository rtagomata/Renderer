#include "Misc.h"

namespace game {
	std::vector<GameObject*> gameObjects;
	int previousTime;
	std::thread bkgdThread;
	bool running = true;
	/*void gameOnExit() //remove?
	{
		running = false;
		game::bkgdThread.join();
		game::bkgdThread.~thread();
		while (!finished) {
			Sleep(1);
		}
	}*/
}