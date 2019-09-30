#pragma once
#include"GameState.h"

class Resource_Audio;
class Resource_Sprite;

class GameWonState : public GameState {
public:
	GameWonState();
	~GameWonState();

	void ListenToEvent(Event* _event);
	void HandleInput(Input_KeyEvent* _keyEvent);
	void Render();
	void Enter();
	void Exit();
	void Update(float dt);

	void UpdateBG(float dt);
	void InitializeBG();

private:
	Resource_Audio* m_sndMenu;
	Resource_Sprite* m_sprCursor{ nullptr };
};