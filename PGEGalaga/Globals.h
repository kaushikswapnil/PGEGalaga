#pragma once

namespace Globals {
	enum Direction { STOP = 0, LEFT = 1, RIGHT = 2 };

	enum GameStates{ STATE_NULL, STATE_MAINMENU, STATE_INSTRUCTIONSMENU, STATE_CREDITSMENU, STATE_PLAYING, STATE_GAMEOVER, STATE_GAMEWON, STATE_EXIT};

	struct Position {
		float x, y;
		Position() : x(400.0f), y(300.0f) {}
		Position(float _x, float _y) : x(_x), y(_y) {}
	};

	const float WORLD_SCALE{ 2.0f };

	const float MAX_PLAYER_SPEED{ 4.0f };
	const float BULLET_SPEED{ 3.5f };
	const float BASE_PLAYER_SPEED{ 2.0f };
	const int MAX_LEVEL{ 3 };

	long long int MyGetTime();

	
}
