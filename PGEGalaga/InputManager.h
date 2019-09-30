#pragma once
#include<map>
#include"Publisher.h"
#include"Singleton.h"

class PuruGameSystem;

class InputManager : public Publisher, public Singleton {
private:
	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	static InputManager* m_inputManagerInstance;

	HANDLE m_handleInputThread;

	bool m_bStart{ true };

	std::map<int, bool> m_pressedKeys{};

	PuruGameSystem* m_pge;

public:
	static InputManager* GetInstance();
	~InputManager();
	static void DestroyInstance();
	void ShutDown();

	bool Initiate(PuruGameSystem* _pge);
	static DWORD WINAPI GetInputThread(LPVOID lpParam);
	void SetStart(bool _start);

	void PublishEvent(Event* _event);
	void AddSubscriber(Subscriber* _subscriber);
	void RemoveSubscriber(Subscriber* _subscriber);
};
