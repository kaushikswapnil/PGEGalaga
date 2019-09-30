#pragma once
#include"Event.h"

class Input_KeyEvent : public Event {
private:
	int m_virtualKey;
	bool m_bDown;

public:
	Input_KeyEvent(int _virtualKey, bool _down) : Event(), m_virtualKey(_virtualKey), m_bDown(_down) { };
	int GetVirtualKey() { return m_virtualKey; }
	bool IsDown() { return m_bDown; }
};