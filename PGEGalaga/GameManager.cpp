#include <PuruGameSystem.h>
#include"GameManager.h"
#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"InputManager.h"
#include"ResourceManager.h"
#include"AudioManager.h"
#include <functional>
GameManager::~GameManager() {
	ShutDown();
}

bool FrameFunc() {
	if (!GameManager::GetInstance()->IsStarted())
	{
		return false;
	}
	float dt = GameManager::GetInstance()->GetPGEPointer()->Timer_GetDelta();

	GameStateManager::GetInstance()->GetState()->Update(dt);

	return true;
}

bool RenderFunc() {

	if (!GameManager::GetInstance()->IsStarted())
	{
		return false;
	}

	GraphicsManager::GetInstance()->BeginScene();
	GameStateManager::GetInstance()->GetState()->Render();
	GraphicsManager::GetInstance()->EndScene();
	return true;
}

void GameManager::StartUp() {
	m_pge = PuruGameSystem::GetInstance();

	m_pge->System_SetState(puruCallBackState::PURU_FRAME, FrameFunc);
	m_pge->System_SetState(puruCallBackState::PURU_RENDER, RenderFunc);
	m_pge->System_SetState(puruBoolState::PURU_WINDOWED, true);
	m_pge->System_SetState(puruIntState::PURU_SCREENWIDTH, 800);
	m_pge->System_SetState(puruIntState::PURU_SCREENHEIGHT, 600);
	m_pge->System_SetState(puruIntState::PURU_FPS, 60);
	
	if (m_pge->Initialize()) { //System_initiate() initiates all h/w and s/w and creates application window. In case of error, message is stored in System_GetErrorMessage()

		bool result = Initialize();
		if (!result)
		{
			ShutDown();
			return;
		}

		m_pge->Run();

	}
	else
	{
		MessageBox(NULL, L"Could not initialize PGE", L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

}

void GameManager::ShutDown() {
	m_pge->Shutdown(); //Releases all allocated resources, destroys window application, and restores video mode
	m_pge = nullptr;
}

PuruGameSystem * GameManager::GetPGEPointer()
{
	return m_pge;
}

void GameManager::SetStart(bool _start)
{
	m_bStart = _start;
	InputManager::GetInstance()->SetStart(false);
}

bool GameManager::GetStart()
{
	return m_bStart;
}

bool GameManager::Initialize()
{
	bool result = false;

	result = InputManager::GetInstance()->Initiate(m_pge);
	if (!result)
	{
		return false;
	}
	result = ResourceManager::GetInstance()->Initiate();
	if (!result)
	{
		return false;
	}
	result = GraphicsManager::GetInstance()->Initialize(m_pge);
	if (!result)
	{
		return false;
	}
	result = GameStateManager::GetInstance()->Initialize();
	if (!result)
	{
		return false;
	}

	return true;
}


