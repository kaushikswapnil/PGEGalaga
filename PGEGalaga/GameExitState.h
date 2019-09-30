#pragma once
#include"GameState.h"

class GameExitState : public GameState {
public:
	GameExitState();
	~GameExitState();

	void ListenToEvent(Event* _event);
	void HandleInput(const Input_KeyEvent _keyEvent);
	void Render();
	void Enter();
	void Exit();
	void Update(float dt);

	void UpdateBG(float dt);
	void InitializeBG();
};