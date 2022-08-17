#pragma once
#include<map>
#include"Publisher.h"
#include"Singleton.h"

class PuruGameSystem;

class InputManager : public Publisher, public Singleton<InputManager> {
private:

	HANDLE m_handleInputThread;

	bool m_bStart{ true };

	std::map<int, bool> m_pressedKeys{};

	PuruGameSystem* m_pge;
	CriticalSection m_cs;

public:
	~InputManager();
	void ShutDown();

	bool Initiate(PuruGameSystem* _pge);
	static DWORD WINAPI GetInputThread(LPVOID lpParam);
	void SetStart(bool _start);

	void PublishEvent(Event* _event);
	void AddSubscriber(Subscriber* _subscriber);
	void RemoveSubscriber(Subscriber* _subscriber);
};
