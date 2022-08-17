#pragma once
#include"GameState.h"
#include"Singleton.h"

class GameStateManager : public Singleton<GameStateManager>
{
public:
	~GameStateManager();

	bool Initialize();

	void ChangeState(Globals::GameStates _state);
	GameState* GetState();

private:
	GameState* m_currentGameState{ nullptr };
};