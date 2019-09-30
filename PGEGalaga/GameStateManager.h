#pragma once
#include"GameState.h"
#include"Singleton.h"

class GameStateManager : public Singleton
{
public:
	static GameStateManager* GetInstance();
	~GameStateManager();

	bool Initialize();

	void ChangeState(Globals::GameStates _state);
	GameState* GetState();

	static void DestroyInstance();

private:
	GameStateManager();
	GameStateManager(const GameStateManager&);
	GameStateManager& operator=(const GameStateManager&);
	static GameStateManager* m_gameStateManagerInstance;
	GameState* m_currentGameState{ nullptr };

};