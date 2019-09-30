#pragma once
#include"Input_KeyEvent.h"

class Input_DownKeyEvent : public Input_KeyEvent
{
public:
	Input_DownKeyEvent(int _virtualkeycode) : Input_KeyEvent(_virtualkeycode) {};
	~Input_DownKeyEvent() {};

private:

};

