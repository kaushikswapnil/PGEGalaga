#include"GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameManager* Game = GameManager::GetInstance();

	Game->StartUp();

	return 0;
}



