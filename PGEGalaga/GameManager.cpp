#include <PuruGameSystem.h>
#include"GameManager.h"
#include"GraphicsManager.h"
#include"GameStateManager.h"
#include"InputManager.h"
#include"ResourceManager.h"
#include"AudioManager.h"

GameManager* GameManager::m_gameManagerInstance{ nullptr };

GameManager::GameManager() : Singleton() {
}

GameManager::~GameManager() {
	m_GraphicsManager->DestroyInstance();
	m_AudioManager->DestroyInstance();
	m_GameStateManager->DestroyInstance();
	m_ResourceManager->DestroyInstance();
	m_InputManager->DestroyInstance();
	ShutDown();
}

GameManager * GameManager::GetInstance()
{
	if (!m_gameManagerInstance) {
		m_cs.Lock();
		if (!m_gameManagerInstance)
			m_gameManagerInstance = new GameManager();
		m_cs.Unlock();
	}
	return m_gameManagerInstance;
}

void GameManager::StartUp() {
	m_pge = PuruGameSystem::GetInstance();

	m_pge->System_SetState(PURU_FRAME, FrameFunc);
	m_pge->System_SetState(PURU_RENDER, RenderFunc);
	m_pge->System_SetState(PURU_WINDOWED, true);
	m_pge->System_SetState(PURU_SCREENWIDTH, 800);
	m_pge->System_SetState(PURU_SCREENHEIGHT, 600);
	m_pge->System_SetState(PURU_FPS, 60);	
	
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

bool GameManager::FrameFunc() {
	if (!GameManager::GetInstance()->m_bStart)
	{
			return false;
	}
	float dt = GameManager::GetInstance()->GetPGEPointer()->Timer_GetDelta();

	GameStateManager::GetInstance()->GetState()->Update(dt);

	return true;
}

bool GameManager::RenderFunc() {

	if (!GameManager::GetInstance()->m_bStart)
	{
		return false;
	}

	GameManager::GetInstance()->m_GraphicsManager->BeginScene();
	GameStateManager::GetInstance()->GetState()->Render();
	GameManager::GetInstance()->m_GraphicsManager->EndScene();
	return true;
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

void GameManager::DestroyInstance()
{
	if (m_gameManagerInstance)
		delete m_gameManagerInstance;
	m_gameManagerInstance = nullptr;
}

bool GameManager::Initialize()
{
	bool result = false;
	
	LoadManagers();

	result = m_InputManager->Initiate(m_pge);
	if (!result)
	{
		return false;
	}
	result = m_ResourceManager->Initiate();
	if (!result)
	{
		return false;
	}
	result = m_GraphicsManager->Initialize(m_pge);
	if (!result)
	{
		return false;
	}
	result = m_GameStateManager->Initialize();
	if (!result)
	{
		return false;
	}

	return true;
}

void GameManager::LoadManagers()
{
	m_InputManager = InputManager::GetInstance();
	m_ResourceManager = ResourceManager::GetInstance();
	m_GameStateManager = GameStateManager::GetInstance();
	m_GraphicsManager = GraphicsManager::GetInstance();
	m_AudioManager = AudioManager::GetInstance();
}



