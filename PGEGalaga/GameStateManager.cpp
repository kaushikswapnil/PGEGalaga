#include "GameStateManager.h"
#include"CreditsMenuState.h"
#include"GameExitState.h"
#include"GameOverState.h"
#include"GameWonState.h"
#include"InstructionsMenuState.h"
#include"MainMenuState.h"
#include"PlayingState.h"

GameStateManager* GameStateManager::m_gameStateManagerInstance{ nullptr };

GameStateManager::GameStateManager() : Singleton()
{
	
}

GameStateManager::GameStateManager(const GameStateManager &)
{
}

GameStateManager & GameStateManager::operator=(const GameStateManager &)
{
	// TODO: insert return statement here
	return *this;
}

GameStateManager* GameStateManager::GetInstance()
{
	if (!m_gameStateManagerInstance) {
		m_cs.Lock();
		if (!m_gameStateManagerInstance)
			m_gameStateManagerInstance = new GameStateManager();
		m_cs.Unlock();
	}
	return m_gameStateManagerInstance;
}

GameStateManager::~GameStateManager()
{
	if (m_currentGameState)
		delete m_currentGameState;
}

bool GameStateManager::Initialize()
{
	m_currentGameState = new MainMenuState();
	if (!m_currentGameState)
	{
		return false;
	}
	m_currentGameState->Enter();
	return true;
}

void GameStateManager::ChangeState(Globals::GameStates _state)
{
	if (m_currentGameState) {
		m_currentGameState->Exit();
		delete m_currentGameState;
	}
	switch (_state) {
	case Globals::GameStates::STATE_NULL:
		break;
	case Globals::GameStates::STATE_MAINMENU:
		m_currentGameState = new MainMenuState();
		break;
	case Globals::GameStates::STATE_INSTRUCTIONSMENU:
		m_currentGameState = new InstructionsMenuState();
		break;
	case Globals::GameStates::STATE_CREDITSMENU:
		m_currentGameState = new CreditsMenuState();
		break;
	case Globals::GameStates::STATE_PLAYING:
		m_currentGameState = new PlayingState();
		break;
	case Globals::GameStates::STATE_GAMEOVER:
		m_currentGameState = new GameOverState();
		break;
	case Globals::GameStates::STATE_GAMEWON:
		m_currentGameState = new GameWonState();
		break;
	case Globals::GameStates::STATE_EXIT:
		m_currentGameState = new GameExitState();
		break;
		
	}
	if(_state != Globals::GameStates::STATE_NULL)
		m_currentGameState->Enter();
}

GameState * GameStateManager::GetState()
{
	return m_currentGameState;
}

void GameStateManager::DestroyInstance()
{
	if (m_gameStateManagerInstance)
		delete m_gameStateManagerInstance;
	m_gameStateManagerInstance = nullptr;
}
