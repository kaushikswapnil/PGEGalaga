#pragma once
#include"GameState.h"
#include"World.h"

class PlayingState : public GameState {
private:
	World* m_world{ nullptr };
public:
	PlayingState();
	~PlayingState();

	void ListenToEvent(Event* _event);
	void HandleInput(Input_KeyEvent* _keyEvent);
	void Render();
	void Enter();
	void Exit();
	void Update(float dt);

	void UpdateBG(float dt);
	void InitializeBG();

};