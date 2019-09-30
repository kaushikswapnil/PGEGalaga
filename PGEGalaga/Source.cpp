#include"GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameManager* Game = GameManager::GetInstance();

	Game->StartUp();

	delete Game;
	Game = nullptr;

	return 0;
}



