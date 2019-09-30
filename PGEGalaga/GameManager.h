#pragma once
#include <Singleton.h>
#include <PuruGameSystem.h>

class InputManager;
class ResourceManager;
class GameStateManager;
class GraphicsManager;
class AudioManager;

class GameManager : public Singleton {
private:
	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	static GameManager* m_gameManagerInstance;

	PuruGameSystem *m_pge{ 0 };

	bool m_bStart{ true };
	bool m_bInitialized{ false };

	InputManager* m_InputManager;
	ResourceManager* m_ResourceManager;
	GameStateManager* m_GameStateManager;
	GraphicsManager* m_GraphicsManager;
	AudioManager* m_AudioManager;

public:	
	static GameManager* GetInstance();
	~GameManager();

	void StartUp();

	//PGE Functions
	static bool FrameFunc();
	static bool RenderFunc();

	PuruGameSystem* GetPGEPointer();

	void SetStart(bool _start);
	bool GetStart();

	static void DestroyInstance();

private:
	bool Initialize();
	void LoadManagers();
	void ShutDown();
 };