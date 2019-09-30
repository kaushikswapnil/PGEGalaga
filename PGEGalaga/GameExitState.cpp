#include"GameExitState.h"
#include"ResourceManager.h"
#include"GraphicsManager.h"

GameExitState::GameExitState()
{
}

GameExitState::~GameExitState()
{
}

void GameExitState::ListenToEvent(Event * _event)
{
}

void GameExitState::HandleInput(Input_KeyEvent _keyEvent)
{
}

void GameExitState::Render()
{
}

void GameExitState::Enter()
{
	GameManager::GetInstance()->SetStart(false);
}

void GameExitState::Exit()
{
}

void GameExitState::Update(float dt)
{
}

void GameExitState::UpdateBG(float dt)
{
}

void GameExitState::InitializeBG()
{
}
