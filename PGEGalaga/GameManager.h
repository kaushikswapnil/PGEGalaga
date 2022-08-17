#pragma once
#include <Singleton.h>
#include <PuruGameSystem.h>

class InputManager;
class ResourceManager;
class GameStateManager;
class GraphicsManager;
class AudioManager;

class GameManager : public Singleton<GameManager> {
private:
	PuruGameSystem *m_pge{ 0 };

	bool m_bStart{ true };
	bool m_bInitialized{ false };

	InputManager* m_InputManager;
	ResourceManager* m_ResourceManager;
	GameStateManager* m_GameStateManager;
	GraphicsManager* m_GraphicsManager;
	AudioManager* m_AudioManager;

public:	
	~GameManager();

	void StartUp();

	bool IsStarted() const {return m_bStart; }

	PuruGameSystem* GetPGEPointer();

	void SetStart(bool _start);
	bool GetStart();

private:
	bool Initialize();
	void ShutDown();
 };